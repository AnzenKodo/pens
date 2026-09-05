// Copyright (c) 2026 - snd module
// Implementation of snd_core.h, backed by miniaudio.h

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "snd_core.h"

////////////////////////////////
//~ snd: Internal Types

typedef struct Snd_Sound Snd_Sound;
struct Snd_Sound
{
  U32          gen;
  B32          in_use;
  ma_decoder   decoder;
  B32          decoder_valid;
  Snd_LoadFlags flags;
};

typedef struct Snd_VoiceSlot Snd_VoiceSlot;
struct Snd_VoiceSlot
{
  U32            gen;
  Snd_VoiceState state;
  Snd_Handle     sound;
  Snd_PlayParams params;
  U64            frame_cursor;
};

typedef struct Snd_State Snd_State;
struct Snd_State
{
  B32              initialized;
  ma_device        device;
  ma_device_config device_config;

  U32              sample_rate;
  U32              channel_count;

  F32              master_volume;
  B32              master_paused;
  F32              bus_volume[SND_MAX_BUSES];

  Snd_Sound        sounds[SND_MAX_SOUNDS];
  U32              sound_free_count;
  U32              sound_free_list[SND_MAX_SOUNDS];

  Snd_VoiceSlot    voices[SND_MAX_VOICES];
};

global Snd_State snd_state = {0};

////////////////////////////////
//~ snd: Helpers (internal)

internal Snd_Sound *
snd__sound_from_handle(Snd_Handle handle)
{
  Snd_Sound *result = 0;
  if(handle.idx < SND_MAX_SOUNDS)
  {
    Snd_Sound *slot = &snd_state.sounds[handle.idx];
    if(slot->in_use && slot->gen == handle.gen)
    {
      result = slot;
    }
  }
  return result;
}

internal Snd_VoiceSlot *
snd__voice_from_handle(Snd_Voice voice)
{
  Snd_VoiceSlot *result = 0;
  if(voice.idx < SND_MAX_VOICES)
  {
    Snd_VoiceSlot *slot = &snd_state.voices[voice.idx];
    if(slot->state != Snd_VoiceState_Inactive && slot->gen == voice.gen)
    {
      result = slot;
    }
  }
  return result;
}

// NOTE(snd): `pitch` is tracked on the voice and exposed through the API for
// future work, but this mixer does not yet resample per-voice -- hooking it
// up means running each decoder through an ma_data_converter (or ma_pitch
// shifter) keyed off params.pitch before the gain stage below.
internal void
snd__mix_voice_into_buffer(Snd_VoiceSlot *voice, F32 *out, U32 frame_count, U32 channels)
{
  Snd_Sound *sound = snd__sound_from_handle(voice->sound);
  if(sound == 0 || !sound->decoder_valid || voice->state != Snd_VoiceState_Playing)
  {
    return;
  }

  local_persist F32 scratch[4096];
  U32 max_scratch_frames = (U32)(ArrayCount(scratch) / channels);
  U32 frames_left = frame_count;
  F32 *dst = out;

  ma_decoder_seek_to_pcm_frame(&sound->decoder, voice->frame_cursor);

  while(frames_left > 0)
  {
    U32 frames_this_pass = Min(frames_left, max_scratch_frames);
    ma_uint64 frames_read = 0;
    ma_decoder_read_pcm_frames(&sound->decoder, scratch, frames_this_pass, &frames_read);

    F32 vol = Clamp(0.f, voice->params.volume, 1.f) *
              Clamp(0.f, snd_state.bus_volume[voice->params.bus], 1.f) *
              Clamp(0.f, snd_state.master_volume, 1.f);

    F32 pan = Clamp(-1.f, voice->params.pan, 1.f);
    F32 left_gain  = vol * Min(1.f, 1.f - pan);
    F32 right_gain = vol * Min(1.f, 1.f + pan);

    for(U32 f = 0; f < (U32)frames_read; f += 1)
    {
      for(U32 c = 0; c < channels; c += 1)
      {
        F32 s = scratch[f*channels + c];
        F32 gain = (channels >= 2) ? ((c == 0) ? left_gain : right_gain) : vol;
        dst[f*channels + c] += s * gain;
      }
    }

    voice->frame_cursor += frames_read;
    dst += (U64)frames_this_pass * channels;
    frames_left -= (U32)frames_read;

    B32 hit_end = (frames_read < frames_this_pass);
    if(hit_end)
    {
      if(voice->params.flags & Snd_PlayFlag_Loop)
      {
        voice->frame_cursor = 0;
        ma_decoder_seek_to_pcm_frame(&sound->decoder, 0);
      }
      else
      {
        voice->state = Snd_VoiceState_Finished;
        break;
      }
    }
  }
}

internal void
snd__device_data_callback(ma_device *device, void *output, const void *input, ma_uint32 frame_count)
{
  (void)input;
  F32 *out = (F32 *)output;
  U32 channels = snd_state.channel_count;

  if(snd_state.master_paused)
  {
    return;
  }

  for(U32 i = 0; i < SND_MAX_VOICES; i += 1)
  {
    Snd_VoiceSlot *voice = &snd_state.voices[i];
    if(voice->state == Snd_VoiceState_Playing)
    {
      snd__mix_voice_into_buffer(voice, out, frame_count, channels);
    }
  }

  (void)device;
}

////////////////////////////////
//~ snd: Play Parameters

function Snd_PlayParams
snd_play_params_default(void)
{
  Snd_PlayParams result = {0};
  result.volume = 1.f;
  result.pitch  = 1.f;
  result.pan    = 0.f;
  result.bus    = 0;
  result.flags  = 0;
  return result;
}

////////////////////////////////
//~ snd: Lifetime

function B32
snd_init(U32 sample_rate, U32 channel_count)
{
  B32 result = Snd_False;
  if(!snd_state.initialized)
  {
    for(U32 i = 0; i < SND_MAX_SOUNDS; i += 1)
    {
      snd_state.sound_free_list[SND_MAX_SOUNDS - 1 - i] = i;
    }
    snd_state.sound_free_count = SND_MAX_SOUNDS;

    snd_state.sample_rate   = sample_rate;
    snd_state.channel_count = channel_count;
    snd_state.master_volume = 1.f;
    for(U32 i = 0; i < SND_MAX_BUSES; i += 1)
    {
      snd_state.bus_volume[i] = 1.f;
    }

    snd_state.device_config = ma_device_config_init(ma_device_type_playback);
    snd_state.device_config.playback.format   = ma_format_f32;
    snd_state.device_config.playback.channels = channel_count;
    snd_state.device_config.sampleRate        = sample_rate;
    snd_state.device_config.dataCallback      = snd__device_data_callback;

    ma_result init_result = ma_device_init(0, &snd_state.device_config, &snd_state.device);
    if(init_result == MA_SUCCESS)
    {
      ma_result start_result = ma_device_start(&snd_state.device);
      if(start_result == MA_SUCCESS)
      {
        snd_state.initialized = Snd_True;
        result = Snd_True;
      }
      else
      {
        ma_device_uninit(&snd_state.device);
      }
    }
  }
  return result;
}

function void
snd_shutdown(void)
{
  if(snd_state.initialized)
  {
    ma_device_uninit(&snd_state.device);
    for(U32 i = 0; i < SND_MAX_SOUNDS; i += 1)
    {
      Snd_Sound *sound = &snd_state.sounds[i];
      if(sound->in_use && sound->decoder_valid)
      {
        ma_decoder_uninit(&sound->decoder);
      }
    }
    Snd_State zero = {0};
    snd_state = zero;
  }
}

function void
snd_update(void)
{
  // NOTE(snd): reap finished voices; nothing to do beyond marking them inactive,
  // since the mixer already skips non-playing voices.
  for(U32 i = 0; i < SND_MAX_VOICES; i += 1)
  {
    Snd_VoiceSlot *voice = &snd_state.voices[i];
    if(voice->state == Snd_VoiceState_Finished)
    {
      voice->state = Snd_VoiceState_Inactive;
      voice->gen += 1;
    }
  }
}

////////////////////////////////
//~ snd: Sound Loading

function Snd_Handle
snd_sound_load_from_path(char *path, Snd_LoadFlags flags)
{
  Snd_Handle result = snd_handle_zero;
  if(snd_state.sound_free_count > 0)
  {
    U32 idx = snd_state.sound_free_list[--snd_state.sound_free_count];
    Snd_Sound *slot = &snd_state.sounds[idx];

    ma_decoder_config cfg = ma_decoder_config_init(ma_format_f32, snd_state.channel_count, snd_state.sample_rate);
    ma_result decode_result = ma_decoder_init_file(path, &cfg, &slot->decoder);
    if(decode_result == MA_SUCCESS)
    {
      slot->in_use = Snd_True;
      slot->decoder_valid = Snd_True;
      slot->flags = flags;
      result.idx = idx;
      result.gen = slot->gen;
    }
    else
    {
      snd_state.sound_free_list[snd_state.sound_free_count++] = idx;
    }
  }
  return result;
}

function Snd_Handle
snd_sound_load_from_memory(void *data, U64 size, Snd_LoadFlags flags)
{
  Snd_Handle result = snd_handle_zero;
  if(snd_state.sound_free_count > 0)
  {
    U32 idx = snd_state.sound_free_list[--snd_state.sound_free_count];
    Snd_Sound *slot = &snd_state.sounds[idx];

    ma_decoder_config cfg = ma_decoder_config_init(ma_format_f32, snd_state.channel_count, snd_state.sample_rate);
    ma_result decode_result = ma_decoder_init_memory(data, size, &cfg, &slot->decoder);
    if(decode_result == MA_SUCCESS)
    {
      slot->in_use = Snd_True;
      slot->decoder_valid = Snd_True;
      slot->flags = flags;
      result.idx = idx;
      result.gen = slot->gen;
    }
    else
    {
      snd_state.sound_free_list[snd_state.sound_free_count++] = idx;
    }
  }
  return result;
}

function void
snd_sound_unload(Snd_Handle handle)
{
  Snd_Sound *sound = snd__sound_from_handle(handle);
  if(sound != 0)
  {
    if(sound->decoder_valid)
    {
      ma_decoder_uninit(&sound->decoder);
      sound->decoder_valid = Snd_False;
    }
    sound->in_use = Snd_False;
    sound->gen += 1;
    U32 idx = (U32)(sound - snd_state.sounds);
    snd_state.sound_free_list[snd_state.sound_free_count++] = idx;
  }
}

function B32
snd_handle_is_valid(Snd_Handle handle)
{
  return snd__sound_from_handle(handle) != 0;
}

////////////////////////////////
//~ snd: Playback

function Snd_Voice
snd_play(Snd_Handle sound, Snd_PlayParams params)
{
  Snd_Voice result = snd_voice_zero;
  if(snd__sound_from_handle(sound) != 0)
  {
    for(U32 i = 0; i < SND_MAX_VOICES; i += 1)
    {
      Snd_VoiceSlot *slot = &snd_state.voices[i];
      if(slot->state == Snd_VoiceState_Inactive)
      {
        slot->sound        = sound;
        slot->params       = params;
        slot->frame_cursor = 0;
        slot->state        = (params.flags & Snd_PlayFlag_StartPaused)
                              ? Snd_VoiceState_Paused
                              : Snd_VoiceState_Playing;
        result.idx = i;
        result.gen = slot->gen;
        break;
      }
    }
  }
  return result;
}

function void
snd_voice_stop(Snd_Voice voice)
{
  Snd_VoiceSlot *slot = snd__voice_from_handle(voice);
  if(slot != 0)
  {
    slot->state = Snd_VoiceState_Inactive;
    slot->gen += 1;
  }
}

function void
snd_voice_pause(Snd_Voice voice)
{
  Snd_VoiceSlot *slot = snd__voice_from_handle(voice);
  if(slot != 0 && slot->state == Snd_VoiceState_Playing)
  {
    slot->state = Snd_VoiceState_Paused;
  }
}

function void
snd_voice_resume(Snd_Voice voice)
{
  Snd_VoiceSlot *slot = snd__voice_from_handle(voice);
  if(slot != 0 && slot->state == Snd_VoiceState_Paused)
  {
    slot->state = Snd_VoiceState_Playing;
  }
}

function void
snd_voice_set_volume(Snd_Voice voice, F32 volume)
{
  Snd_VoiceSlot *slot = snd__voice_from_handle(voice);
  if(slot != 0)
  {
    slot->params.volume = Clamp(0.f, volume, 1.f);
  }
}

function void
snd_voice_set_pitch(Snd_Voice voice, F32 pitch)
{
  Snd_VoiceSlot *slot = snd__voice_from_handle(voice);
  if(slot != 0)
  {
    slot->params.pitch = Max(0.01f, pitch);
  }
}

function void
snd_voice_set_pan(Snd_Voice voice, F32 pan)
{
  Snd_VoiceSlot *slot = snd__voice_from_handle(voice);
  if(slot != 0)
  {
    slot->params.pan = Clamp(-1.f, pan, 1.f);
  }
}

function Snd_VoiceState
snd_voice_state(Snd_Voice voice)
{
  Snd_VoiceState result = Snd_VoiceState_Inactive;
  Snd_VoiceSlot *slot = snd__voice_from_handle(voice);
  if(slot != 0)
  {
    result = slot->state;
  }
  return result;
}

function B32
snd_voice_is_valid(Snd_Voice voice)
{
  return snd__voice_from_handle(voice) != 0;
}

////////////////////////////////
//~ snd: Bus / Master Control

function void
snd_bus_set_volume(U32 bus, F32 volume)
{
  if(bus < SND_MAX_BUSES)
  {
    snd_state.bus_volume[bus] = Clamp(0.f, volume, 1.f);
  }
}

function F32
snd_bus_volume(U32 bus)
{
  F32 result = 0.f;
  if(bus < SND_MAX_BUSES)
  {
    result = snd_state.bus_volume[bus];
  }
  return result;
}

function void
snd_set_master_volume(F32 volume)
{
  snd_state.master_volume = Clamp(0.f, volume, 1.f);
}

function F32
snd_master_volume(void)
{
  return snd_state.master_volume;
}

function void
snd_set_master_pause(B32 paused)
{
  snd_state.master_paused = paused;
}

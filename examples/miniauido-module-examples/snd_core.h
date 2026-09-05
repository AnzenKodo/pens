// Copyright (c) 2026 - snd module
// Sound playback layer, built on top of miniaudio.h
// Style: base types + module prefix + arena-free fixed pools, RAD-debugger-flavored

#ifndef SND_CORE_H
#define SND_CORE_H

#include "snd_base.h"

////////////////////////////////
//~ snd: Base Types

#if !defined(SND_BASE_TYPES_DEFINED)
#define SND_BASE_TYPES_DEFINED

#include <stdint.h>
#include <stddef.h>

typedef uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
typedef int8_t   S8;
typedef int16_t  S16;
typedef int32_t  S32;
typedef int64_t  S64;
typedef float    F32;
typedef double   F64;
typedef S32      B32;
typedef size_t   USZ;

#define Snd_False 0
#define Snd_True  1

#endif // SND_BASE_TYPES_DEFINED

////////////////////////////////
//~ snd: Helper Macros

#if !defined(Min)
# define Min(a,b) (((a)<(b))?(a):(b))
#endif
#if !defined(Max)
# define Max(a,b) (((a)>(b))?(a):(b))
#endif
#if !defined(Clamp)
# define Clamp(lo,x,hi) (((x)<(lo))?(lo):((x)>(hi))?(hi):(x))
#endif
#if !defined(ArrayCount)
# define ArrayCount(a) (sizeof(a)/sizeof((a)[0]))
#endif

#if defined(_MSC_VER)
# define Snd_Assert(c) do{ if(!(c)){ __debugbreak(); } }while(0)
#else
# define Snd_Assert(c) do{ if(!(c)){ __builtin_trap(); } }while(0)
#endif

////////////////////////////////
//~ snd: Config

#define SND_MAX_SOUNDS    (256)
#define SND_MAX_VOICES    (64)
#define SND_MAX_BUSES     (8)
#define SND_INVALID_INDEX (0xFFFFFFFFu)

////////////////////////////////
//~ snd: Handles
//
// All external references to sounds / playing voices are generation-tagged
// indices into fixed pools, so stale handles are detectable rather than
// silently reused (RAD-style "handle, not pointer" API).

typedef struct Snd_Handle Snd_Handle;
struct Snd_Handle
{
  U32 idx;
  U32 gen;
};

typedef struct Snd_Voice Snd_Voice;
struct Snd_Voice
{
  U32 idx;
  U32 gen;
};

read_only Snd_Handle snd_handle_zero = {SND_INVALID_INDEX, 0};
read_only Snd_Voice  snd_voice_zero  = {SND_INVALID_INDEX, 0};

////////////////////////////////
//~ snd: Enums

typedef U32 Snd_LoadFlags;
enum
{
  Snd_LoadFlag_Stream    = (1<<0), // decode on the fly instead of loading fully into memory
  Snd_LoadFlag_Loop      = (1<<1), // default the sound to looping playback
};

typedef U32 Snd_PlayFlags;
enum
{
  Snd_PlayFlag_Loop      = (1<<0),
  Snd_PlayFlag_StartPaused = (1<<1),
};

typedef U32 Snd_VoiceState;
enum
{
  Snd_VoiceState_Inactive,
  Snd_VoiceState_Playing,
  Snd_VoiceState_Paused,
  Snd_VoiceState_Finished,
};

////////////////////////////////
//~ snd: Play Parameters

typedef struct Snd_PlayParams Snd_PlayParams;
struct Snd_PlayParams
{
  F32           volume;      // 0 = silent, 1 = unity gain
  F32           pitch;       // 1 = unmodified
  F32           pan;         // -1 = full left, 0 = center, 1 = full right
  U32           bus;         // index in [0, SND_MAX_BUSES)
  Snd_PlayFlags flags;
};

function Snd_PlayParams snd_play_params_default(void);

////////////////////////////////
//~ snd: Lifetime

function B32  snd_init(U32 sample_rate, U32 channel_count);
function void snd_shutdown(void);
function void snd_update(void); // call once per frame; reaps finished voices, applies bus volumes

////////////////////////////////
//~ snd: Sound Loading

function Snd_Handle snd_sound_load_from_path(char *path, Snd_LoadFlags flags);
function Snd_Handle snd_sound_load_from_memory(void *data, U64 size, Snd_LoadFlags flags);
function void        snd_sound_unload(Snd_Handle handle);
function B32          snd_handle_is_valid(Snd_Handle handle);

////////////////////////////////
//~ snd: Playback

function Snd_Voice snd_play(Snd_Handle sound, Snd_PlayParams params);
function void        snd_voice_stop(Snd_Voice voice);
function void        snd_voice_pause(Snd_Voice voice);
function void        snd_voice_resume(Snd_Voice voice);
function void        snd_voice_set_volume(Snd_Voice voice, F32 volume);
function void        snd_voice_set_pitch(Snd_Voice voice, F32 pitch);
function void        snd_voice_set_pan(Snd_Voice voice, F32 pan);
function Snd_VoiceState snd_voice_state(Snd_Voice voice);
function B32          snd_voice_is_valid(Snd_Voice voice);

////////////////////////////////
//~ snd: Bus / Master Control

function void snd_bus_set_volume(U32 bus, F32 volume);
function F32  snd_bus_volume(U32 bus);
function void snd_set_master_volume(F32 volume);
function F32  snd_master_volume(void);
function void snd_set_master_pause(B32 paused);

#endif // SND_CORE_H

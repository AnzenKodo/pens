# snd — a small sound module (miniaudio backend)

Written in RAD-Debugger-flavored C: `snake_case` module-prefixed functions,
generation-tagged handles instead of raw pointers, fixed pools instead of
`malloc` scattered through the code, `//~ snd:` section banners, and the
`function` / `internal` / `global` / `read_only` linkage keywords instead of
raw `static`.

## Files
- `snd_base.h`   — the handful of linkage keywords the module needs. Skip this
  if you already have a base layer (e.g. from raddebugger itself) that
  defines `function`/`internal`/`global`/`read_only`.
- `snd_core.h`   — public API: types, handles, lifetime, loading, playback, buses.
- `snd_core.c`   — implementation. Owns `#define MINIAUDIO_IMPLEMENTATION`.
- `example_main.c` — plays a file from argv[1] until you hit enter.
- `miniaudio.h`  — vendored dependency (single-header, public domain / MIT-0),
  pulled straight from `mackron/miniaudio`.

## Design
- **Handles, not pointers.** `Snd_Handle` (loaded sound) and `Snd_Voice`
  (a playing instance) are `{idx, gen}` pairs into fixed arrays
  (`SND_MAX_SOUNDS = 256`, `SND_MAX_VOICES = 64`). Stopping a voice or
  unloading a sound bumps its generation, so a stale handle held elsewhere
  fails `snd_voice_is_valid`/`snd_handle_is_valid` instead of aliasing a
  reused slot silently.
- **No dynamic allocation at runtime.** Everything lives in one static
  `Snd_State`, sized at compile time via the `SND_MAX_*` macros in
  `snd_core.h`.
- **Mixing** happens directly in miniaudio's device callback
  (`snd__device_data_callback`): each active voice seeks its decoder to
  `frame_cursor`, decodes into a scratch buffer, and gets summed into the
  output with per-voice volume/pan combined with its bus volume and the
  master volume.
- **Buses** are just `SND_MAX_BUSES` (8) volume multipliers — enough for a
  "music" / "sfx" / "ui" split without building a full mix graph.
- **Known simplification:** `Snd_PlayParams.pitch` is tracked and exposed but
  not yet applied — the mixer doesn't resample. Hooking it up means running
  each voice's decoder through an `ma_data_converter` keyed off `pitch`
  before the gain stage in `snd__mix_voice_into_buffer`. Left as a TODO
  rather than faked.

## Build
```bash
# Linux
gcc example_main.c snd_core.c -o example -lpthread -lm -ldl

# macOS
clang example_main.c snd_core.c -o example \
  -framework CoreAudio -framework CoreFoundation -framework AudioToolbox

# Windows (MSVC)
cl example_main.c snd_core.c /link ole32.lib
```
This was compiled and link-tested in-sandbox (warnings-as-checked, `-Wall
-Wextra`) and run end-to-end against a generated WAV through the full
init → load → play → stop → unload → shutdown lifecycle before being handed
to you.

## API sketch
```c
snd_init(48000, 2);

Snd_Handle sound = snd_sound_load_from_path("boom.wav", 0);

Snd_PlayParams p = snd_play_params_default();
p.volume = 0.8f;
p.bus    = 0;
Snd_Voice v = snd_play(sound, p);

// per-frame:
snd_update(); // reaps finished voices

snd_voice_stop(v);
snd_sound_unload(sound);
snd_shutdown();
```

// Example: minimal usage of the snd module.
// Build (Linux): gcc example_main.c snd_core.c -o example -lpthread -lm -ldl
// Build (macOS): clang example_main.c snd_core.c -o example -framework CoreAudio -framework CoreFoundation -framework AudioToolbox
// Build (Windows, MSVC): cl example_main.c snd_core.c /link ole32.lib

#include <stdio.h>
#include "snd_core.h"
#include "snd_core.c"

int
main(int argument_count, char **arguments)
{
  if(argument_count < 2)
  {
    printf("usage: %s <sound_file>\n", arguments[0]);
    return 1;
  }

  if(!snd_init(48000, 2))
  {
    printf("snd_init failed\n");
    return 1;
  }

  Snd_Handle sound = snd_sound_load_from_path(arguments[1], 0);
  if(!snd_handle_is_valid(sound))
  {
    printf("failed to load: %s\n", arguments[1]);
    snd_shutdown();
    return 1;
  }

  Snd_PlayParams params = snd_play_params_default();
  params.volume = 0.8f;
  params.bus    = 0;
  Snd_Voice voice = snd_play(sound, params);

  printf("playing... press enter to stop\n");
  getchar();

  snd_voice_stop(voice);
  snd_sound_unload(sound);
  snd_shutdown();
  return 0;
}

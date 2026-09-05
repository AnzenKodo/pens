/*
    play_audio.c - Example program to play audio files with miniaudio.
    This example does NOT use the high-level miniaudio engine. Instead,
    it uses the lower-level ma_device and ma_decoder APIs.
*/

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

/* Volatile flag to keep track of playback status across threads */
volatile ma_bool32 g_isPlaying = MA_TRUE;

/* SIGINT handler for graceful termination when user presses Ctrl+C */
void sigint_handler(int sig)
{
    (void)sig;
    g_isPlaying = MA_FALSE;
}

/*
    The data callback is where miniaudio requests more audio data.
    We read PCM frames from our decoder and write them to the output buffer (pOutput).
*/
void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    if (pDecoder == NULL) {
        return;
    }

    ma_uint64 framesRead = 0;
    ma_result result = ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, &framesRead);
    
    if (result != MA_SUCCESS || framesRead < frameCount) {
        /*
            If we reached the end of the file or an error occurred,
            we zero out the rest of the output buffer to avoid noise/static,
            and stop playback.
        */
        ma_uint32 bytesPerFrame = ma_get_bytes_per_frame(pDecoder->outputFormat, pDecoder->outputChannels);
        memset((ma_uint8*)pOutput + (framesRead * bytesPerFrame), 0, (frameCount - framesRead) * bytesPerFrame);
        g_isPlaying = MA_FALSE;
    }

    (void)pInput; /* Unused in playback mode */
}

int main(int argc, char* argv[])
{
    ma_result result;
    ma_decoder decoder;
    ma_device_config deviceConfig;
    ma_device device;

    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    /* Register Ctrl+C handler for a clean exit */
    signal(SIGINT, sigint_handler);

    printf("Loading file: %s...\n", argv[1]);

    /*
        Initialize the decoder from the input file.
        Passing NULL for the configuration means miniaudio will use the file's
        native audio format, channels, and sample rate.
    */
    result = ma_decoder_init_file(argv[1], NULL, &decoder);
    if (result != MA_SUCCESS) {
        printf("Error: Failed to initialize decoder for file: %s (Error code: %d)\n", argv[1], result);
        return result;
    }

    /* Print source audio file info */
    printf("Format:   %s\n", ma_get_format_name(decoder.outputFormat));
    printf("Channels: %d\n", decoder.outputChannels);
    printf("Rate:     %d Hz\n", decoder.outputSampleRate);

    /*
        Initialize the playback device configuration.
        We configure the device to match the decoder's format, channels, and sample rate.
    */
    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format   = decoder.outputFormat;
    deviceConfig.playback.channels = decoder.outputChannels;
    deviceConfig.sampleRate        = decoder.outputSampleRate;
    deviceConfig.dataCallback      = data_callback;
    deviceConfig.pUserData         = &decoder;

    result = ma_device_init(NULL, &deviceConfig, &device);
    if (result != MA_SUCCESS) {
        printf("Error: Failed to initialize audio playback device. (Error code: %d)\n", result);
        ma_decoder_uninit(&decoder);
        return result;
    }

    /* Start the audio device (starts playback) */
    result = ma_device_start(&device);
    if (result != MA_SUCCESS) {
        printf("Error: Failed to start playback device. (Error code: %d)\n", result);
        ma_device_uninit(&device);
        ma_decoder_uninit(&decoder);
        return result;
    }

    printf("\nPlaying... Press Ctrl+C to stop.\n");

    /* Retrieve audio duration if available */
    ma_uint64 totalFrames = 0;
    ma_bool32 hasLength = MA_FALSE;
    if (ma_decoder_get_length_in_pcm_frames(&decoder, &totalFrames) == MA_SUCCESS && totalFrames > 0) {
        hasLength = MA_TRUE;
    }

    /* Print progress loop */
    while (g_isPlaying) {
        ma_uint64 currentFrame = 0;
        ma_decoder_get_cursor_in_pcm_frames(&decoder, &currentFrame);

        double currentSeconds = (double)currentFrame / decoder.outputSampleRate;
        int currentMin = (int)(currentSeconds / 60);
        int currentSec = (int)(currentSeconds) % 60;

        if (hasLength) {
            double totalSeconds = (double)totalFrames / decoder.outputSampleRate;
            int totalMin = (int)(totalSeconds / 60);
            int totalSec = (int)(totalSeconds) % 60;
            printf("\rProgress: %02d:%02d / %02d:%02d", currentMin, currentSec, totalMin, totalSec);
        } else {
            printf("\rProgress: %02d:%02d / Unknown", currentMin, currentSec);
        }
        fflush(stdout);

        /* Sleep a bit before the next progress update */
        ma_sleep(100);
    }
    printf("\nPlayback finished.\n");

    /* Cleanup resources */
    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);

    return 0;
}

/**
 * Copyright (c) 2010-2012 Julius project team, Nagoya Institute of Technology
 * All rights reserved
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>
#include <pulse/simple.h>
#include <pulse/error.h>


#define BUFSIZE 32

#define RATE 44100

//#define RATE 16000

int16_t buffer[BUFSIZE];

static pa_simple *microphone = NULL;
static pa_simple *playback = NULL;
static char name_buf[] = "PulseAudio default device";

/** 
 * Connection initialization: check connectivity and open for recording.
 * 
 * @param sfreq [in] required sampling frequency
 * @param dummy [in] a dummy data
 * 
 * @return TRUE on success, FALSE on failure.
 */
int adin_pulseaudio_standby(int sfreq, void *dummy)
{
  return 0;
}
 
/** 
 * Start recording.
 * @a pathname is dummy.
 *
 * @param arg [in] argument
 * 
 * @return TRUE on success, FALSE on failure.
 */
int adin_pulseaudio_begin(char *arg)
{
  int error;

  static const pa_sample_spec ss = {
    .format = PA_SAMPLE_FLOAT32LE,
  	.rate = RATE,
  	.channels = 1
  };
  
  if (!(microphone = pa_simple_new(NULL, "Julius", PA_STREAM_RECORD, NULL, "record", &ss, NULL, NULL, &error))) {
    printf("Error: adin_pulseaudio: pa_simple_new() failed: %s\n", pa_strerror(error));
    return 1;
  }
  /* Create a new playback stream */
  if (!(playback = pa_simple_new(NULL, "Caesar", PA_STREAM_PLAYBACK, NULL, "playback", &ss, NULL, NULL, &error))) {
        printf(__FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
    }

  return 0;
}

/** 
 * Stop recording.
 * 
 * @return TRUE on success, FALSE on failure.
 */
int adin_pulseaudio_end()
{
  if (microphone != NULL) {
    pa_simple_free(microphone);
    pa_simple_free(playback);
    microphone = NULL;
    playback = NULL;
  }
  return 0;
}

/**
 * @brief  Read samples from device
 * 
 * Try to read @a sampnum samples and returns actual number of recorded
 * samples currently available.  This function will block until
 * at least one sample was obtained.
 * 
 * @param buf [out] samples obtained in this function
 * @param sampnum [in] wanted number of samples to be read
 * 
 * @return actural number of read samples, -2 if an error occured.
 */
int adin_pulseaudio_read (float *buf, int sampnum)
{
  int error;
  int cnt, bufsize;

  bufsize = sampnum * sizeof(float);
  //if (bufsize > BUFSIZE) bufsize = BUFSIZE;


  if (pa_simple_read(microphone, buf, bufsize, &error) < 0) {
        printf("Error: pa_simple_read() failed: %s\n", pa_strerror(error));
  }

  pa_simple_flush(microphone, &error);

  cnt = bufsize / sizeof(int16_t);
  return (cnt);
}

void microphone_start()
{
    adin_pulseaudio_begin("nothing");
}

void run_microphone(float * buffer, int length)
{

    //int count = 0;
    //for(; count < length; count++)
    //{
        adin_pulseaudio_read(buffer, length);
    //}
}

void run_playback(float * buffer, int length)
{
    int error;
#if 0
        pa_usec_t latency;
        if ((latency = pa_simple_get_latency(playback, &error)) == (pa_usec_t) -1) {
            fprintf(stderr, __FILE__": pa_simple_get_latency() failed: %s\n", pa_strerror(error));
            goto finish;
        }
        fprintf(stderr, "%0.0f usec    \r", (float)latency);
#endif

    if (pa_simple_write(playback, buffer, length, &error) < 0) {
        printf(__FILE__": pa_simple_write() failed: %s\n", pa_strerror(error));
    }
    /* Make sure that every single sample was played */
    if (pa_simple_drain(playback, &error) < 0) {
            printf(__FILE__": pa_simple_drain() failed: %s\n", pa_strerror(error));
    }
}

void microphone_end()
{
    adin_pulseaudio_end();
}

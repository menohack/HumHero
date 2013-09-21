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

#include <fftw.h>


#define BUFSIZE 32

#define RATE 44100

//#define RATE 16000

int16_t buffer[BUFSIZE];

static pa_simple *s = NULL;
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
  
  if (!(s = pa_simple_new(NULL, "Julius", PA_STREAM_RECORD, NULL, "record", &ss, NULL, NULL, &error))) {
    printf("Error: adin_pulseaudio: pa_simple_new() failed: %s\n", pa_strerror(error));
    return 1;
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
  if (s != NULL) {
    pa_simple_free(s);
    s = NULL;
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

  pa_simple_flush(s, &error);
  printf("%d\n", error);
  if (pa_simple_read(s, buf, bufsize, &error) < 0) {
        printf("Error: pa_simple_read() failed: %s\n", pa_strerror(error));
  }
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

void microphone_end()
{
    adin_pulseaudio_end();
}

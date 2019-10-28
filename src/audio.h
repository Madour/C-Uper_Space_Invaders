//
//  sndfile_tutorial
//
//  Created by Matthew Hosack on 11/28/14.
//  Copyright (c) 2014 Matthew Hosack. All rights reserved.
//

#ifndef __AUDIO_H__
#define __AUDIO_H__ value

#include <stdio.h>
#include <string.h>

#include "sndfile.h"
#include "portaudio.h"

#define FRAMES_PER_BUFFER   (512)

typedef struct
{
    SNDFILE     *file;
    SF_INFO      info;
    float 		 volume;
    int*          fade_out;
} callback_data_s;

int callback(const void *input, void *output,
            unsigned long frameCount,
            const PaStreamCallbackTimeInfo* timeInfo,
            PaStreamCallbackFlags statusFlags,
            void *userData
            );


void play_audio(const char* audiofile, PaStream** stream, callback_data_s* data, int* fade_out);
#endif
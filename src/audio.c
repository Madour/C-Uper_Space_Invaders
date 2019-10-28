/*_____________________________________________________
 /                                                     \
| Modar NASSER - Groupe TP2                            |
| TP5 - 22/10/2019                                     |
| Création d'un space invader                          |
|------------------------------------------------------|
| Fichier : audio.c                                    |
|   -> contient des outils pour la lecture d'un        |
|      audio                                           |
|------------------------------------------------------|
| Compilation :                                        |
|   - generation du .o :                               |
|         $ gcc -c audio.c                             |
|                                                      |
\______________________________________________________/

*/
//
//  sndfile_tutorial
//
//  Created by Matthew Hosack on 11/28/14.
//  Copyright (c) 2014 Matthew Hosack. All rights reserved.
//

#include "audio.h"

int
callback
    (const void                     *input
    ,void                           *output
    ,unsigned long                   frameCount
    ,const PaStreamCallbackTimeInfo *timeInfo
    ,PaStreamCallbackFlags           statusFlags
    ,void                           *userData
    )
{
    float           *out;
    callback_data_s *p_data = (callback_data_s*)userData;
    sf_count_t       num_read;

    out = (float*)output;
    p_data = (callback_data_s*)userData;

    /* clear output buffer */
    memset(out, 0, sizeof(float) * frameCount * p_data->info.channels);

    /* read directly into output buffer */
    num_read = sf_read_float(p_data->file, out, frameCount * p_data->info.channels);
    
    if(*(p_data->fade_out) == 1)
    {
        p_data->volume -= 0.0005f;
        if (p_data->volume < 0)
        {
            p_data->volume = 0;
            *(p_data->fade_out) = 0;
        }
    }
    // reglage du volume
    for(int z=0; z < frameCount * p_data->info.channels; z++)
    {
        out[z]*=p_data->volume;
    }
    /*  If we couldn't read a full frameCount of samples we've reached EOF */
    if (num_read < frameCount)
    {
        return paComplete;
    }
    
    return paContinue;
}


void play_audio(const char* audiofile, PaStream** stream, callback_data_s* data, int* fade_out)
{
    data->file = sf_open(audiofile, SFM_READ, &data->info);
    data->volume = 1.f;
    data->fade_out = fade_out;
    Pa_OpenDefaultStream(stream
                        ,0                     // no input 
                        ,data->info.channels         // stereo out 
                        ,paFloat32             // floating point 
                        ,data->info.samplerate
                        ,FRAMES_PER_BUFFER
                        ,callback
                        ,data);        // our sndfile data struct
    // Start the stream
    Pa_StartStream(*stream);
}

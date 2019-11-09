#ifndef __TEXT_H__
#define __TEXT_H__

#include "alphabet.h"

// affiche un message alphanumérique à l'ecran, n'accepte que les lettres majuscules
void displayMessage(char* message, tuple pos, int color);

void displayGameOver(tuple* text_pos);

void displayWaveNum(tuple* wave_text_pos, int* wave_text_speed, t_boss* boss);


#endif

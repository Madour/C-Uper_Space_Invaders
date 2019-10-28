#ifndef __LETERS_H__
#define __LETERS_H__ 

#include <string.h>
#include "affichage.h"
t_sprite spr_space;
t_sprite spr_A;
t_sprite spr_B;
t_sprite spr_C;
t_sprite spr_D;
t_sprite spr_E;
t_sprite spr_F;
t_sprite spr_G;
t_sprite spr_H;
t_sprite spr_I;
t_sprite spr_J;
t_sprite spr_K;
t_sprite spr_L;
t_sprite spr_M;
t_sprite spr_N;
t_sprite spr_O;
t_sprite spr_P;
t_sprite spr_Q;
t_sprite spr_R;
t_sprite spr_S;
t_sprite spr_T;
t_sprite spr_U;
t_sprite spr_V;
t_sprite spr_W;
t_sprite spr_X;
t_sprite spr_Y;
t_sprite spr_Z;

t_sprite spr_0;
t_sprite spr_1;
t_sprite spr_2;
t_sprite spr_3;
t_sprite spr_4;
t_sprite spr_5;
t_sprite spr_6;
t_sprite spr_7;
t_sprite spr_8;
t_sprite spr_9;

t_sprite spr_interrogation;

t_sprite* alphabet[26];
t_sprite* numbers[10];

// affiche un message alphanumérique à l'ecran, n'accepte que les lettres majuscules
void displayMessage(char* message, tuple pos, int color);

#endif
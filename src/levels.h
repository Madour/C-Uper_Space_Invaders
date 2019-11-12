#ifndef __LEVEL_H__
#define __LEVEL_H__
#include "alien.h"
#include "boss.h"


// les informations nécessaires pour chargr un niveau, décrivent les aliens
wave wave_init;
wave wave0;
wave wave1;
wave wave2;
wave wave3;
wave wave4;
wave wave5;
wave wave6;
wave wave7;
wave wave_boss;
wave wave9;

wave* waves_list[MAX_LEVELS];


// permet de charger un niveau et de generer les aliens et boucliers
void load_next_wave(entity alien_list[10][5], entity shields_list[3], t_boss* boss);

#endif
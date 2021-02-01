#ifndef __LEVEL_H__
#define __LEVEL_H__
#include "alien.h"
#include "boss.h"


// les informations nécessaires pour chargr un niveau, décrivent les aliens
extern wave wave_init;
extern wave wave0;
extern wave wave1;
extern wave wave2;
extern wave wave3;
extern wave wave4;
extern wave wave5;
extern wave wave6;
extern wave wave7;
extern wave wave_boss;
extern wave wave9;

extern wave* waves_list[MAX_LEVELS];


// permet de charger un niveau et de generer les aliens et boucliers
void load_next_wave(entity alien_list[10][5], entity shields_list[3], t_boss* boss);

#endif
#ifndef __LEVEL_H__
#define __LEVEL_H__
#include "alien.h"
#include "boss.h"
#include <stdlib.h>
#include <time.h>
#define LEVELS_NB 8
#define MAX_LEVELS 9

// les informations nécessaires pour chargr un niveau, décrivent les aliens
typedef struct 
{
    // informations sur les aliens
    int aliens_rows;
    int shoot_rate;
    int xstep;
    int ystep;
    int glow_chance;

    int boss_id;
    // 1, 2 ou 3 quand il faut deployer les boucliers, 0 sinon
    int has_shields;
    // quand le niveau est terminé, le score augmente
    int score_bonus;
} wave;

wave wave0;
wave wave1;
wave wave2;
wave wave3;
wave wave4;
wave wave5;
wave wave6;
wave wave7;
wave wave_boss;

wave* waves_list[MAX_LEVELS];


// permet de charger un niveau et de generer les aliens et boucliers
void load_wave(wave* curr_wave, int wave_index, entity alien_list[10][5], entity shields_list[3], t_boss* boss);

#endif
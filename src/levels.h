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
} level;

level level0;
level level1;
level level2;
level level3;
level level4;
level level5;
level level6;
level level7;
level level_boss;

level* levels_list[MAX_LEVELS];


// permet de charger un niveau et de generer les aliens et boucliers
void load_level(level* curr_level, int level_index, entity alien_list[10][5], entity shields_list[3], t_boss* boss);

#endif
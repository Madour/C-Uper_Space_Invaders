#ifndef __BOSS_H__
#define __BOSS_H__

#include "sprites.h"


void create_boss(t_boss* boss);

void animBoss(t_boss* boss);

void moveBoss(t_boss* boss);

void doActionBoss(t_boss* boss);

void afficheBoss(t_boss* boss);

int intersect_boss(tuple missile_pos, t_boss* boss);

#endif
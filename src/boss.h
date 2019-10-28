#ifndef __BOSS_H__
#define __BOSS_H__

#include "sprites.h"

#define BOSS_MAX_MISSILE 50


typedef struct 
{
	tuple pos[BOSS_SPRITES_COUNT_Y][BOSS_SPRITES_COUNT_X];
	tuple velocity;
	int direction; // 1 = droite, -1 = gauche
	tuple size;

	int left;
	int right;
	int top;
	int bottom;

	int color;
	int glow_color;

	t_sprite* sprite[BOSS_SPRITES_COUNT_Y][BOSS_SPRITES_COUNT_X];
	t_sprite* glow_sprite[BOSS_SPRITES_COUNT_Y][BOSS_SPRITES_COUNT_X];

	t_sprite* spritesheet[BOSS_SPRITES_COUNT_Y][BOSS_SPRITES_COUNT_X][SHEET_LEN];
	t_sprite* glow_spritesheet[BOSS_SPRITES_COUNT_Y][BOSS_SPRITES_COUNT_X][SHEET_LEN];

	int glowing;

	int frame_nb;
	int compteur;
	int compteur_anim;
	int anim_index;
	int anim_speed;

	int max_missile;
	int missile_count;
	int shoot_chance;
	int missile[BOSS_MAX_MISSILE];
	tuple missile_pos[BOSS_MAX_MISSILE];
	t_sprite* missile_sprite[BOSS_MAX_MISSILE];

	int alive;
	int triggered;
	int ready;

} t_boss;


void create_boss(t_boss* boss);

void animBoss(t_boss* boss);

void moveBoss(t_boss* boss, int player_life);

void doActionBoss(t_boss* boss);

void afficheBoss(t_boss* boss);

int intersect_boss(tuple missile_pos, t_boss* boss);

#endif
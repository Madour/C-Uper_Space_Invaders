#ifndef __SPRITES_H__
#define __SPRITES_H__

#include "window.h"

extern t_sprite missile_sprite;
extern t_sprite impact_sprite;

extern t_sprite heart_sprite;
extern t_spritesheet player_spritesheet;
extern t_spritesheet player_glow_spritesheet;
extern t_spritesheet player_reactor;

extern t_spritesheet alien0_spritesheet;
extern t_spritesheet alien0_glow_spritesheet;

extern t_spritesheet alicen1_spritesheet;
extern t_spritesheet alicen1_glow_spritesheet;

extern t_spritesheet alien2_spritesheet;
extern t_spritesheet alien2_glow_spritesheet;

extern t_spritesheet alien3_spritesheet;
extern t_spritesheet alien3_glow_spritesheet;

extern t_spritesheet shields_spritesheet;

extern t_spritesheet* aliens_spritesheets_list[5];
extern t_spritesheet* aliens_glow_spritesheets_list[5];
extern int aliens_animspeed[5];

extern t_spritesheet boss1_spritesheets[BOSS_SPRITES_COUNT_Y][BOSS_SPRITES_COUNT_X];
extern t_spritesheet boss1_glow_spritesheets[BOSS_SPRITES_COUNT_Y][BOSS_SPRITES_COUNT_X];

#endif
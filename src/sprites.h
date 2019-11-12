#ifndef __SPRITES_H__
#define __SPRITES_H__

#include "window.h"

t_sprite missile_sprite;
t_sprite impact_sprite;

t_sprite heart_sprite;
t_spritesheet player_spritesheet;
t_spritesheet player_glow_spritesheet;
t_spritesheet player_reactor;

t_spritesheet alien0_spritesheet;
t_spritesheet alien0_glow_spritesheet;

t_spritesheet alicen1_spritesheet;
t_spritesheet alicen1_glow_spritesheet;

t_spritesheet alien2_spritesheet;
t_spritesheet alien2_glow_spritesheet;

t_spritesheet alien3_spritesheet;
t_spritesheet alien3_glow_spritesheet;

t_spritesheet shields_spritesheet;

t_spritesheet* aliens_spritesheets_list[5];
t_spritesheet* aliens_glow_spritesheets_list[5];
int aliens_animspeed[5];

t_spritesheet boss1_spritesheets[BOSS_SPRITES_COUNT_Y][BOSS_SPRITES_COUNT_X];
t_spritesheet boss1_glow_spritesheets[BOSS_SPRITES_COUNT_Y][BOSS_SPRITES_COUNT_X];

#endif
#include "boss.h"
#include <stdio.h>
#include <stdlib.h>

void create_boss(t_boss* boss)
{
    boss->size.x = RATIO*SPRITE_X*BOSS_SPRITES_COUNT_X;
    boss->size.y = RATIO*SPRITE_Y*BOSS_SPRITES_COUNT_Y;
    boss->velocity.x = 2;
    boss->velocity.y = 2;
    boss->direction = 1;

    boss->color = BLEU;
    boss->glow_color = BLEU;
    boss->glowing = 0;

    for (int y = 0; y < BOSS_SPRITES_COUNT_Y; ++y)
    {
        for (int x = 0; x < BOSS_SPRITES_COUNT_X; ++x)
        {
            boss->pos[y][x].x = (WIN_W/2) - boss->size.x/2 + x*SPRITE_X*RATIO;
            boss->pos[y][x].y = -boss->size.y + y*SPRITE_Y*RATIO;
            boss->sprite[y][x] = &boss1_spritesheets[y][x][0];
            boss->glow_sprite[y][x] = &boss1_glow_spritesheets[y][x][0];
        }
    }

    boss->left = boss->pos[0][0].x;
    boss->right = boss->pos[0][0].x + boss->size.x;
    boss->top = boss->pos[0][0].y;
    boss->bottom = boss->pos[0][0].y + boss->size.y;


    boss->max_missile = 9;
    boss->missile_count = 0;
    boss->shoot_chance = 4;
    for(int i=0; i< boss->max_missile; i++)
    {
        boss->missile[i] = 0;
        boss->missile_pos[i] = boss->pos[1][0];
    }

    boss->frame_nb = 2;
    boss->anim_index = 0;
    boss->anim_speed = 15;
    boss->compteur_anim = 0;
    boss->compteur = 0;
    boss->alive = 20;
    boss->triggered = 0;
    boss->ready = 0;
}

void afficheBoss(t_boss* boss)
{
    for (int y = 0; y < BOSS_SPRITES_COUNT_Y; ++y)
    {
        for (int x = 0; x < BOSS_SPRITES_COUNT_X; ++x)
        {
            afficheSprite(*boss->sprite[y][x], boss->pos[y][x].x, boss->pos[y][x].y , boss->color);
            if ((boss->compteur_anim % 2)>=1 && boss->glowing)
                afficheSprite(*boss->glow_sprite[y][x], boss->pos[y][x].x, boss->pos[y][x].y , boss->glow_color);
        }
    }
    for (int i = 0; i < boss->max_missile; ++i)
    {
        if (boss->missile[i])
        {
            afficheSprite(missile_sprite, boss->missile_pos[i].x, boss->missile_pos[i].y, ROUGE);
        }
    }
}

void animBoss(t_boss* boss)
{
    if (boss->compteur_anim > boss->anim_speed)
    {
        boss->anim_index = (boss->anim_index+1)%(boss->frame_nb);
        for (int y = 0; y < BOSS_SPRITES_COUNT_Y; ++y)
        {
            for (int x = 0; x < BOSS_SPRITES_COUNT_X; ++x)
            {
                boss->sprite[y][x] = &boss1_spritesheets[y][x][boss->anim_index];
                if (boss->glowing)
                    boss->glow_sprite[y][x] = &boss1_glow_spritesheets[y][x][boss->anim_index];
            }
        }
        boss->compteur_anim = 0;
    }
    boss->compteur_anim+=1;
}

void moveBoss(t_boss* boss, int player_life)
{
    if(!player_life)
        if(boss->pos[0][0].y < WIN_H)
        {
            for (int y = 0; y < BOSS_SPRITES_COUNT_Y; ++y)
                for (int x = 0; x < BOSS_SPRITES_COUNT_X; ++x)
                    boss->pos[y][x].y += boss->velocity.y*4;
        }

    if (boss->triggered)
    {
        // mouvement du boss
        if(player_life)
            for (int y = 0; y < BOSS_SPRITES_COUNT_Y; ++y)
                for (int x = 0; x < BOSS_SPRITES_COUNT_X; ++x)
                    boss->pos[y][x].x += boss->velocity.x*boss->direction;

        boss->left = boss->pos[0][0].x;
        boss->right = boss->pos[0][0].x+boss->size.x;
        boss->top = boss->pos[0][0].y;
        boss->bottom = boss->pos[0][0].y+boss->size.y;

        if (boss->right >= RIGHT_BOUNDARY || boss->left <= LEFT_BOUNDARY)
            boss->direction = -boss->direction;

        // mouvement des missiles du boss
        for(int i = 0; i<boss->max_missile; i++){
            if (boss->missile[i])
            {
                if (boss->missile_pos[i].y >= WIN_H)
                {
                    boss->missile[i] = 0;
                    boss->missile_pos[i] = boss->pos[1][1];
                }
                boss->missile_pos[i].y += 26;
            }
            else
            {
                boss->missile_pos[i] = boss->pos[1][1];
            }
        }

    }
    else
    {
        if(boss->pos[0][0].y < 100)
        {
            for (int y = 0; y < BOSS_SPRITES_COUNT_Y; ++y)
                for (int x = 0; x < BOSS_SPRITES_COUNT_X; ++x)
                    boss->pos[y][x].y += boss->velocity.y;

            boss->left = boss->pos[0][0].x;
            boss->right = boss->pos[0][0].x+boss->size.x;
            boss->top = boss->pos[0][0].y;
            boss->bottom = boss->pos[0][0].y+boss->size.y;
        }
        else
            boss->ready = 1;
    }
}

void doActionBoss(t_boss* boss)
{
    for (int i = 0; i < boss->max_missile; ++i)
    {
        if(!(boss->missile[i]) && !(boss->missile[i-1]))
        {
            if(rand()%100 < boss->shoot_chance && boss->missile_count < boss->max_missile)
            {
                int tmp = rand()%3;
                while(tmp == 1) tmp = rand()%3;
                boss->missile[i] = 1;
                boss->missile_pos[i] = boss->pos[1][tmp];
            }
        }
    }
}

int intersect_boss(tuple missile_pos, t_boss* target){
    // condition sur les y
    if (target->top <= missile_pos.y+2*RATIO && missile_pos.y <= target->bottom)
    {
        // condition sur les x
        if (target->left <= missile_pos.x+5*RATIO && missile_pos.x+6*RATIO <= target->right)
        {
            return 1;
        }
    }
    return 0;
}


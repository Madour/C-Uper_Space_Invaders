#ifndef __TYPEDEFS_H__
#define __TYPEDEFS_H__

#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/* Définition d'un sprite
un sprite est définie par un tableau de 0 et de 1.
Les sprites sont de taille fixe (ici 11x8) et en une seule couleur */
#define SPRITE_X 11
#define SPRITE_Y 8
#define SHEET_LEN 5 // taille maximum d'une feuille de sprite
#define BOSS_SPRITES_COUNT_X 3
#define BOSS_SPRITES_COUNT_Y 2
#define BOSS_MAX_MISSILE 50

#define PLAYER_MAX_MISSILE 10

#define INPUT_SIZE 4

#define FAKE_END 7
#define FIRST_END 8
#define MAX_LEVELS 10

// type tuple, pour stocker des coordonnés de position entre autre
typedef struct
{
    int x;
    int y;
} tuple;

typedef int t_sprite[SPRITE_Y][SPRITE_X];

typedef int t_spritesheet[SHEET_LEN][SPRITE_Y][SPRITE_X];

typedef struct
{
    int index;
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

typedef struct {
    int width;
    int height;
    int is_open;
    int update_rate;
    int input_list[2][INPUT_SIZE];
    int players_nb;
    wave* current_wave;
    int finished_game;
    int show_wave_nb;
    int paused;
    int game_over;
    int background_scroll_speed;
    int counter;
} new_game;

// type entity, contient toute les informations nécessaire à
// la manipulation des aliens et du joueur
typedef struct
{
    char type; // PLAYER ou ALIEN
    int id; // identitfiant de l'entité, utile pour differencier les aliens

    tuple pos;
    tuple velocity;
    tuple size; // taille du sprite (fixée dans ce projet)

    int color; // la couleur du sprite
    int missile_color;

    t_sprite* sprite;          // sprite qui sera affiché
    t_sprite* glow_sprite;     // sprite de la lueur autour de l'entité

    t_sprite* spritesheet[SHEET_LEN];      // feuille de sprite principale
    t_sprite* glow_spritesheet[SHEET_LEN]; // feuille de sprite de la lueur

    // vaut 1 si il faut afficher une leur, vaut 0 par défaut
    int glowing;

    // permet de définir les positions des contours externes de l'entité
    int left;
    int right;
    int top;
    int bottom;

    // divers compteurs pour l'animation
    int frame_nb;
    int compteur;
    int compteur_anim;
    int anim_index;
    int anim_speed;

    // information pour le missile
    int shoot_rate;
    int max_missile;
    int missile_count;
    tuple missile_pos[PLAYER_MAX_MISSILE];
    int missile[PLAYER_MAX_MISSILE];
    t_sprite* missile_sprite[PLAYER_MAX_MISSILE];

    // les points de vie de l'entité
    int alive;
} entity;



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

#endif

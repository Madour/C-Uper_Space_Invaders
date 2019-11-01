#ifndef __ENTITIES_H__
#define __ENTITIES_H__ 

#include "sprites.h"


#define PLAYER 0
#define ALIEN 1


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
    tuple missile_pos;
    int missile;
    t_sprite* missile_sprite;

    // les points de vie de l'entité
    int alive;


} entity;

// créé l'entité entity en fonction des arguments donnés
void create_player(entity* entity, tuple pos);

// créé un shield tout simplement
void create_shield(entity* shield, tuple pos);

// anime l'entité
void animEntity(entity *entity, int animspeed);

// déplace l'entité selon les input, et la vitesse de déplacement en x
void moveEntity(entity *entity, int input, int xstep);

// renvoie 1 si le tuple missile_pos est en intersection avec 
// le sprite de l'entité
int intersect(tuple missile_pos, entity* target);

#endif
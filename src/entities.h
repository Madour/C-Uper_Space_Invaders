#ifndef __ENTITIES_H__
#define __ENTITIES_H__ 

#include "sprites.h"

#define PLAYER 0
#define ALIEN 1

// créé l'entité entity en fonction des arguments donnés
void create_player(entity* entity, tuple pos);

// créé un shield tout simplement
void create_shield(entity* shield, tuple pos);

// anime l'entité
void animEntity(entity *entity, int animspeed);

// fait shooter une entity
void entityShoot(entity *entity);

// déplace l'entité selon les input, et la vitesse de déplacement en x
void moveEntity(entity *entity, int input, int xstep);

// affiche une entitée à l'écran
void drawEntity(entity *entity);

// draws an entity's missiles that are shoot
void drawEntityMissiles(entity *entity);

// renvoie 1 si le tuple missile_pos est en intersection avec 
// le sprite de l'entité
int intersect(tuple missile_pos, entity* target);

#endif
#ifndef __ALIEN_H__
#define __ALIEN_H__

#include "entities.h"

// t_alien et entity partagent les memes champs, c'est des types synonymes
typedef entity t_alien;

// permet de créer alien passé en parametre a partir d'une position et d'un identifiant (pour déterminer le sprite)
void create_alien(t_alien* alien, tuple pos, int id);

// gère le déplacement des alien
// xstep : vitesse en x, ystep : vitesse en y,
// side : 1 = gauche, 2 = droite
void deplacerAlien(t_alien* alien, int xstep, int ystep, int side);

#endif
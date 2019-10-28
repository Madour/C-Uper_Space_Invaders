/*_____________________________________________________
 /                                                     \
| Modar NASSER - Groupe TP2                            |
| TP5 - 21/10/2019                                     |
| Création d'un space invader                          |
|------------------------------------------------------|
| Fichier : alien.c                                    |
|   -> create_alien  créé un alien a partir de la pos  |
|                    et d'un id                        |
|   -> deplacerAlien gère le déplacement des aliens    |
|------------------------------------------------------|
| Compilation :                                        |
|   - generation du .o :                               |
|   	  $ gcc -c alien.c                             |
|                                                      |
\______________________________________________________/

*/


#include "alien.h"
#include <stdio.h>

void create_alien(t_alien* entity, tuple pos, int id) //t_spritesheet spritesheet)
{
	entity->type = ALIEN;
	entity->id = id;
	entity->size.x = RATIO*SPRITE_X;
	entity->size.y = RATIO*SPRITE_Y;

	entity->pos = pos;
	entity->frame_nb = 2;

	// on copie la spritesheet dans le champ de l'alien
	for (int i = 0; i < entity->frame_nb; ++i)
		entity->spritesheet[i] = &(*aliens_spritesheets_list[id])[i];

	entity->sprite = entity->spritesheet[0];
	
	// on fait de meme pour les sprite de la lueur
	for (int i = 0; i < entity->frame_nb; ++i)
		entity->glow_spritesheet[i] = &(*aliens_glow_spritesheets_list[id])[i];

	entity->glow_sprite = entity->glow_spritesheet[0];

	entity->glowing = 0;

	entity->missile = 0;
	entity->missile_pos = pos;
	entity->missile_sprite = &missile_sprite;
	
	entity->left = pos.x;
	entity->right = pos.x+entity->size.x;
	entity->top = pos.y;
	entity->bottom = pos.y+entity->size.y;

	entity->anim_index = 0;
	entity->anim_speed = 10;
	entity->compteur_anim = 0;
	entity->compteur = 0;
	entity->alive = 1;

}

void deplacerAlien(t_alien* alien, int xstep, int ystep, int side){
	// deplacer a droite
	// formule : (deplacement en X - 2) * nombre d'alien sur une ligne
	if (alien->compteur < 25 - (xstep-2)*4)
	{
		moveEntity(alien, 2, xstep);
	}
	else if (alien->compteur == 25 - (xstep-2)*4 && side == 1)
	{
		alien->pos.y += ystep;
	}
	// deplacer a gauche
	else if (alien->compteur > 25 - (xstep-2)*4)
	{
		moveEntity(alien, 1, xstep);
	}
	
	if (alien->compteur >= 50 - 2*(xstep-2)*4)
	{	
		if (side == 2)
		{
			alien->pos.y += ystep;
		}
		alien->compteur = 0;
	}
	else
		alien->compteur +=1;
}
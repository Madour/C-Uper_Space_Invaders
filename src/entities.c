/*_____________________________________________________
 /                                                     \
| Modar NASSER - Groupe TP2                            |
| TP5 - 21/10/2019                                     |
| Création d'un space invader                          |
|------------------------------------------------------|
| Fichier : entities.c                                 |
|   -> Contient la déscription des entités,            |
|      ce sont les aliens et le joueur                 |
|   -> fonctions permettant de manipuler les entités   |
|------------------------------------------------------|
| Compilation :                                        |
|   - generation du .o :                               |
|   	  $ gcc -c entities.c                          |
|                                                      |
\______________________________________________________/

*/

#include "entities.h"
#include <stdio.h>

void create_player(entity* entity, tuple pos)
{
    entity->type = PLAYER;
    entity->size.x = RATIO*SPRITE_X;
    entity->size.y = RATIO*SPRITE_Y;

    entity->pos = pos;
    entity->velocity.x = 3*RATIO;
    entity->velocity.y = 0;
    entity->frame_nb = 2;

    entity->sprite = &player_spritesheet[0];
    for (int i = 0; i < entity->frame_nb; ++i)
    {
        entity->spritesheet[i] = &player_spritesheet[i];
    }

    for (int i = 0; i < entity->frame_nb; ++i)
    {
        entity->glow_spritesheet[i] = &player_glow_spritesheet[i];
    }
    entity->glow_sprite = &player_glow_spritesheet[0];
    entity->glowing = 1;

    // pour augmenter la difficulté,le joueur ne pourra utiliser
    // qu'un missile a la foi, ça évitera les comportement de type
    // "spamer le bouton espace"
    entity->missile = 0;
    entity->missile_pos = pos;
    entity->missile_sprite = &missile_sprite;

    entity->left = pos.x;
    entity->right = pos.x+entity->size.x;
    entity->top = pos.y;
    entity->bottom = pos.y+entity->size.y;

    entity->anim_index = 0;
    entity->anim_speed = 15;
    entity->compteur_anim = 0;
    entity->compteur = 0;
    entity->alive = 10;
}


void create_shield(entity* shield, tuple pos)
{
    shield->size.x = RATIO*SPRITE_X;
    shield->size.y = RATIO*SPRITE_Y;
    shield->pos = pos;

    shield->left = pos.x;
    shield->right = pos.x+shield->size.x;
    shield->top = pos.y;
    shield->bottom = pos.y+shield->size.y;

    shield->frame_nb = 3;
    shield->sprite = &shields_spritesheet[0];

    shield->alive = 4;

}

void moveEntity(entity *entity, int input, int xstep)
{
    int step_x = 0, step_y = 0;

    // on teste les input
    if (input == 1)
    {
        step_x -= xstep;
    }
    else if (input == 2)
    {
        step_x += xstep;
    }
    else if(input == 3)
    {
        entity->missile = 1;
    }

    entity->pos.x += step_x;
    entity->pos.y += step_y;

    if(entity->type == PLAYER)
    {
        // si le sprite sort des limites, on l'empeche de dépasser
        if (entity->pos.x + entity->size.x >= RIGHT_BOUNDARY)
        {
            entity->pos.x = RIGHT_BOUNDARY - entity->size.x;
        }
        else if (entity->pos.x <= LEFT_BOUNDARY)
        {
            entity->pos.x = LEFT_BOUNDARY;
        }
    }

    // on met a jour les global_bounds du sprite
    entity->left = entity->pos.x;
    entity->right = entity->pos.x+entity->size.x;
    entity->top = entity->pos.y;
    entity->bottom = entity->pos.y+entity->size.y;


    // mise a jour des pos du missile s'il existe
    if (entity->missile)
    {
        if (entity->type == PLAYER)
        {
            if (entity->missile_pos.y <= 20)
            {
                entity->missile = 0;
                entity->missile_pos = entity->pos;
            }
            entity->missile_pos.y -= 25;
        }
        else if(entity->type == ALIEN)
        {
            if (entity->missile_pos.y >= 560)
            {
                entity->missile = 0;
                entity->missile_pos = entity->pos;
            }
            entity->missile_pos.y += 20;
        }

    }
    else{
        entity->missile_pos.x = entity->pos.x;
        entity->missile_pos.y = entity->pos.y;
    }
}

void animEntity(entity *entity, int animspeed)
{
    if (entity->compteur_anim > animspeed)
    {
        entity->anim_index = (entity->anim_index+1)%(entity->frame_nb);
        entity->sprite = entity->spritesheet[entity->anim_index];
        entity->compteur_anim = 0;
        if(entity->glowing)
        {
            entity->glow_sprite = entity->glow_spritesheet[entity->anim_index];
        }
    }
    entity->compteur_anim+=1;
}

int intersect(tuple missile_pos, entity* target){
    // condition sur les y
    if( (target->top <= missile_pos.y+2*RATIO && missile_pos.y+2*RATIO <= target->bottom) ||
        (target->top <= missile_pos.y+6*RATIO && missile_pos.y+6*RATIO <= target->bottom)
    )
    {
        // condition sur les x
        if( (target->left <= missile_pos.x+5*RATIO+RATIO/2 && missile_pos.x+5*RATIO+RATIO/2 <= target->right) ||
            (target->left <= missile_pos.x+6*RATIO-RATIO/2 && missile_pos.x+6*RATIO-RATIO/2 <= target->right)
        )
        {
            return 1;
        }
    }
    return 0;
}


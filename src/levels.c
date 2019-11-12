/*_____________________________________________________
 /                                                     \
| Modar NASSER - Groupe TP2                            |
| TP5 - 23/10/2019                                     |
| Création d'un space invader                          |
|------------------------------------------------------|
| Fichier : levels.c                                   |
|   -> Contient la déscription des niveaux             |
|   -> load_wave permet de charger un niveau           |
|      a partir du main.c                              |
|------------------------------------------------------|
| Compilation :                                        |
|   - generation du .o :                               |
|         $ gcc -c levels.c                            |
|                                                      |
\______________________________________________________/

*/

#include "levels.h"

wave wave_init = {
        .index = -1,
        .aliens_rows = 0,
        .shoot_rate = 0,
        .xstep = 0,
        .ystep = 0,
        .glow_chance = 0,
        .boss_id = 0,
        .has_shields = 0,
        .score_bonus = 0
};

wave wave0 = {
        .index = 0,
        .aliens_rows = 1,
        .shoot_rate = 180,
        .xstep = 1,
        .ystep = 5,
        .glow_chance = 0,
        .boss_id = 0,
        .has_shields = 0,
        .score_bonus = 10
};

wave wave1 = {
        .index = 1,
        .aliens_rows = 2,
        .shoot_rate = 200,
        .xstep = 2,
        .ystep = 10,
        .glow_chance = 0,
        .boss_id = 0,
        .has_shields = 0,
        .score_bonus = 20

};

wave wave2 = {
        .index = 2,
        .aliens_rows = 3,
        .shoot_rate = 180,
        .xstep = 2,
        .ystep = 12,
        .glow_chance = 0,
        .boss_id = 0,
        .has_shields = 0,
        .score_bonus = 25
};

wave wave3 = {
        .index = 3,
        .aliens_rows = 3,
        .shoot_rate = 160,
        .xstep = 3,
        .ystep = 16,
        .glow_chance = 0,
        .boss_id = 0,
        .has_shields = 3,
        .score_bonus = 30
};

wave wave4 = {
        .index = 4,
        .aliens_rows = 5,
        .shoot_rate = 180,
        .xstep = 4,
        .ystep = 18,
        .glow_chance = 0,
        .boss_id = 0,
        .has_shields = 1,
        .score_bonus = 50
};

wave wave5 = {
        .index = 5,
        .aliens_rows = 2,
        .shoot_rate = 60,
        .xstep = 5,
        .ystep = 24,
        .glow_chance = 5,
        .boss_id = 0,
        .has_shields = 2,
        .score_bonus = 50
};

wave wave6 = {
        .index = 6,
        .aliens_rows = 4,
        .shoot_rate = 150,
        .xstep = 3,
        .ystep = 20,
        .glow_chance = 20,
        .boss_id = 0,
        .has_shields = 3,
        .score_bonus = 70
};

wave wave7 = {
        .index = 7,
        .aliens_rows = 4,
        .shoot_rate = 150,
        .xstep = 3,
        .ystep = 20,
        .glow_chance = 101,
        .boss_id = 0,
        .has_shields = 2,
        .score_bonus = 100
};

wave wave_boss = {
        .index = 8,
        .aliens_rows = 0,
        .shoot_rate = 150,
        .xstep = 3,
        .ystep = 20,
        .glow_chance = 0,
        .boss_id = 1,
        .has_shields = 0,
        .score_bonus = 300
};

wave wave9 = {
        .index = 9,
        .aliens_rows = 1,
        .shoot_rate = 150,
        .xstep = 3,
        .ystep = 20,
        .glow_chance = 1,
        .boss_id = 0,
        .has_shields = 2,
        .score_bonus = 100
};

wave* waves_list[MAX_LEVELS] = {&wave0, &wave1, &wave2, &wave3, &wave4, &wave5, &wave6, &wave7, &wave_boss, &wave9};

void load_next_wave(entity alien_list[10][5], entity shields_list[3], t_boss* boss)
{
    game.current_wave = waves_list[game.current_wave->index + 1];
    int tmp, line_color, prev_line_color;

    //on créé les bouclier si le niveau les recquiere
    if(game.current_wave->has_shields)
        for (int i = 0; i < 3; ++i)
            if(!(i==1 && game.current_wave->has_shields == 2) &&
                !((i==0 && game.current_wave->has_shields == 1) ||
                (i==2 && game.current_wave->has_shields == 1))
            )
            {
                entity shield;
                shield.alive = 3;
                tuple pos = {.x= 85+i*95, .y=460};
                shield.pos = pos;
                create_shield(&shield, pos);
                shields_list[i] = shield;
            }

        // CREATION DES ALIENS
    for (int i = 0; i < game.current_wave->aliens_rows; ++i)
    {
        line_color = rand()%6+2;
        while(line_color == prev_line_color)
            line_color = rand()%6+2;
        prev_line_color = line_color;

        for (int j = 0; j < 5; ++j)
        {
            entity alien;

            tuple pos;
            pos.x = j*(SPRITE_X+2)*RATIO+60;
            pos.y = i*(SPRITE_Y+4)*RATIO+30;

            // randomise le choix du prochain alien créé
            tmp = rand()%3;
            if(game.current_wave->index >= 5)
                tmp = rand()%4;
            create_alien(&alien, pos, tmp);

            alien.color = line_color;

            alien.compteur = 50-2*(game.current_wave->xstep-2)*4;

            // si le niveau est 3 ou plus, les aliens peuvent avoir jusqu'a 3 PV
            if(game.current_wave->index>=3)
            {
                tmp = rand()%2+1;
                alien.alive = tmp;

                // au debut du niveau 3, tout les aliens tirent
                if(game.current_wave->index == 3)
                    alien.missile[0] = 1;
            }
            else
                alien.alive = 1;

            // on teste si l'alien sera clignotant ou pas
            tmp = rand()%100;
            if(tmp<game.current_wave->glow_chance)
            {
                alien.glowing = 1;

                // l'alien clignotant peut avoir jusqu'a 5 points de vie !
                tmp = rand()%2+3;
                alien.alive = tmp;
            }

            if(i%2)
            {
                alien.compteur = 25-(game.current_wave->xstep-2)*4;
                alien.pos.x += 40;
            }

            alien.compteur_anim = rand()%10;
            alien.type = ALIEN;

            alien_list[i][j] = alien;
        }
    }

    // definition spéciale pour le niveau 4, ce qui le rendra plus dur
    if(game.current_wave->index==4)
    {
        // premiere ligne
        for (int j = 0; j < 5; ++j)
        {
            entity alien;
            tuple pos;
            pos.x = j*(SPRITE_X+2)*RATIO+60;
            pos.y = 0*(SPRITE_Y+4)*RATIO+30;

            create_alien(&alien, pos, 3);
            alien.color = BLACK;

            alien.anim_speed = aliens_animspeed[alien.id];

            tmp = rand()%2+1;
            alien.alive = tmp;
            alien.glowing = 1;

            alien.compteur = 25-(game.current_wave->xstep-2)*4;
            alien.pos.x += 40;

            alien.compteur_anim = rand()%10;

            alien_list[0][j] = alien;
        }
        // derniere ligne
        for (int j = 0; j < 5; ++j)
        {
            entity alien;

            tuple pos;
            pos.x = j*(SPRITE_X+2)*RATIO+60;
            pos.y = (game.current_wave->aliens_rows-1)*(SPRITE_Y+4)*RATIO+30;

            create_alien(&alien, pos, 2);
            alien.color = DARKGREY;

            alien.glowing = 1;

            alien.anim_speed = aliens_animspeed[alien.id];
            alien.compteur = 50-2*(game.current_wave->xstep-2)*4;

            alien.alive = 3;

            if((game.current_wave->aliens_rows-1)%2)
            {
                alien.compteur = 25-(game.current_wave->xstep-2)*4;
                alien.pos.x += 40;
            }


            alien_list[game.current_wave->aliens_rows-1][j] = alien;
        }
    }

    if (game.current_wave->boss_id)
    {
        create_boss(boss);
    }
}	






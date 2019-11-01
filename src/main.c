/*_____________________________________________________
 /                                                     \
| Modar NASSER - Groupe TP2                            |
| TP5 - 21/10/2019                                     |
| Création d'un space invader                          |
|------------------------------------------------------|
| Fichier : main.c                                     |
|   -> Contient la boucle principale du jeu            |
|   -> Gestion des inputs                              |
|   -> Déplacement et animation des entitées           |
|   -> Affichage des textes et score                   |
|   -> Lecture du fichier audio                        |
|------------------------------------------------------|
| Compilation :                                        |
|   - generation du .o :                               |
|   	  $ gcc -c main.c                              |
|   - generation de l'éxecutable:                      |
|       $gcc -o space main.o affichage.o alien.o       |
|           entities.o levels.o sprites.o audio.o      |
|           alphabet.o -lX11 -lSDL2_mixer              |
|                                                      |
\______________________________________________________/

*/
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boss.h"
#include "levels.h"
#include "alphabet.h"

int main(int argc, char const *argv[])
{
    // #### VARIABLES INITIALIZATION ####
    srand(time(NULL));
    int killed_aliens = 0;              // number of dead aliens in the last row
    int score = 0;                      // stores player score
    int wave_index = 0;                 // number of the current wave
    int load_next_wave = 0;             // equals 1 when no aliens remaining
    int show_wave_nb = 1;               // set to 1 at the start of each wave
    int wave_text_speed = 40;           // speed of the "Wave X" text animation
    int finished_game = 0;              // equals 1 when all levels are won
    int game_over = 0;                  // equals 1 when player 1 or player 2 are dead
    int timer = 0;                      // timer used in cut scenes as a "clock"
    int cutscene_state = 0;             // used to track cut scene progression
    int background_scroll_speed = 2;    // background scroll speed for a nice visual effect
    int tmp=0;
    time_t frame_time = clock();

    wave current_wave;                  // contains information about the current wave
    entity alien_list[10][5];           // aliens array
    entity shields_list[3];             // shield list
    t_boss boss;                        // will be set if current wave has a boss
    entity player, player2;             // declaring players entities
    entity* players[2];

    // defining some positions for entities and texts
    tuple tmp_pos={.x=0,.y=0};
    tuple player_pos = {.x=181, .y=500};
    tuple game_over_pos = {.x=150, .y=-100};
    tuple thank_you_pos = {.x=70, .y=350};
    tuple wave_text_pos = {.x=400, .y=295};
    tuple end_text_pos = {.x=90, .y=250};

    // HUD positions
    tuple hearts_pos1 = {.x=8*RATIO, .y=WIN_H -14*RATIO};
    tuple hearts_pos2 = {.x=8*RATIO*6, .y=WIN_H -14*RATIO};
    tuple score_text_pos = {.x=300, .y=10};

    char msg[20];                       // used to store temporary displayed messages
    char user_name[11];                 // user will be prompted their name when they exit
    FILE* score_file;                   // highscores.txt


    // Bloc Lecture du fichier audio
    const char* audiofile = "assets/bgm.ogg";
    int volume = 128;
    int audio_fade_out = 0;
    printf("initialisation audio ...\n");
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    printf("terminé.\n");
    Mix_Music* bgm = Mix_LoadMUS(audiofile);
    Mix_PlayMusic(bgm, -1);
    // fin de lecture

    // if user tries to select a level :
    if (argc > 1) {
        if (*argv[1] - '0' < LEVELS_NB + 1)
            wave_index = *argv[1] - '0';
        else {
            printf("Niveau %d n'existe pas.\n", *argv[1] - '0');
            wave_index = 0;
        }
    }
    tuple hearts_pos = {.x=8*RATIO, .y=WIN_H -14*RATIO};

    // creating player entity
    create_player(&player, player_pos);
    player.color = ROUGE;
    create_player(&player2, player_pos);
    player2.color = VERT;

    players[0] = &player;
    players[1] = &player2;

    // loading first wave
    load_wave(&current_wave, wave_index, alien_list, shields_list, &boss);

    if(initAffichage(WIN_W, WIN_H) == -1)
    {
        printf("Erreur lors de l'initialisation graphique\n");
        return 0;
    }

    // ##### DEBUT BOUCLE PRINCIPALE DU JEU #####
    while(game.is_open)
    {

        defilerFond(0, background_scroll_speed);

        if (audio_fade_out)
            Mix_VolumeMusic(--volume);

        // si le niveau possede des boucliers on les affiche
        if (current_wave.has_shields)
            for (int i = 0; i < 3; ++i)
                if (shields_list[i].alive)
                    afficheSprite(*shields_list[i].sprite, shields_list[i].left, shields_list[i].top, GRISCLAIR);

        // si joueur en vie, on affiche son sprite, le missile et les coeurs
        for (int p = 0; p < game.players_nb; ++p) {
            if (players[p]->alive) {
                // affichage des sprites du joueur (flame du reacteur et le vaisseau)
                tmp = (players[p]->compteur_anim % 6 >= 3 ? 1 : 0);
                if (!finished_game)
                    afficheSprite(player_reactor[tmp], players[p]->pos.x, players[p]->pos.y + 5 * RATIO, BLANC);
                afficheSprite(*players[p]->sprite, players[p]->pos.x, players[p]->pos.y, players[p]->color);

                // un clignotement indicateur de l'etat de santé du vaisseau, devient
                // plus frequent quand peu de point de vie restant
                if (players[p]->glowing) {
                    if (players[p]->alive == 1) {
                        if (players[p]->compteur_anim % 2 == 0)
                            afficheSprite(*players[p]->glow_sprite, players[p]->pos.x, players[p]->pos.y, BLANC);
                    } else if (players[p]->alive <= 3) {
                        if (players[p]->compteur_anim % 4 == 0)
                            afficheSprite(*players[p]->glow_sprite, players[p]->pos.x, players[p]->pos.y, BLANC);
                    } else if (players[p]->alive <= 5) {
                        if (players[p]->compteur_anim % 6 == 0)
                            afficheSprite(*players[p]->glow_sprite, players[p]->pos.x, players[p]->pos.y, BLANC);
                    }
                }
                // affichage du missile s'il a été tiré
                if (players[p]->missile)
                    afficheSprite(*players[p]->missile_sprite, players[p]->missile_pos.x, players[p]->missile_pos.y, JAUNE);

                // test collision entre le missile du joueur et les boucliers
                if (current_wave.has_shields)
                    for (int s = 0; s < 3; ++s)
                        if (intersect(players[p]->missile_pos, &shields_list[s]) && shields_list[s].alive) {
                            if (shields_list[s].alive) {
                                shields_list[s].alive -= 1;
                                shields_list[s].sprite++;
                            }
                            afficheSprite(impact_sprite, shields_list[s].pos.x, shields_list[s].pos.y, BLANC);
                            players[p]->missile = 0;
                            players[p]->missile_pos = players[p]->pos;
                        }
            }
                // si joueur est mort , on commence le slow motion
            else {
                displayMessage("GAME", game_over_pos, ROUGE);
                game_over_pos.y += 40;
                displayMessage("OVER", game_over_pos, ROUGE);
                game_over_pos.y -= 40;
                if (game_over_pos.y < 70)
                    game_over_pos.y += 4;
                if (game.update_rate < 300)
                    game.update_rate += 2;
            }
        }


        // #### BOUCLE ALIENS ####
        // boucle qui gère les interactions pour chaque alien
        for (int i = 0; i < current_wave.aliens_rows; i++) {
            for (int j = 0; j < 5; ++j) {
                if (alien_list[i][j].missile) {
                    //si un missile alien touche le joueur, on enleve un coeur au joueur
                    for (int p = 0; p < game.players_nb; ++p) {
                        if (intersect(alien_list[i][j].missile_pos, players[p]) && players[p]->alive) {
                            if (players[p]->alive)
                                players[p]->alive -= 1;
                            score = (alien_list[i][j].glowing ? score - 10 : score - 5);
                            score = (score < 0 ? 0 : score);
                            afficheSprite(impact_sprite, players[p]->pos.x, players[p]->pos.y, BLANC);
                            alien_list[i][j].missile = 0;
                            alien_list[i][j].missile_pos = alien_list[i][j].pos;
                        }
                    }

                    //si un missile alien touche un bouclier, on lui enleve une vie
                    if (current_wave.has_shields)
                        for (int s = 0; s < 3; ++s)
                            if (intersect(alien_list[i][j].missile_pos, &shields_list[s]) &&
                                shields_list[s].alive) {
                                if (shields_list[s].alive) {
                                    shields_list[s].alive -= 1;
                                    shields_list[s].sprite++;
                                }
                                afficheSprite(impact_sprite, shields_list[s].pos.x, shields_list[s].pos.y, BLANC);
                                alien_list[i][j].missile = 0;
                                alien_list[i][j].missile_pos = alien_list[i][j].pos;
                            }

                    // affichage du missile alien
                    if (player.alive)
                        afficheSprite(*alien_list[i][j].missile_sprite, alien_list[i][j].missile_pos.x,
                                      alien_list[i][j].missile_pos.y, ORANGE);
                    else
                        afficheSprite(*alien_list[i][j].missile_sprite, alien_list[i][j].missile_pos.x,
                                      alien_list[i][j].missile_pos.y, GRISCLAIR);
                }

                if (alien_list[i][j].alive) {
                    // si les aliens sont arrivé au bord bas, le joueur a perdu
                    if (i == current_wave.aliens_rows - 1)
                        if (alien_list[i][j].pos.y + alien_list[i][j].size.y >= player.pos.y - 4)
                            player.alive = 0;

                    // si le missile du joueur touche un alien
                    for (int p = 0; p < game.players_nb; ++p) {
                        if (intersect(players[p]->missile_pos, &alien_list[i][j])) {
                            if (alien_list[i][j].alive)
                                alien_list[i][j].alive -= 1;

                            score = (alien_list[i][j].glowing ? score + 10 : score + 5);
                            afficheSprite(impact_sprite, alien_list[i][j].pos.x, alien_list[i][j].pos.y, BLANC);
                            players[p]->missile = 0;
                            players[p]->missile_pos = players[p]->pos;
                        }
                    }


                    if (alien_list[i][j].alive) {
                        // on décide si l'alien doit tirer
                        tmp = rand() % current_wave.shoot_rate;
                        if (tmp == 1 && alien_list[i][j].missile == 0)
                            alien_list[i][j].missile = 1;

                        animEntity(&alien_list[i][j], alien_list[i][j].anim_speed);

                        // si le joueur est en vie, on affiche les aliens en couleur
                        if (player.alive) {
                            afficheSprite(*alien_list[i][j].sprite, alien_list[i][j].pos.x, alien_list[i][j].pos.y,
                                          alien_list[i][j].color);
                            if (alien_list[i][j].compteur_anim % 3 == 0 && alien_list[i][j].glowing)
                                afficheSprite(*alien_list[i][j].glow_sprite, alien_list[i][j].pos.x,
                                              alien_list[i][j].pos.y, BLANC);
                        }
                            // sinon, on affiche en gris
                        else {
                            afficheSprite(*alien_list[i][j].sprite, alien_list[i][j].pos.x, alien_list[i][j].pos.y,
                                          GRISFONCE);
                            if (alien_list[i][j].compteur_anim % 3 == 0 && alien_list[i][j].glowing)
                                afficheSprite(*alien_list[i][j].glow_sprite, alien_list[i][j].pos.x,
                                              alien_list[i][j].pos.y, GRISCLAIR);
                        }
                    }
                } else
                    killed_aliens += 1;

                // on deplace les aliens en décalés (ligne pair vers la gauche et impair vers la droite)
                tmp = 2;
                if (i % 2)
                    tmp = 1;
                deplacerAlien(&alien_list[i][j], current_wave.xstep, current_wave.ystep, tmp);

            }
            // si tout les aliens de la derniere lignes sont mort, on decremente le nombre de ligne d'aliens
            if (i == (current_wave.aliens_rows - 1))
                if (killed_aliens == 5)
                    current_wave.aliens_rows -= 1;

            killed_aliens = 0;
        }
        // #### FIN DE LA BOUCLE ALIEN ####

        // #### GESTION DU BOSS ####
        if (current_wave.boss_id) {
            if (background_scroll_speed > 10) {
                background_scroll_speed -= 5;
            }

            for (int p = 0; p < game.players_nb ; ++p) {
                if (intersect_boss(players[p]->missile_pos, &boss) && boss.alive && players[p]->alive) {
                    if (!boss.triggered && boss.ready) {
                        boss.triggered = 1;
                        hearts_pos.y = WIN_H - 14 * RATIO;
                        boss.glowing = 1;
                        boss.glow_color = NOIR;

                        audiofile = "assets/boss.ogg";
                        bgm = Mix_LoadMUS(audiofile);
                        Mix_PlayMusic(bgm, -1);
                        volume = 128;
                        Mix_VolumeMusic(volume);
                        audio_fade_out = 0;
                    } else if (boss.ready) {
                        boss.alive -= 1;
                        score = score + 15;
                        boss.max_missile += 1;
                        boss.velocity.x += 2;
                        afficheSprite(impact_sprite, players[p]->missile_pos.x, players[p]->missile_pos.y - 5 * RATIO, BLANC);
                        switch (boss.alive) {
                            case 15:
                                boss.glow_color = VIOLET;
                                break;
                            case 10:
                                boss.color = VIOLET;
                                boss.glow_color = BLANC;
                                break;
                            case 7:
                                boss.color = NOIR;
                                boss.glow_color = BLANC;
                                break;
                            case 5:
                                boss.glow_color = ORANGE;
                                break;
                            case 1:
                                boss.glow_color = ROUGE;
                                break;
                        }
                    }
                    players[p]->missile = 0;
                    players[p]->missile_pos = players[p]->pos;
                }
            }


            for (int i = 0; i < boss.max_missile; i++) {
                if (boss.missile[i]) {
                    for (int p = 0; p < game.players_nb ; ++p) {
                        if (intersect(boss.missile_pos[i], players[p]) && players[p]->alive) {
                            if (players[p]->alive)
                                players[p]->alive -= 1;

                            score = (score < 0 ? 0 : score);
                            afficheSprite(impact_sprite, players[p]->pos.x, players[p]->pos.y, BLANC);
                            boss.missile[i] = 0;
                            boss.missile_pos[i] = boss.pos[1][1];
                        }
                    }

                }
            }
            // affichage des coeurs du boss s'il est en colere
            if (boss.triggered) {
                if (player.alive)
                    doActionBoss(&boss); // le boss décide s'il doit tirer ou pas
                for (int i = 0; i < boss.alive; ++i)
                    afficheSprite(heart_sprite, i * hearts_pos.x, 0, VIOLET);
            }
            animBoss(&boss);
            if (boss.alive)
                afficheBoss(&boss);
            else {
                finished_game = 1;
                current_wave.boss_id = 0;
                score += current_wave.score_bonus;
            }

            moveBoss(&boss, player.alive);
        }

        // ### DISPLAYING HUD ###
        // displaying score (top right corner
        if (!current_wave.boss_id && !finished_game) {
            sprintf(msg, "%d", score);
            displayMessage(msg, score_text_pos, BLANC);
        }

        // displaying players life
        for(int p=0; p<game.players_nb; p++)
            for (int i = 0; i < players[p]->alive; ++i)
                afficheSprite(heart_sprite, i * hearts_pos.x, hearts_pos.y - SPRITE_Y*RATIO*p, players[p]->color);

        ////////////////

        // affichage du message WAVE X au debut de chaque niveau
        if (show_wave_nb) {
            if (background_scroll_speed < 10)
                background_scroll_speed = 10;

            if (wave_text_pos.x > -200) {
                if (current_wave.boss_id) {
                    if (boss.triggered) {
                        if (wave_text_pos.x >= 45 && wave_text_pos.x < 100)
                            wave_text_speed = 2;
                        else
                            wave_text_speed = 40;

                        displayMessage("THE BOSS", wave_text_pos, player.compteur_anim % 8 + 2);
                        wave_text_pos.y += 40;
                        displayMessage("IS ANGRY", wave_text_pos, player.compteur_anim % 8 + 2);
                        wave_text_pos.y -= 40;
                        wave_text_pos.x -= wave_text_speed;
                    }
                } else {
                    if (wave_index == LEVELS_NB - 1) {
                        if (wave_text_pos.x >= 45 && wave_text_pos.x < 100)
                            wave_text_speed = 2;
                        else
                            wave_text_speed = 40;
                        displayMessage("FINAL WAVE", wave_text_pos, ROUGE);
                    } else {
                        if (wave_text_pos.x > 90 && wave_text_pos.x <= 130)
                            wave_text_speed = 2;
                        else
                            wave_text_speed = 40;
                        sprintf(msg, "WAVE %d", wave_index);
                        displayMessage(msg, wave_text_pos, BLANC);
                    }
                    wave_text_pos.x -= wave_text_speed;
                }
            } else {
                background_scroll_speed = 2;
                show_wave_nb = 0;
                wave_text_pos.x = 400;
            }
        }

        // s'il ne reste plus d'alien , on peut charger le niveau suivant
        if (current_wave.aliens_rows == 0 && current_wave.boss_id == 0)
            load_next_wave = 1;

        // si on est au boss et qu'on l'a tué !
        if (wave_index == LEVELS_NB && finished_game) {
            background_scroll_speed = 4;
            afficheSprite(player_reactor[player.compteur_anim % 2], player.pos.x, player.pos.y + 5 * RATIO, BLANC);
            afficheSprite(*player.sprite, player.pos.x, player.pos.y, ROUGE);
            afficheSprite(player_reactor[player.compteur_anim % 2], player2.pos.x, player2.pos.y + 5 * RATIO, BLANC);
            afficheSprite(*player2.sprite, player2.pos.x, player2.pos.y, VERT);
            if (player.pos.y > -50)
                player.pos.y -= 8;

            if (player2.pos.y > -50)
                player2.pos.y -= 8+rand()%4;
            tmp_pos.x = 95;
            tmp_pos.y = 150;
            displayMessage("CONGRATS", tmp_pos, JAUNE);
            sprintf(msg, "%d", score);
            tmp_pos.x = 160;
            tmp_pos.y = 210;
            displayMessage(msg, tmp_pos, BLANC);
            tmp_pos.x = 105;
            tmp_pos.y = 320;
            displayMessage("THE END", tmp_pos, BLEU);
        }
            //si tout les aliens sont mort et qu'on n'est pas au dernier niveau, on load le niveau suivant !
        else if (wave_index != LEVELS_NB - 1) {
            if (load_next_wave) {
                score += current_wave.score_bonus;
                show_wave_nb = 1;
                load_wave(&current_wave, ++wave_index, alien_list, shields_list, &boss);
                load_next_wave = 0;
            }
        }
            // si on est au dernier niveau et qu'il ny a plus d'aliens, on a finit le jeu !!
        else if (load_next_wave) {
            load_next_wave = 0;
            if (!finished_game) {
                score += 20 * player.alive;
                score += current_wave.score_bonus;
                finished_game = 1;
            }
            displayMessage("WELL", game_over_pos, ROUGE);
            game_over_pos.y += 40;
            game_over_pos.x -= 35;
            displayMessage("PLAYED", game_over_pos, ROUGE);
            game_over_pos.y -= 40;
            game_over_pos.x += 35;

            if (game_over_pos.y > 100) {
                for (int p = 0; p < game.players_nb; ++p) {
                    afficheSprite(player_reactor[players[p]->compteur_anim%2], players[p]->pos.x, players[p]->pos.y + 5 * RATIO,
                                  BLANC);
                    afficheSprite(*players[p]->sprite, players[p]->pos.x, players[p]->pos.y, players[p]->color);
                }

            }
            // on joue la cinématique de fin
            switch (cutscene_state) {
                case 0:
                    if (game_over_pos.y <= 200)
                        game_over_pos.y += 5;
                    else
                        cutscene_state++;
                    break;

                case 1:
                    if (player.pos.y > -100) {
                        player.pos.y -= 25;
                        player2.pos.y -= 25 + rand()%8;
                        if (timer) timer = 0;
                    } else
                        cutscene_state++;
                    break;

                case 2:
                    if (player.compteur_anim % 15 > 7 && timer < 30) {
                        displayMessage("THANK YOU", thank_you_pos, JAUNE);
                        thank_you_pos.x -= 35;
                        thank_you_pos.y += 40;
                        displayMessage("FOR PLAYING", thank_you_pos, JAUNE);
                        thank_you_pos.x += 35;
                        thank_you_pos.y -= 40;
                    } else timer++;

                    if (timer >= 30) {
                        background_scroll_speed = 12;
                        hearts_pos.y += 5;
                        game_over_pos.y += 10;
                        if (game_over_pos.y > 550) {
                            cutscene_state++;
                            timer = 0;
                        }
                    }
                    break;

                case 3:
                    background_scroll_speed = 152;
                    if (player.pos.y == 500 && player2.pos.y == 500) {
                        cutscene_state++;
                        printf("cut %d", cutscene_state);
                    }
                    else {
                        if(player.pos.y < 500)
                            player.pos.y = (player.pos.y+2 < 500 ? player.pos.y+2:500);
                        if(player2.pos.y < 500)
                            player2.pos.y = (player2.pos.y+2 < 500 ? player2.pos.y+2:500);
                        if (player.pos.y >= 300) {
                            displayMessage("THE END ?", end_text_pos, BLEU);
                            audio_fade_out = 1;
                        }
                    }
                    // on redonne les points de vie au joueur
                    if (player.alive < 10)
                        player.alive = 10;

                    if (game_over_pos.y < 644)
                        game_over_pos.y += 10;
                    break;

                case 4:
                    game_over_pos.x = 150;
                    game_over_pos.y = -100;
                    wave_index += 1;
                    load_wave(&current_wave, wave_index, alien_list, shields_list, &boss);
                    show_wave_nb = 1;
                    finished_game = 0;
                    cutscene_state = 0;
                    break;
            }
        }

        // get inputs and limit frame rate ...
        while ( (clock() - frame_time)*1000.0 / CLOCKS_PER_SEC < (float)game.update_rate) {
            if(getInputs() == -1) // getInputs returns -1 when escape is pressed
                break;
        }
        // then move players
        if (player.alive) {
            if (in_input_list(KEY_SPACE, 0))
                player.missile = 1;
            moveEntity(&player, get_last_input(0), player.velocity.x);
            animEntity(&player, player.anim_speed);

            if (game.players_nb == 2)
            {
                if (in_input_list(KEY_SPACE, 1))
                    player2.missile = 1;
                moveEntity(&player2, get_last_input(1), player.velocity.x);
                animEntity(&player2, player.anim_speed);
            }
        }
        // finaly, we can update the window
        updateWindow();

        // reset frame_time for next frame
        frame_time = clock();
    }


    // on est sortie de la boucle du jeu, la partie est donc terminé
    // on demande à l'utilisateur s'il souhaite sauvagerder son score avant de quitter
    printf("Votre score : %d\n", score);
    if(wave_index == LEVELS_NB && finished_game)
    {
        printf("Vous êtes le maître de l'espace !\n");
    }
    else if(wave_index == LEVELS_NB-1 && finished_game)
        printf("Félicitations ! Vous avez fini le jeu !\n");
    else
        printf("Vous êtes arrivé au niveau %d sur %d\n", wave_index, LEVELS_NB-1);
    printf("Souhaitez vous enregistrer votre score ? (1=oui;0=non)\n->");
    scanf("%d", &tmp);
    if(tmp==1)
    {
        printf("Entrez votre nom (maximum 10 caractères):\n->");
        scanf("%s", user_name);
        score_file = fopen("highscores.txt", "a+");
        fprintf(score_file, "%s %d\n", user_name, score);
        fclose(score_file);
        printf("Merci d'avoir joué %s !\n", user_name);
    }
    else
        printf("Merci d'avoir joué !\n");
    return 0;
}

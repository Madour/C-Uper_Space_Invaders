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

#include "boss.h"
#include "levels.h"
#include "text.h"

int main(int argc, char const *argv[])
{
    // #### VARIABLES INITIALIZATION ####
    srand(time(NULL));
    int killed_aliens = 0;              // number of dead aliens in the last row
    int score = 0;                      // stores player score
    game.current_wave = &wave_init;
    int load_next = 0;                  // equals 1 when no aliens remaining
    int wave_text_speed = 40;           // speed of the "Wave X" text animation
    int timer = 0;                      // timer used in cut scenes as a "clock"
    int cutscene_state = 0;             // used to track cut scene progression
    int tmp=0;
    time_t frame_time = clock();

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
    tuple hearts_pos = {.x=8*RATIO, .y=WIN_H -10*RATIO};
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
        if (*argv[1] - '0' < MAX_LEVELS)
            game.current_wave->index = *argv[1] - '0' - 1;
        else {
            printf("Niveau %d n'existe pas.\n", *argv[1] - '0');
            game.current_wave->index = -1;
        }
    }
     // creating player entity
    create_player(&player, player_pos);
    player.color = RED;
    create_player(&player2, player_pos);
    player2.color = GREEN;

    players[0] = &player;
    players[1] = &player2;

    // loading first wave
    load_next_wave(alien_list, shields_list, &boss);

    if(initDisplay(WIN_W, WIN_H) == -1)
    {
        printf("Erreur lors de l'initialisation graphique\n");
        return 0;
    }

    // region ##### GAME LOOP #####
    while(game.is_open)
    {

        game.counter = (game.counter == 15 ? 0 : game.counter+1);
        scrollBackground(0, game.background_scroll_speed);

        if (audio_fade_out)
            Mix_VolumeMusic(--volume);

        // si le niveau possede des boucliers on les affiche
        if (game.current_wave->has_shields)
            for (int i = 0; i < 3; ++i)
                if (shields_list[i].alive)
                    afficheSprite(*shields_list[i].sprite, shields_list[i].left, shields_list[i].top, LIGHTGREY);

        // si joueur en vie, on affiche son sprite, le missile et les coeurs
        for (int p = 0; p < game.players_nb; ++p) {
            if (players[p]->alive) {
                drawEntity(players[p]);
                drawEntityMissiles(players[p]);

                // test collision entre le missile du joueur et les boucliers
                if (game.current_wave->has_shields)
                    for (int s = 0; s < 3; ++s)
                        for (int m = 0; m < players[p]->max_missile; ++m)
                            if (intersect(players[p]->missile_pos[m], &shields_list[s]) && shields_list[s].alive) {
                                if (shields_list[s].alive) {
                                    shields_list[s].alive -= 1;
                                    shields_list[s].sprite++;
                                }
                                afficheSprite(impact_sprite, shields_list[s].pos.x, shields_list[s].pos.y, WHITE);
                                players[p]->missile[m] = 0;
                                players[p]->missile_pos[m] = players[p]->pos;
                                players[p]->missile_count--;
                            }
            }
        }

        // region #### BOUCLE ALIENS ####
        // boucle qui gère les interactions pour chaque alien
        for (int i = 0; i < game.current_wave->aliens_rows; i++) {
            for (int j = 0; j < 5; ++j) {
                if(game.game_over == game.players_nb) {
                    if(alien_list[i][j].color != DARKGREY) {
                        alien_list[i][j].color = DARKGREY;
                        alien_list[i][j].missile_color = LIGHTGREY;
                    }
                }

                if (alien_list[i][j].missile[0]) {
                    //si un missile alien touche un bouclier, on lui enleve une vie
                    if (game.current_wave->has_shields)
                        for (int s = 0; s < 3; ++s)
                            if (intersect(alien_list[i][j].missile_pos[0], &shields_list[s]) && shields_list[s].alive) {
                                if (shields_list[s].alive) {
                                    shields_list[s].alive -= 1;
                                    shields_list[s].sprite++;
                                }
                                afficheSprite(impact_sprite, shields_list[s].pos.x, shields_list[s].pos.y, WHITE);
                                alien_list[i][j].missile[0] = 0;
                                alien_list[i][j].missile_pos[0] = alien_list[i][j].pos;
                            }

                    //si un missile alien touche le joueur, on enleve un coeur au joueur
                    for (int p = 0; p < game.players_nb; ++p) {
                        if (intersect(alien_list[i][j].missile_pos[0], players[p]) && players[p]->alive) {
                            if (players[p]->alive) {
                                players[p]->alive -= 1;
                                if(!players[p]->alive)
                                    game.game_over++;
                            }
                            score = (alien_list[i][j].glowing ? score - 10 : score - 5);
                            score = (score < 0 ? 0 : score);
                            afficheSprite(impact_sprite, players[p]->pos.x, players[p]->pos.y, WHITE);
                            alien_list[i][j].missile[0] = 0;
                            alien_list[i][j].missile_pos[0] = alien_list[i][j].pos;
                        }
                    }

                    // affichage du missile alien
                    drawEntityMissiles(&alien_list[i][j]);

                }

                if (alien_list[i][j].alive) {
                    // on décide si l'alien doit tirer
                    tmp = rand() % game.current_wave->shoot_rate;
                    if (tmp == 1 && alien_list[i][j].missile[0] == 0) {
                        alien_list[i][j].missile[0] = 1;
                    }

                    animEntity(&alien_list[i][j], alien_list[i][j].anim_speed);

                    // on affiche le sprite des aliens
                    drawEntity(&alien_list[i][j]);

                    // si les aliens sont arrivé au bord bas, le joueur a perdu
                    if (i == game.current_wave->aliens_rows - 1)
                        if (alien_list[i][j].bottom >= player.pos.y - 4) {
                            game.game_over = 2;
                            player.alive = 0;
                            player2.alive = 0;
                        }
                    // si le missile du joueur touche un alien
                    for (int p = 0; p < game.players_nb; ++p) {
                        for (int m = 0; m < players[p]->max_missile; ++m) {
                            if (intersect(players[p]->missile_pos[m], &alien_list[i][j])) {
                                if (alien_list[i][j].alive)
                                    alien_list[i][j].alive -= 1;

                                score = (alien_list[i][j].glowing ? score + 10 : score + 5);
                                afficheSprite(impact_sprite, alien_list[i][j].pos.x, alien_list[i][j].pos.y, WHITE);
                                players[p]->missile[m] = 0;
                                players[p]->missile_pos[m] = players[p]->pos;
                                players[p]->missile_count--;
                            }
                        }
                    }
                }
                else
                    killed_aliens += 1;

                // on deplace les aliens en décalés (ligne pair vers la gauche et impair vers la droite)
                tmp = 2;
                if (i % 2)
                    tmp = 1;
                deplacerAlien(&alien_list[i][j], game.current_wave->xstep, game.current_wave->ystep, tmp);

            }
            // si tout les aliens de la derniere lignes sont mort, on decremente le nombre de ligne d'aliens
            if (i == (game.current_wave->aliens_rows - 1))
                if (killed_aliens == 5)
                    game.current_wave->aliens_rows -= 1;

            killed_aliens = 0;
        }
        // #### FIN DE LA BOUCLE ALIEN ####
        // endregion

        // region #### GESTION DU BOSS ####
        if (game.current_wave->boss_id) {
            if (game.background_scroll_speed > 10) {
                game.background_scroll_speed -= 5;
            }

            for (int p = 0; p < game.players_nb ; ++p) {
                for (int m = 0; m < players[p]->max_missile; ++m) {
                    if (intersect_boss(players[p]->missile_pos[m], &boss) && boss.alive && players[p]->alive) {
                        if (!boss.triggered && boss.ready) {
                            boss.triggered = 1;
                            hearts_pos.y = WIN_H - 14 * RATIO;
                            boss.glowing = 1;
                            boss.glow_color = BLACK;
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
                            afficheSprite(impact_sprite, players[p]->missile_pos[m].x,
                                          players[p]->missile_pos[m].y - 5 * RATIO, WHITE);
                            switch (boss.alive) {
                                case 15:
                                    boss.glow_color = VIOLET;
                                    break;
                                case 10:
                                    boss.color = VIOLET;
                                    boss.glow_color = WHITE;
                                    break;
                                case 7:
                                    boss.color = BLACK;
                                    boss.glow_color = WHITE;
                                    break;
                                case 5:
                                    boss.glow_color = ORANGE;
                                    break;
                                case 1:
                                    boss.glow_color = RED;
                                    break;
                            }
                        }
                        players[p]->missile[m] = 0;
                        players[p]->missile_pos[m] = players[p]->pos;
                        players[p]->missile_count--;
                    }
                }
            }


            for (int i = 0; i < boss.max_missile; i++) {
                if (boss.missile[i]) {
                    for (int p = 0; p < game.players_nb ; ++p) {
                        if (intersect(boss.missile_pos[i], players[p]) && players[p]->alive) {
                            if (players[p]->alive) {
                                players[p]->alive -= 1;
                                if(!players[p]->alive)
                                    game.game_over++;
                            }

                            score = (score < 0 ? 0 : score);
                            afficheSprite(impact_sprite, players[p]->pos.x, players[p]->pos.y, WHITE);
                            boss.missile[i] = 0;
                            boss.missile_pos[i] = boss.pos[1][1];
                        }
                    }

                }
            }
            // affichage des coeurs du boss s'il est en colere
            if (boss.triggered) {
                if (game.game_over != game.players_nb)
                    doActionBoss(&boss); // le boss décide s'il doit tirer ou pas
                for (int i = 0; i < boss.alive; ++i)
                    afficheSprite(heart_sprite, i * hearts_pos.x, 0, VIOLET);
            }
            animBoss(&boss);
            if (boss.alive)
                afficheBoss(&boss);
            else {
                game.finished_game = 1;
                game.current_wave->boss_id = 0;
                score += game.current_wave->score_bonus;
            }

            moveBoss(&boss);
        }

        // ### DISPLAYING HUD ###
        // displaying score (top right corner
        if (!game.current_wave->boss_id && !game.finished_game) {
            sprintf(msg, "%d", score);
            displayMessage(msg, score_text_pos, WHITE);
        }

        // displaying players life
        for(int p=0; p<game.players_nb; p++)
            for (int i = 0; i < players[p]->alive; ++i)
                afficheSprite(heart_sprite, i * hearts_pos.x, hearts_pos.y - 10*RATIO*p, players[p]->color);

        ////////////////
        // endregion

        if(game.game_over == game.players_nb) {
            displayGameOver(&game_over_pos);
        }

        // affichage du message WAVE X au debut de chaque niveau
        if (game.show_wave_nb) {
            displayWaveNum(&wave_text_pos, &wave_text_speed, &boss);
        }

        // s'il ne reste plus d'alien , on peut charger le niveau suivant
        if (game.current_wave->aliens_rows == 0 && game.current_wave->boss_id == 0)
            load_next = 1;

        if(game.current_wave->index == MAX_LEVELS - 1 && load_next)
        {
            game.background_scroll_speed = 4;
            afficheSprite(player_reactor[player.compteur_anim % 2], player.pos.x, player.pos.y + 5 * RATIO, WHITE);
            afficheSprite(*player.sprite, player.pos.x, player.pos.y, player.color);
            afficheSprite(player_reactor[player.compteur_anim % 2], player2.pos.x, player2.pos.y + 5 * RATIO, WHITE);
            afficheSprite(*player2.sprite, player2.pos.x, player2.pos.y, player2.color);
            if (player.pos.y > -50)
                player.pos.y -= 8;

            if (player2.pos.y > -50)
                player2.pos.y -= 8+rand()%4;
            tmp_pos.x = 95;
            tmp_pos.y = 150;
            displayMessage("CONGRATS", tmp_pos, YELLOW);
            sprintf(msg, "%d", score);
            tmp_pos.x = 160;
            tmp_pos.y = 210;
            displayMessage(msg, tmp_pos, WHITE);
            tmp_pos.x = 105;
            tmp_pos.y = 320;
            displayMessage("THE END", tmp_pos, BLUE);
        }
        // si on est au boss et qu'on l'a tué !
        else if (game.current_wave->index == FIRST_END && game.finished_game) {
            game.background_scroll_speed = 4;
            afficheSprite(player_reactor[player.compteur_anim % 2], player.pos.x, player.pos.y + 5 * RATIO, WHITE);
            afficheSprite(*player.sprite, player.pos.x, player.pos.y, player.color);
            afficheSprite(player_reactor[player.compteur_anim % 2], player2.pos.x, player2.pos.y + 5 * RATIO, WHITE);
            afficheSprite(*player2.sprite, player2.pos.x, player2.pos.y, player2.color);
            if (player.pos.y > -50)
                player.pos.y -= 8;

            if (player2.pos.y > -50)
                player2.pos.y -= 8+rand()%4;
            tmp_pos.x = 95;
            tmp_pos.y = 150;
            displayMessage("CONGRATS", tmp_pos, YELLOW);
            sprintf(msg, "%d", score);
            tmp_pos.x = 160;
            tmp_pos.y = 210;
            displayMessage(msg, tmp_pos, WHITE);
            tmp_pos.x = 105;
            tmp_pos.y = 320;
            displayMessage("THE END", tmp_pos, BLUE);
        }
            //si tout les aliens sont mort et qu'on n'est pas au dernier niveau, on load le niveau suivant !
        else if (game.current_wave->index != FAKE_END) {
            if (load_next) {
                score += game.current_wave->score_bonus;
                game.show_wave_nb = 1;
                load_next_wave( alien_list, shields_list, &boss);
                load_next = 0;
            }
        }
            // si on est au dernier niveau et qu'il ny a plus d'aliens, on a finit le jeu !!
        else if (load_next) {
            load_next = 0;
            if (!game.finished_game) {
                score += 20 * player.alive;
                score += game.current_wave->score_bonus;
                game.finished_game = 1;
            }
            displayMessage("WELL", game_over_pos, RED);
            game_over_pos.y += 40;
            game_over_pos.x -= 35;
            displayMessage("PLAYED", game_over_pos, RED);
            game_over_pos.y -= 40;
            game_over_pos.x += 35;

            if (game_over_pos.y > 100) {
                for (int p = 0; p < game.players_nb; ++p) {
                    afficheSprite(player_reactor[players[p]->compteur_anim%2], players[p]->pos.x, players[p]->pos.y + 5 * RATIO,
                                  WHITE);
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
                        displayMessage("THANK YOU", thank_you_pos, YELLOW);
                        thank_you_pos.x -= 35;
                        thank_you_pos.y += 40;
                        displayMessage("FOR PLAYING", thank_you_pos, YELLOW);
                        thank_you_pos.x += 35;
                        thank_you_pos.y -= 40;
                    } else timer++;

                    if (timer >= 30) {
                        game.background_scroll_speed = 12;
                        hearts_pos.y += 5;
                        game_over_pos.y += 10;
                        if (game_over_pos.y > 550) {
                            cutscene_state++;
                            timer = 0;
                        }
                    }
                    break;

                case 3:
                    game.background_scroll_speed = 160;
                    if (player.pos.y == 500 && player2.pos.y == 500) {
                        cutscene_state++;
                    }
                    else {
                        if(player.pos.y < 500)
                            player.pos.y = (player.pos.y+2 < 500 ? player.pos.y+2:500);
                        if(player2.pos.y < 500)
                            player2.pos.y = (player2.pos.y+2 < 500 ? player2.pos.y+2:500);
                        if (player.pos.y >= 300) {
                            displayMessage("THE END ?", end_text_pos, BLUE);
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
                    load_next_wave(alien_list, shields_list, &boss);
                    game.show_wave_nb = 1;
                    game.finished_game = 0;
                    cutscene_state = 0;
                    correctBackground();
                    break;
            }
        }

        // get inputs and limit frame rate ...
        while ( (clock() - frame_time)*1000.0 / CLOCKS_PER_SEC < (float)game.update_rate || game.paused==1) {
            if(getInputs() == -1) // getInputs returns -1 when escape is pressed
                break;
        }

        if(game.paused && !game.show_wave_nb) {
            game.paused--;
            tmp_pos.x = 100; tmp_pos.y = 200;
            displayMessage("PAUSED", tmp_pos, BLUE);
        }
        // then move players
        if (player.alive) {
            if (in_input_list(KEY_SPACE, 0) && player.compteur > player.shoot_rate) {
                entityShoot(&player);
            }
            moveEntity(&player, get_last_input(0), player.velocity.x);
            animEntity(&player, player.anim_speed);
            player.compteur++;
        }

        if (game.players_nb == 2) {
            if(player2.alive) {
                if (in_input_list(KEY_SPACE, 1) && player2.compteur > player2.shoot_rate) {
                    entityShoot(&player2);
                }
                moveEntity(&player2, get_last_input(1), player2.velocity.x);
                animEntity(&player2, player2.anim_speed);
                player2.compteur++;
            }
        }

        // finaly, we can update the window
        updateWindow();

        // reset frame_time for next frame
        frame_time = clock();
    }
    // endregion GAME LOOP

    // on est sortie de la boucle du jeu, la partie est donc terminé
    // on demande à l'utilisateur s'il souhaite sauvegarder son score avant de quitter
    printf("Votre score : %d\n", score);
    if(game.current_wave->index == MAX_LEVELS-1 && game.finished_game)
    {
        printf("Vous êtes le maître de l'espace !\n");
    }
    else if(game.current_wave->index == FAKE_END && game.finished_game)
        printf("Félicitations ! Vous avez fini le jeu !\n");
    else
        printf("Vous êtes arrivé a la vague %d sur %d\n", game.current_wave->index, FAKE_END);
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

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
|           alphabet.o -lX11 -lportaudio -lsndfile     |
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
	// #### INITIALISATION DES VARIABLES DU JEU ####
	srand(time(NULL));
	int level_index = 0;
	// user_name stockera le nom de l'utilisateur s'il souhaite enregister son score
	char user_name[11]; 
	FILE* score_file;
	
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
	
	// si l'utilisateur tente de selectionner un niveau
	if (argc > 1)
		if(*argv[1] -'0' < LEVELS_NB+1)
			level_index = *argv[1] -'0';
		else
		{
			printf("Niveau %d n'existe pas.\n", *argv[1] - '0');
			level_index = 0;
		}

	t_alien alien_list[10][5];
	entity shields_list[3];

	level current_level;
	
	tuple player_pos;
	player_pos.x = 181;
	player_pos.y = 500;

	tuple game_over_pos = {.x=150, .y=-100};
	tuple thank_you_pos = {.x=70, .y=350};
	tuple wave_text_pos = {.x=400, .y=295};
	int wave_text_speed = 40;
	tuple end_text_pos = {.x=90, .y=250};
	tuple score_text_pos = {.x=300, .y=10};

	int running = 1;
	int update_rate = 50;
	int input = 0;
	int killed_aliens = 0;
	int load_next_level = 0;
	int score = 0;
	int show_wave_nb = 1;
	int finished_game = 0;
	int tmp; tuple tmp_pos;
	int timer = 0;
	int cutscene_state = 0;
	int background_scroll_speed = 2;
	char msg[20];

	entity player;
	tuple hearts_pos;
	// creation du vaisseau joueur
	create_player(&player, player_pos);
	hearts_pos.x = 8 * RATIO;
	hearts_pos.y = WIN_H - 14*RATIO;
	// creation du boss
	t_boss boss;
	//create_boss(&boss);

	// chargement du niveau
	load_level(&current_level, level_index, alien_list, shields_list, &boss);

	if(initAffichage(WIN_W, WIN_H) == -1)
	{
		printf("Erreur lors de l'initialisation graphique\n");
		return 0;
	}

	// ##### DEBUT BOUCLE PRINCIPALE DU JEU #####
	while(running)
	{
		defilerFond(0, background_scroll_speed);

		if(audio_fade_out)
			Mix_VolumeMusic(--volume);

		// affichage du score en haut à droite
		if(!current_level.boss_id && !finished_game)
		{
			sprintf(msg, "%d", score);
			displayMessage(msg, score_text_pos, BLANC);
		}

		// si joueur en vie, on affiche son sprite, le missile et les coeurs
		if (player.alive)
		{	
			// affichage des sprites du joueur (flame du reacteur et le vaisseau)
			tmp = (player.compteur_anim%6 >= 3? 1 : 0);
			if(!finished_game)
				afficheSprite(player_reactor[tmp], player.pos.x, player.pos.y+5*RATIO, BLANC);
			afficheSprite(*player.sprite, player.pos.x, player.pos.y, ROUGE);

			// un clignotement indicateur de l'etat de santé du vaisseau, devient
			// plus frequent quand peu de point de vie restant
			if(player.glowing)
			{
				if(player.alive == 1)
				{
					if(player.compteur_anim%2 == 0)
						afficheSprite(*player.glow_sprite, player.pos.x, player.pos.y, BLANC);
				}
				else if(player.alive <= 3)
				{
					if(player.compteur_anim%4 == 0)
						afficheSprite(*player.glow_sprite, player.pos.x, player.pos.y, BLANC);
				}
				else if(player.alive <= 5)
				{
					if(player.compteur_anim%6 == 0)
						afficheSprite(*player.glow_sprite, player.pos.x, player.pos.y, BLANC);
				}
			}
			// affichage du missile s'il a été tiré
			if (player.missile)
				afficheSprite(*player.missile_sprite, player.missile_pos.x, player.missile_pos.y, JAUNE);
			// affichage des coeurs du joueur
			for (int i = 0; i < player.alive; ++i)
				afficheSprite(player_life, i*hearts_pos.x, hearts_pos.y, ROUGE);

			// test collision entre le missile du joueur et les boucliers
			if(current_level.has_shields)
				for (int s = 0; s < 3; ++s)
					if(intersect(player.missile_pos, &shields_list[s]) && shields_list[s].alive)
					{
						if(shields_list[s].alive)
						{
							shields_list[s].alive -= 1;
							shields_list[s].sprite++;
						}
						afficheSprite(impact_sprite, shields_list[s].pos.x, shields_list[s].pos.y, BLANC);
						player.missile = 0;
						player.missile_pos = player.pos;
					}
		}
		// sinon on commence le slow motion
		else
		{
			displayMessage("GAME", game_over_pos, ROUGE);
			game_over_pos.y += 40;
			displayMessage("OVER", game_over_pos, ROUGE);
			game_over_pos.y -= 40;
			if (game_over_pos.y<70)
				game_over_pos.y += 4;
			if (update_rate < 300)
			{
				update_rate+=2;
			}
		}

		// si le niveau possede des boucliers on les affiche
		if(current_level.has_shields)
			for (int i = 0; i < 3; ++i)
				if (shields_list[i].alive)
					afficheSprite(*shields_list[i].sprite, shields_list[i].left, shields_list[i].top, GRISCLAIR);

		// #### BOUCLE ALIENS ####
		// boucle qui gère les interactions pour chaque alien
		for(int i=0; i<current_level.aliens_rows; i++)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (alien_list[i][j].missile)
				{	
					//si un missile alien touche le joueur, on enleve un coeur au joueur
					if(intersect(alien_list[i][j].missile_pos, &player))
					{
						if(player.alive)
							player.alive -= 1;
						score = (alien_list[i][j].glowing ? score-10 : score-5);
						score = (score < 0 ? 0 : score);
						afficheSprite(impact_sprite, player.pos.x, player.pos.y, BLANC);
						alien_list[i][j].missile = 0;
						alien_list[i][j].missile_pos = alien_list[i][j].pos;
					}

					//si un missile alien touche un bouclier, on lui enleve une vie
					if(current_level.has_shields)
						for (int s = 0; s < 3; ++s)
							if(intersect(alien_list[i][j].missile_pos, &shields_list[s]) && shields_list[s].alive)
							{
								if(shields_list[s].alive)
								{
									shields_list[s].alive -= 1;
									shields_list[s].sprite++;
								}
								afficheSprite(impact_sprite, shields_list[s].pos.x, shields_list[s].pos.y, BLANC);
								alien_list[i][j].missile = 0;
								alien_list[i][j].missile_pos = alien_list[i][j].pos;
							}
	
					// affichage du missile alien
					if (player.alive)
						afficheSprite(*alien_list[i][j].missile_sprite, alien_list[i][j].missile_pos.x, alien_list[i][j].missile_pos.y, ORANGE);
					else
						afficheSprite(*alien_list[i][j].missile_sprite, alien_list[i][j].missile_pos.x, alien_list[i][j].missile_pos.y, GRISCLAIR);
				}

				if(alien_list[i][j].alive)
				{	
					// si les aliens sont arrivé au bord bas, le joueur a perdu
					if(i==current_level.aliens_rows-1)
						if(alien_list[i][j].pos.y+alien_list[i][j].size.y >= player.pos.y-4)
							player.alive = 0;

					// si le missile du joueur touche un alien
					if (intersect(player.missile_pos, &alien_list[i][j]))
					{
						if(alien_list[i][j].alive)
							alien_list[i][j].alive -= 1;

						score = (alien_list[i][j].glowing?score+10 : score+5);
						afficheSprite(impact_sprite, alien_list[i][j].pos.x, alien_list[i][j].pos.y, BLANC);
						player.missile = 0;
						player.missile_pos = player.pos;
					}
					
					if(alien_list[i][j].alive)
					{
						// on décide si l'alien doit tirer
						tmp = rand()%current_level.shoot_rate;
						if (tmp==1 && alien_list[i][j].missile == 0)
							alien_list[i][j].missile = 1;	
						
						animEntity(&alien_list[i][j], alien_list[i][j].anim_speed);
						
						// si le joueur est en vie, on affiche les aliens en couleur
						if(player.alive)
						{
							afficheSprite(*alien_list[i][j].sprite, alien_list[i][j].pos.x, alien_list[i][j].pos.y, alien_list[i][j].color);
							if(alien_list[i][j].compteur_anim%3 == 0 && alien_list[i][j].glowing)
								afficheSprite(*alien_list[i][j].glow_sprite, alien_list[i][j].pos.x, alien_list[i][j].pos.y, BLANC);
						}
						// sinon, on affiche en gris
						else
						{
							afficheSprite(*alien_list[i][j].sprite, alien_list[i][j].pos.x, alien_list[i][j].pos.y, GRISFONCE);
							if(alien_list[i][j].compteur_anim%3 == 0 && alien_list[i][j].glowing)
								afficheSprite(*alien_list[i][j].glow_sprite, alien_list[i][j].pos.x, alien_list[i][j].pos.y, GRISCLAIR);
						}
					}
				}
				else
					killed_aliens += 1;

				// on deplace les aliens en décalés (ligne pair vers la gauche et impair vers la droite)
				tmp = 2;
				if(i%2)
					tmp = 1;
				deplacerAlien(&alien_list[i][j], current_level.xstep, current_level.ystep, tmp);

			}
			// si tout les aliens de la derniere lignes sont mort, on decremente le nombre de ligne d'aliens
			if(i == (current_level.aliens_rows-1))
				if (killed_aliens == 5)
					current_level.aliens_rows -= 1;

			killed_aliens = 0;
		}
		// #### FIN DE LA BOUCLE ALIEN ####

		// #### GESTION DU BOSS ####
		if(current_level.boss_id)
		{
			if(background_scroll_speed > 10){
				background_scroll_speed-=5;
			}
			if(intersect_boss(player.missile_pos, &boss) && boss.alive && player.alive)
			{
				if(!boss.triggered && boss.ready)
				{
					boss.triggered = 1;
					hearts_pos.y = WIN_H - 14*RATIO;
					boss.glowing = 1;
					boss.glow_color = NOIR;
					
					audiofile = "assets/boss.ogg";
					bgm = Mix_LoadMUS(audiofile);
					Mix_PlayMusic(bgm, -1);
					volume = 128;
					Mix_VolumeMusic(volume);
					audio_fade_out = 0;
				}
				else if(boss.ready)
				{
					boss.alive -= 1;
					score = score+15;
					boss.max_missile += 1;
					boss.velocity.x += 2;
					afficheSprite(impact_sprite, player.missile_pos.x, player.missile_pos.y-5*RATIO, BLANC);
					switch(boss.alive){
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
				player.missile = 0;
				player.missile_pos = player.pos;
			}

			for(int i=0; i< boss.max_missile; i++)
			{
				if(boss.missile[i])
				{
					if(intersect(boss.missile_pos[i], &player) && player.alive)
					{
						if(player.alive)
							player.alive -= 1;
						
						score = (score < 0 ? 0 : score);
						afficheSprite(impact_sprite, player.pos.x, player.pos.y, BLANC);
						boss.missile[i] = 0;
						boss.missile_pos[i] = boss.pos[1][1];
					}
				}
			}
			// affichage des coeurs du boss s'il est en colere
			if(boss.triggered)
			{
				if(player.alive)
					doActionBoss(&boss); // le boss décide s'il doit tirer ou pas
				for (int i = 0; i < boss.alive; ++i)
					afficheSprite(player_life, i*hearts_pos.x, 0, VIOLET);
			}
			animBoss(&boss);
			if(boss.alive)
				afficheBoss(&boss);
			else
			{
				finished_game = 1;
				current_level.boss_id = 0;
				score+=current_level.score_bonus;
			}

			moveBoss(&boss, player.alive);
		}

		// affichage du message WAVE X au debut de chaque niveau
		if(show_wave_nb)
		{
			if(background_scroll_speed<10)
				background_scroll_speed = 10;

			if(wave_text_pos.x > -200)
			{
				if(current_level.boss_id)
				{
					if(boss.triggered)
					{
						if(wave_text_pos.x >= 45 && wave_text_pos.x < 100)
							wave_text_speed = 2;
						else
							wave_text_speed = 40;
	
						displayMessage("THE BOSS", wave_text_pos, player.compteur_anim%8+2);
						wave_text_pos.y +=40;
						displayMessage("IS ANGRY", wave_text_pos, player.compteur_anim%8+2);
						wave_text_pos.y -=40;
						wave_text_pos.x -= wave_text_speed;
					}
				}
				else
				{	
					if(level_index == LEVELS_NB-1)
					{
						if(wave_text_pos.x >= 45 && wave_text_pos.x < 100)
							wave_text_speed = 2;
						else
							wave_text_speed = 40;
						displayMessage("FINAL WAVE", wave_text_pos, ROUGE);
					}
					else
					{
						if(wave_text_pos.x > 90 && wave_text_pos.x <= 130)
							wave_text_speed = 2;
						else
							wave_text_speed = 40;
						sprintf(msg, "WAVE %d", level_index);
						displayMessage(msg, wave_text_pos, BLANC);
					}
					wave_text_pos.x -= wave_text_speed;
				}
			}
			else
			{
				show_wave_nb = 0;
				wave_text_pos.x = 400;
			}
		}

		// s'il ne reste plus d'alien , on peut charger le niveau suivant
		if(current_level.aliens_rows == 0 && current_level.boss_id == 0)
			load_next_level = 1;

		// si on est au boss et qu'on l'a tué !
		if(level_index == LEVELS_NB && finished_game)
		{
			background_scroll_speed = 4;
			afficheSprite(player_reactor[player.compteur_anim%2], player.pos.x, player.pos.y+5*RATIO, BLANC);
			afficheSprite(*player.sprite, player.pos.x, player.pos.y, ROUGE);
			if(player.pos.y>-50)
				player.pos.y -= 8;
			tmp_pos.x=95; tmp_pos.y=150;
			displayMessage("CONGRATS",tmp_pos, JAUNE);
			sprintf(msg, "%d", score);
			tmp_pos.x=160; tmp_pos.y=210;
			displayMessage(msg, tmp_pos, BLANC);
			tmp_pos.x=105; tmp_pos.y=320;
			displayMessage("THE END", tmp_pos, BLEU);
		}
		//si tout les aliens sont mort et qu'on n'est pas au dernier niveau, on load le niveau suivant !
		else if(level_index != LEVELS_NB-1)
		{
			if (load_next_level)
			{
				score += current_level.score_bonus;
				show_wave_nb = 1;
				load_level(&current_level, ++level_index, alien_list, shields_list, &boss);
				load_next_level = 0;
			}
		}
		// si on est au dernier niveau et qu'il ny a plus d'aliens, on a finit le jeu !!
		else if(current_level.aliens_rows == 0 && current_level.boss_id == 0)
		{
			load_next_level = 0;
			if(!finished_game)
			{
				score += 20*player.alive;
				score += current_level.score_bonus;
				finished_game = 1;
			}
			displayMessage("WELL", game_over_pos, ROUGE);
			game_over_pos.y += 40; game_over_pos.x -= 35;
			displayMessage("PLAYED", game_over_pos, ROUGE);
			game_over_pos.y -= 40; game_over_pos.x += 35;
			
			if(game_over_pos.y > 100)
			{
				afficheSprite(player_reactor[player.compteur_anim%2], player.pos.x, player.pos.y+5*RATIO, BLANC);
				afficheSprite(*player.sprite, player.pos.x, player.pos.y, ROUGE);
			}
			// on joue la cinématique de fin
			switch(cutscene_state)
			{
				case 0:
					if (game_over_pos.y <= 200)
						game_over_pos.y += 5;
					else
						cutscene_state++;
					break;

				case 1:
					if(player.pos.y > -100)
					{
						player.pos.y -= 25;
						if(timer) timer=0;
					}
					else 
						cutscene_state++;
					break;

				case 2:
					if(player.compteur_anim%15 > 7 && timer < 30)
					{
						displayMessage("THANK YOU", thank_you_pos, JAUNE);
						thank_you_pos.x-=35; thank_you_pos.y+=40;
						displayMessage("FOR PLAYING", thank_you_pos, JAUNE);
						thank_you_pos.x+=35; thank_you_pos.y-=40;
					}
					else timer++;

					if(timer >= 30)
					{
						background_scroll_speed = 12;
						hearts_pos.y += 5;
						game_over_pos.y += 10;
						if(game_over_pos.y > 550)
						{
							cutscene_state++;
							timer = 0;
						}
					}
					break;

				case 3:
					background_scroll_speed = 152;
					if(player.pos.y != 500)
					{
						player.pos.y += 2;
						if (player.pos.y >=300)
						{
							displayMessage("THE END ?", end_text_pos, BLEU);
						}
						if(player.pos.y>=250)
							audio_fade_out=1;
					}
					else
						cutscene_state++;
					// on redonne les points de vie au joueur
					if(player.alive < 10)
						player.alive = 10;

					if (game_over_pos.y < 610)
						game_over_pos.y += 10;
					break;

				case 4:
					game_over_pos.x=150;
					game_over_pos.y=-100;
					level_index+=1;
					load_level(&current_level, level_index, alien_list, shields_list, &boss);
					show_wave_nb = 1;
					finished_game = 0;
					cutscene_state = 0;
					break;
			}
		}

		// Gestion des inputs et mise a jour de l'affichage
		input = miseAJourAffichage(update_rate);
		if(input == -1)
		{
			running = 0;
		}
		else if(player.alive)
		{
			moveEntity(&player, input, X_STEP);
			animEntity(&player, player.anim_speed);
		}
	}

	// on est sortie de la boucle du jeu, la partie est donc terminé
	// on demande à l'utilisateur s'il souhaite sauvagerder son score avant de quitter
	printf("Votre score : %d\n", score);
	if(level_index == LEVELS_NB && finished_game)
	{
		printf("Vous êtes le maître de l'espace !\n");
	}
	else if(level_index == LEVELS_NB-1 && finished_game)
		printf("Félicitations ! Vous avez fini le jeu !\n");
	else
		printf("Vous êtes arrivé au niveau %d sur %d\n", level_index, LEVELS_NB-1);
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

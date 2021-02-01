/*=========================================
*
*    oO  Affichage pour Space-Invaders   Oo
*
*==========================================
*
* File : affichage.h
* Date : 29 octobre 09
* Author : Hilaire Thibault
* 
* Contient les prototypes des fonctions d'affichage
* pour le space-invaders, ainsi que les types prédéfinis
*
*======================================================================
*/

#ifndef __AFFICHAGE_H__
#define __AFFICHAGE_H__
#include <time.h>
#include "typedefs.h"


#define RATIO 4 // un pixel est affiché sur 4x4 pixels

#define WIN_W 400
#define WIN_H 640

#define RIGHT_BOUNDARY 380 // limite droite de l'écran
#define LEFT_BOUNDARY 20 // limite gauche de l'écran


#define KEY_LEFT 1
#define KEY_RIGHT 2
#define KEY_SPACE 3

extern int input_list[2][INPUT_SIZE];
extern int free_inputs[2];



/* constantes des couleurs */
#define WHITE 0
#define BLACK 1
#define RED 2
#define GREEN 3
#define BLUE 4
#define ORANGE 5
#define VIOLET 6
#define YELLOW 7
#define PINK 8
#define LIGHTGREY 9
#define DARKGREY 10


extern new_game game;
/* Fonction initAffichage
But: Permet d'initialiser tout l'affichage X11, de créer la fenêtre, les pixmap, les couleurs, etc...
Paramètres:
  - L : largeur (en X) de la fenêtre
  - H : hauteur (en Y) de la fenêtre
Retour: renvoit 0 si tout c'est bien passé, et -1 en cas d'erreur */
int initDisplay(int L, int H);


/* Fonction "afficheSprite"
But: Affiche un "sprite" à l'écran, aux coordonnées (x,y), et à une couleur donnée
Paramètres:
  - sprite : sprite à afficher
  - x,y : coordonnées où afficher le sprite
  - coul: couleur du sprite 
Les coordonnées correspondent au coin supérieur gauche du sprite. De plus, le sprite a pour dimension 4*SPRITE_X et 4*SPRITE_Y pixels  */
void afficheSprite( t_sprite sprite, int x, int y, int coul);

// returns -1 when escape pressed, return 0 otherwise
int getInputs();

int updateWindow();

void scrollBackground(int vit_x, int vit_y);
void correctBackground();

int in_input_list(int key, int player_nb);
int get_input_index(int key, int player_nb);
void pop(int list[INPUT_SIZE], int index);
int get_last_input(int player_nb);

#endif
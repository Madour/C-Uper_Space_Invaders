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
*
* Remarque: l'utilisation de affichage.o pour l'édition de lien
*           implique l'utilisation de l'option "-lX11 -L/usr/X11R6/lib"
*           pour l'utilisation de gcc (cela indique que l'on utilise la
*           librairie X11 de linux, responsable de l'affichage)
*           Ainsi, pour faire correctement l'édition de lien, il faut
*           rajouter "-lX11 -L/usr/X11R6/lib" à la fin de la commande,
*           par exemple :
*
*           gcc -o space.out main.o affichage.o alien.o 
*			 -lX11 -L/usr/X11R6/lib
*
*/


#ifndef __AFFICHAGE_H__
#define __AFFICHAGE_H__


/* Définition d'un sprite
un sprite est définie par un tableau de 0 et de 1.
Les sprites sont de taille fixe (ici 11x8) et en une seule couleur */
#define SPRITE_X 11
#define SPRITE_Y 8
#define SHEET_LEN 5 // taille maximum d'une feuille de sprite
#define RATIO 4 // un pixel est affiché sur 4x4 pixels

#define WIN_W 400
#define WIN_H 600

#define RIGHT_BOUNDARY 380 // limite droite de l'écran
#define LEFT_BOUNDARY 20 // limite gauche de l'écran

typedef int t_sprite[SPRITE_Y][SPRITE_X];

typedef int t_spritesheet[SHEET_LEN][SPRITE_Y][SPRITE_X];

// type tuple, pour stocker des coordonnés de position entre autre
typedef struct 
{
  int x;
  int y;
} tuple;

/* constantes des couleurs */
#define BLANC 0
#define NOIR 1
#define ROUGE 2
#define VERT 3
#define BLEU 4
#define ORANGE 5
#define VIOLET 6
#define JAUNE 7
#define ROSE 8
#define GRISCLAIR 9
#define GRISFONCE 10



/* Fonction initAffichage
But: Permet d'initialiser tout l'affichage X11, de créer la fenêtre, les pixmap, les couleurs, etc...
Paramètres:
  - L : largeur (en X) de la fenêtre
  - H : hauteur (en Y) de la fenêtre
Retour: renvoit 0 si tout c'est bien passé, et -1 en cas d'erreur */
int initAffichage(int L, int H);



/* Fonction "afficheSprite"
But: Affiche un "sprite" à l'écran, aux coordonnées (x,y), et à une couleur donnée
Paramètres:
  - sprite : sprite à afficher
  - x,y : coordonnées où afficher le sprite
  - coul: couleur du sprite 
Les coordonnées correspondent au coin supérieur gauche du sprite. De plus, le sprite a pour dimension 4*SPRITE_X et 4*SPRITE_Y pixels  */
void afficheSprite( t_sprite sprite, int x, int y, int coul);



/* Fonction miseAJourAffichage
But: Gère tous les évènements graphiques (déplacement de fenêtre, touches pressées, etc...). L'affichage ne se fait réellement QUE quand cette fonction est appelée.
Paramètres:
 - tempo_affichage : temporisation en micro-secondes (à régler en fonction de la machine et de la fluidité voulue. Entre 50 et 200 par exemple).
Retour: renvoit une valeur dépendant de la touche pressée par l'utilisateur
   -1 si l'utilisateur a pressé la touche ESC
   1 pour la flèche gauche "<-"
   2 pour la flèche droite "->"
   3 pour la touche "espace"
   0 si aucune touche n'a été pressée */
int miseAJourAffichage( int tempo_affichage);


void defilerFond(int vit_x, int vit_y);


#endif
	
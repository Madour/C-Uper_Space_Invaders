/*=========================================
*
*    oO  Affichage pour Space-Invaders   Oo
*
*==========================================
*
* File : affichage.c
* Date : 29 octobre 09
* Author : Hilaire Thibault
*
*=====================================
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
* Compilation : $gcc -c affichage.c
*/

#include <X11/Xlib.h>			/* pour XLib */
#include <X11/keysym.h>			/* pour les touches XLib */
#include <X11/Xatom.h>			/* pour le message WM_DELETE_WINDOW */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "affichage.h"
#include <unistd.h>


/* temporisation affichage en µs */
#define TEMPO_AFFICHAGE 150



/* Variables X11 */
Display* display;
int screen;
GC gc;
Window w;
Colormap cmap;
Atom wmDeleteMessage;

/* Pixmap */
Pixmap pix;		/* pixmap général sur lequel on écrit tout */
Pixmap fond1;	/* pixmap avec juste le fond */
Pixmap fond2;	/* pixmap avec juste le fond */
Pixmap clear;  /* pixmap tout noir, permet de clear l'ecran */

/* couleurs */
unsigned int couleurs[11];

/* Variables communes */
int init=0;					/* permet de savoir si on a lancé InitAffichage */
int Largeur, Hauteur;		/* taille de l'affichage */
int fond1_x=0, fond1_y=0;
int fond2_x=0, fond2_y=0;



/* Fonction "alloueCouleur"
   Allocation d'une couleur dans la ColorMap
Paramètres : red,green,blue : quantité (16bits) de rouge,vert et bleu qui compose la couleur
Retour: renvoit un entier non signé identifiant la couleur dans la ColorMap
*/
unsigned int alloueCouleur( int red, int green, int blue)
{
	XColor coul;
	coul.green = green;
	coul.red = red;
	coul.blue = blue;
	XAllocColor( display, cmap, &coul);
	return coul.pixel;
}




/* Fonction initAffichage
But: Permet d'initialiser tout l'affichage X11, de créer la fenêtre, les pixmap, les couleurs, etc...
Paramètres:
  - L : largeur (en X) de la fenêtre
  - H : hauteur (en Y) de la fenêtre
Retour: renvoit 0 si tout c'est bien passé, et -1 en cas d'erreur
*/
int initAffichage(int L, int H)
{
	int i,x,y;
	unsigned int gris[8];
	
	/* Vérifications */
	if (init)
	{
		fprintf( stderr, "Erreur (initAffichage) : la fonction initAffichage ne doit être lancée qu'une seule fois!\n");
		return -1;
	}	
	if ( (L<=49) || (L>800) || (H<=49) || (H>800) )
	{
		fprintf( stderr, "Erreur (InitAffichage) : la longueur et la hauteur doivent être compris entre 50 et 800\n");
		return -1;
	}
	Largeur = L;
	Hauteur = H;
	fond2_y = -H;

	/* Initialisation X11 */
	if ( (display=XOpenDisplay(NULL)) == NULL )
	{
		fprintf( stderr, "Erreur (InitAffichage) : connection avec X impossible : X est-il lancé ??\n");
		return -1;
	}

	/* crée la fenetre */
	screen = DefaultScreen(display);
	gc = DefaultGC (display, screen);
	cmap = DefaultColormap( display, screen);
	w = XCreateSimpleWindow( display, RootWindow(display,screen), 0,0, L,H,2 ,BlackPixel(display,screen), WhitePixel(display,screen));
	XStoreName( display, w, "Space-Invaders");

	/* crée la table de couleur */
	for( i=0; i<7; i++)
		gris[i] = alloueCouleur( 0xFFFF>>i, 0xFFFF>>i, 0xFFFF>>i );
	couleurs[BLANC] = alloueCouleur( 0xFFFF, 0xFFFF, 0xFFFF);
	couleurs[NOIR] = alloueCouleur( 0,0,0);
	couleurs[ROUGE] = alloueCouleur( 0xFFFF,0,0);
	couleurs[VERT] = alloueCouleur( 0,0xFFFF,0);
	couleurs[BLEU] = alloueCouleur( 0,0,0xFFFF);
	couleurs[ORANGE] = alloueCouleur( 0xFFFF,0x9999,0x3333);
	couleurs[VIOLET] = alloueCouleur( 0x8A8A, 0x2B2B, 0xE2E2);
	couleurs[JAUNE] = alloueCouleur( 0xFFFF,0xFFFF,0);
	couleurs[ROSE] = alloueCouleur( 0xFFFF,0x9999,0xFFFF);
	couleurs[GRISCLAIR] = alloueCouleur( 0xDDDD,0xDDDD,0xDDDD);
	couleurs[GRISFONCE] = alloueCouleur( 0x6666,0x6666,0x6666);
	

	int depth = XDefaultDepth (display, screen);
	/* crée le pixmap dans lequel on va tout dessiner */
	pix = XCreatePixmap (display, RootWindow(display,screen), L,H, depth);

	/* crée le pixmap qui va tout effacer à chaque frame*/
	clear = XCreatePixmap(display, RootWindow(display, screen), L,H, depth);
	XSetForeground( display, gc, BlackPixel(display,screen) );
	XFillRectangle( display,clear,gc, 0,0, L,H);
	//XCopyArea( display, clear, pix, gc, 0,0, L,H, 0,0);

	/* crée le pixmap de fond (dans lequel on rajoutera les obstacles ) */
	fond1 = XCreatePixmap (display, RootWindow(display,screen), L,H, depth);
	XSetForeground( display, gc, BlackPixel(display,screen) );
	XFillRectangle( display,fond1,gc, 0,0, L,H);
	for(i=0;i<=L*H/500;i++)
	{
		XSetForeground( display, gc, gris[ (rand()&0x7000)>>12 ] );
		x=((rand()&0xFFF00)>>8)%L;
		y=((rand()&0xFFF00)>>8)%H;
		XFillRectangle( display,fond1,gc, x,y,2,2);
	}
	/* copie du fond1 sur pix */
	XCopyArea( display, fond1, pix, gc, 0,0, L,H, 0,0);

	/* crée le pixmap de fond2 (dans lequel on rajoutera les obstacles ) */
	fond2 = XCreatePixmap (display, RootWindow(display,screen), L,H, depth);
	XSetForeground( display, gc, BlackPixel(display,screen) );
	XFillRectangle( display,fond2,gc, 0,0, L,H);
	for(i=0;i<=L*H/500;i++)
	{
		XSetForeground( display, gc, gris[ (rand()&0x7000)>>12 ] );
		x=((rand()&0xFFF00)>>8)%L;
		y=((rand()&0xFFF00)>>8)%H;
		XFillRectangle( display,fond2,gc, x,y,2,2);
	}
	/* copie du fond2 sur pix */
	XCopyArea( display, fond2, pix, gc, 0,0, L,H, 0,-H);


	/* sélectionne les évennements que l'on va gérer (renouvellement de l'affichage et gestion des touches, fermeture de fenêtre) */
	XSelectInput (display, w, ExposureMask | KeyPressMask);
	wmDeleteMessage = XInternAtom( display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols( display, w, &wmDeleteMessage, 1);


	// affiche la fenetre
	XMapWindow(display, w);

	/* on en profite pour initialiser le générateur de nb aléatoire, avec la date courante */
	srand(time(0));

	/* mise à jour d'init (qui indique si on est passé dans initAffichage) */
  	init = 1;

	return 0;
}


/* Fonction "afficheSprite"
But: Affiche un "sprite" à l'écran, aux coordonnées (x,y), et à une couleur donnée
Paramètres:
  - sprite : sprite à afficher
  - x,y : coordonnées où afficher le sprite
  - coul: couleur du sprite
Les coordonnées correspondent au coin supérieur gauche du sprite. De plus, le sprite a pour dimension 4*SPRITE_X et 4*SPRITE_Y pixels  */
void afficheSprite( t_sprite sprite, int x, int y, int coul)
{
	int i,j;
	
	/* vérifications */
	if (!init)
		fprintf( stderr, "Warning (afficheSprite) : initAffichage n'a pas encore été exécuté\n");
	if ( (x<1) || (y<1) || ( (x+SPRITE_X*4)>Largeur ) || ( (y+SPRITE_Y*4)>Hauteur ) )
		;
		//fprintf( stderr, "Warning (afficheSprite) : un sprite est affiché à la position (%d,%d) ce qui le fait sortir de la fenêtre\n", x,y);
		
	/* boucle pour afficher le sprite */
	XSetForeground( display, gc, couleurs[coul] );
	for( i=0; i<SPRITE_X; i++)
		for( j=0; j<SPRITE_Y; j++)
		{
			if (sprite[j][i])
				XFillRectangle( display,pix,gc, x+i*4,y+j*4,4,4);
		}
}


void defilerFond(int vit_x, int vit_y)
{
	fond1_x+=vit_x;
	fond1_y+=vit_y;
	
	fond2_x+=vit_x;
	fond2_y+=vit_y;

	if (fond1_y >= Hauteur)
		fond1_y=-Hauteur;
	
	if (fond2_y >= Hauteur)
		fond2_y=-Hauteur;
	
	if (fond1_x >= Largeur)
		fond1_x=-Largeur;
	
	if (fond2_x >= Largeur)
		fond2_x=-Largeur;
}



/* Fonction miseAJourAffichage
But: Gère tous les évènements graphiques (déplacement de fenêtre, touches pressées, etc...)
Paramètres:
 - tempo_affichage : temporisation en micro-secondes (à régler en fonction de la machine et de la fluidité voulue. Entre 50 et 200 par exemple).
Retour: renvoit une valeur dépendant de la touche pressée par l'utilisateur
   -1 si l'utilisateur a pressé la touche ESC
   1 pour la flèche gauche "<-"
   2 pour la flèche droite "->"
   3 pour la touche "espace"
   0 si aucune touche n'a été pressée
*/
int miseAJourAffichage( int tempo_affichage)
{
	int fin_attente = 0;
	int retour = 0;
	XEvent e;
	
	/* vérifications */
	if (!init)
		fprintf( stderr, "Warning (miseAJourAffichage) : initAffichage n'a pas encore été exécuté\n");
	/* affiche tout à l'écran */
	XCopyArea( display, pix, w, gc, 0,0, Largeur,Hauteur, 0,0);

	/* attente et gestion des évenements */
	time_t time=clock();
	while(!fin_attente)
	{
		if (XPending(display))		/* y'a-t-il un event qui nous attent */
		{
			XNextEvent(display,&e);
			switch (e.type)
			{
				case Expose :				/* réaffichage demandé */
					XCopyArea( display, pix, w, gc, 0,0, Largeur,Hauteur, 2,2);
					break;
				case KeyPress:			/* touche pressée */
					if (XLookupKeysym(&e.xkey, 0) == XK_Left)
					{
						retour=1;
						break;
					}
					else if (XLookupKeysym(&e.xkey, 0) == XK_Right)
					{
						retour=2;
						break;
					}
					else if (XLookupKeysym(&e.xkey, 0) == XK_space)
					{
						retour=3;
						break;
					}
					else if (XLookupKeysym(&e.xkey, 0) == XK_Escape)
					{
						/*XFreeGC(display, gc);*/
						XDestroyWindow( display,w);
						XCloseDisplay( display);
						return -1;
					}
					break;
				case ClientMessage:	/* fermeture fenêtre */
					if (e.xclient.data.l[0] == wmDeleteMessage)
					{
						exit(1);
						/*XPeekEvent( display, &e );
						XCloseDisplay(display);
						return 1;*/
					}
			}
		}
		/* vérification si on a attendu suffisamment longtemps
		TODO: faire propre (façon de faire absolument horrible,  mais faire "propre" me demanderait trop de temps) */
		if ( ((clock()-time)*1000/CLOCKS_PER_SEC) > tempo_affichage)
			fin_attente=1;
 	}

 	/* on nettoie l'affichage */
	XCopyArea(display, clear, pix, gc, 0,0, Largeur, Hauteur, 0, 0);
	/* copie du fond sur pix pour le tour suivant */
	XCopyArea( display, fond1, pix, gc, 0,0, Largeur,Hauteur, fond1_x, fond1_y);
	XCopyArea( display, fond2, pix, gc, 0,0, Largeur,Hauteur, fond2_x, fond2_y);



	return retour;
}


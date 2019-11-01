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
*/

#include <X11/Xlib.h>           /* pour XLib */
#include <X11/keysym.h>         /* pour les touches XLib */
#include <X11/Xatom.h>          /* pour le message WM_DELETE_WINDOW */

#include <stdio.h>
#include <stdlib.h>
#include "window.h"
#include <unistd.h>


/* temporisation affichage en µs */
#define TEMPO_AFFICHAGE 150

/* Variables X11 */
Display* display;
int screen;
GC gc;
Window w;
Colormap color_map;
Atom wmDeleteMessage;

/* Pixmap */
Pixmap pix;         /* pixmap général sur lequel on écrit tout */
Pixmap clear;       /* pixmap tout noir, permet de clear pix a chaque frame */
Pixmap bg_stars1;       /* pixmap avec juste le fond */
Pixmap bg_stars2;       /* pixmap avec juste le fond */

/* couleurs */
unsigned int colors[11];

/* Variables communes */
int init=0;                 /* permet de savoir si on a lancé InitAffichage */
int Largeur, Hauteur;       /* taille de l'affichage */
int bg_stars1_x=0, bg_stars1_y=0;
int bg_stars2_x=0, bg_stars2_y=0;


int input_list[2][INPUT_SIZE]= {{},{}};
int free_inputs[2]={INPUT_SIZE, INPUT_SIZE};

new_game game = {
        .width = WIN_W,
        .height = WIN_H,
        .update_rate = 50,
        .is_open = 1,
        .input_list = {{},{}},
        .players_nb = 1
};

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
    XAllocColor( display, color_map, &coul);
    return coul.pixel;
}

/* Fonction initAffichage
But: Permet d'initialiser tout l'affichage X11, de créer la fenêtre, les pixmap, les colors, etc...
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
    /*if ( (L<=49) || (L>800) || (H<=49) || (H>800) )
    {
        fprintf( stderr, "Erreur (InitAffichage) : la longueur et la hauteur doivent être compris entre 50 et 800\n");
        return -1;
    }*/
    Largeur = L;
    Hauteur = H;
    bg_stars2_y = -H;

    /* Initialisation X11 */
    if ( (display=XOpenDisplay(NULL)) == NULL )
    {
        fprintf( stderr, "Erreur (InitAffichage) : connection avec X impossible : X est-il lancé ??\n");
        return -1;
    }

    /* crée la fenetre */
    screen = DefaultScreen(display);
    gc = DefaultGC (display, screen);
    color_map = DefaultColormap( display, screen);
    w = XCreateSimpleWindow( display, RootWindow(display,screen), 0,0, L,H, 2 ,BlackPixel(display,screen), WhitePixel(display,screen));
    XStoreName( display, w, "C-Uper Space Invaders");

    /* crée la table de couleur */
    for( i=0; i<7; i++)
        gris[i] = alloueCouleur( 0xFFFF>>i, 0xFFFF>>i, 0xFFFF>>i );
    colors[BLANC] = alloueCouleur( 0xFFFF, 0xFFFF, 0xFFFF);
    colors[NOIR] = alloueCouleur( 0,0,0);
    colors[ROUGE] = alloueCouleur( 0xFFFF,0,0);
    colors[VERT] = alloueCouleur( 0,0xFFFF,0);
    colors[BLEU] = alloueCouleur( 0,0,0xFFFF);
    colors[ORANGE] = alloueCouleur( 0xFFFF,0x9999,0x3333);
    colors[VIOLET] = alloueCouleur( 0x8A8A, 0x2B2B, 0xE2E2);
    colors[JAUNE] = alloueCouleur( 0xFFFF,0xFFFF,0);
    colors[ROSE] = alloueCouleur( 0xFFFF,0x9999,0xFFFF);
    colors[GRISCLAIR] = alloueCouleur( 0xDDDD,0xDDDD,0xDDDD);
    colors[GRISFONCE] = alloueCouleur( 0x6666,0x6666,0x6666);

    int depth = XDefaultDepth (display, screen);
    /* crée le pixmap dans lequel on va tout dessiner */
    pix = XCreatePixmap (display, RootWindow(display,screen), L,H, depth);

    /* crée le pixmap qui va tout effacer à chaque frame*/
    clear = XCreatePixmap(display, RootWindow(display, screen), L,H, depth);
    XSetForeground( display, gc, BlackPixel(display,screen) );
    XFillRectangle( display,clear,gc, 0,0, L,H);
    XCopyArea( display, clear, pix, gc, 0,0, L,H, 0,0);

    /* crée le pixmap de fond (dans lequel on rajoutera les obstacles ) */
    bg_stars1 = XCreatePixmap (display, RootWindow(display,screen), L,H, depth);
    XSetForeground( display, gc, BlackPixel(display,screen) );
    XFillRectangle( display,bg_stars1,gc, 0,0, L,H);
    for(i=0;i<=L*H/500;i++)
    {
        XSetForeground( display, gc, gris[ (rand()&0x7000)>>12 ] );
        x=((rand()&0xFFF00)>>8)%L;
        y=((rand()&0xFFF00)>>8)%H;
        XFillRectangle( display,bg_stars1,gc, x,y,2,2);
    }
    /* copie du bg_stars1 sur pix */
    XCopyArea( display, bg_stars1, pix, gc, 0,0, L,H, 0,0);

    /* crée le pixmap de bg_stars2 (dans lequel on rajoutera les obstacles ) */
    bg_stars2 = XCreatePixmap (display, RootWindow(display,screen), L,H, depth);
    XSetForeground( display, gc, BlackPixel(display,screen) );
    XFillRectangle( display,bg_stars2,gc, 0,0, L,H);
    for(i=0;i<=L*H/500;i++)
    {
        XSetForeground( display, gc, gris[ (rand()&0x7000)>>12 ] );
        x=((rand()&0xFFF00)>>8)%L;
        y=((rand()&0xFFF00)>>8)%H;
        XFillRectangle( display,bg_stars2,gc, x,y,2,2);
    }
    /* copie du bg_stars2 sur pix */
    XCopyArea( display, bg_stars2, pix, gc, 0,0, L,H, 0,-H);

    /* sélectionne les évennements que l'on va gérer (renouvellement de l'affichage et gestion des touches, fermeture de fenêtre) */
    XSelectInput (display, w, ExposureMask | KeyPressMask | KeyReleaseMask);
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
void afficheSprite( t_sprite sprite, int x, int y, int color_index)
{
    int i,j;

    /* vérifications */
    if (!init)
        fprintf( stderr, "Warning (afficheSprite) : initAffichage n'a pas encore été exécuté\n");
    if ( (x<1) || (y<1) || ( (x+SPRITE_X*RATIO)>Largeur ) || ( (y+SPRITE_Y*RATIO)>Hauteur ) )
        ;
        //fprintf( stderr, "Warning (afficheSprite) : un sprite est affiché à la position (%d,%d) ce qui le fait sortir de la fenêtre\n", x,y);

    /* boucle pour afficher le sprite */
    XSetForeground( display, gc, colors[color_index] );
    for( i=0; i<SPRITE_X; i++)
        for( j=0; j<SPRITE_Y; j++)
        {
            if (sprite[j][i])
                XFillRectangle( display,pix,gc, x+i*RATIO,y+j*RATIO,RATIO,RATIO);
        }
}


void defilerFond(int vit_x, int vit_y)
{
    bg_stars1_x+=vit_x;
    bg_stars1_y+=vit_y;

    bg_stars2_x+=vit_x;
    bg_stars2_y+=vit_y;

    if (bg_stars1_y >= Hauteur)
        bg_stars1_y=-Hauteur;

    if (bg_stars2_y >= Hauteur)
        bg_stars2_y=-Hauteur;

    if (bg_stars1_x >= Largeur)
        bg_stars1_x=-Largeur;

    if (bg_stars2_x >= Largeur)
        bg_stars2_x=-Largeur;
}

int in_input_list(int key, int player_nb)
{
    for(int i=0; i<INPUT_SIZE; i++)
        if(key == game.input_list[player_nb][i])
            return 1;
    return 0;
}

int get_input_index(int key, int player_nb)
{
    for(int i=0; i<INPUT_SIZE; i++)
        if(key == game.input_list[player_nb][i])
            return i;
    return NULL;
}

void pop(int list[INPUT_SIZE], int index)
{
    for (int i = index; i < INPUT_SIZE-1; ++i)
        list[i] = list[i+1];
}

int get_last_input(int player_nb)
{
    for (int i = INPUT_SIZE-1; i >= 0 ; --i) {
        if(game.input_list[player_nb][i] && game.input_list[player_nb][i]!=KEY_SPACE)
            return game.input_list[player_nb][i];
    }
    return 0;
}

int getInputs()
{
    XEvent e;
    // wait for event
    if (XPending(display))
    {
        XNextEvent(display,&e);
        switch (e.type)
        {
            case Expose :               /* réaffichage demandé */
                XCopyArea( display, pix, w, gc, 0,0, Largeur,Hauteur, 2,2);
                break;

            case KeyPress:
            // player 1 inputs
                if(free_inputs[0])
                {
                    if (XLookupKeysym(&e.xkey, 0) == XK_Left) {
                        if (!in_input_list(KEY_LEFT, 0)) {
                            game.input_list[0][INPUT_SIZE - free_inputs[0]] = KEY_LEFT;
                            free_inputs[0]--;
                        }
                        break;
                    } else if (XLookupKeysym(&e.xkey, 0) == XK_Right) {
                        if (!in_input_list(KEY_RIGHT, 0)) {
                            game.input_list[0][INPUT_SIZE - free_inputs[0]] = KEY_RIGHT;
                            free_inputs[0]--;
                        }
                        break;
                    } else if ((XLookupKeysym(&e.xkey, 0) == XK_space) || (XLookupKeysym(&e.xkey, 0) == XK_Up)) {
                        if (!in_input_list(KEY_SPACE, 0)) {
                            game.input_list[0][INPUT_SIZE - free_inputs[0]] = KEY_SPACE;
                            free_inputs[0]--;
                        }
                        break;
                    }
                }
                // player 2 inputs
                if(free_inputs[1])
                {
                    if (XLookupKeysym(&e.xkey, 0) == XK_q) {
                        if (!in_input_list(KEY_LEFT, 1)) {
                            game.input_list[1][INPUT_SIZE - free_inputs[1]] = KEY_LEFT;
                            free_inputs[1]--;
                        }
                        break;
                    } else if (XLookupKeysym(&e.xkey, 0) == XK_d) {
                        if (!in_input_list(KEY_RIGHT, 1)) {
                            game.input_list[1][INPUT_SIZE - free_inputs[1]] = KEY_RIGHT;
                            free_inputs[1]--;
                        }
                        break;
                    } else if (XLookupKeysym(&e.xkey, 0) == XK_z) {
                        if (!in_input_list(KEY_SPACE, 1)) {
                            game.input_list[1][INPUT_SIZE - free_inputs[1]] = KEY_SPACE;
                            free_inputs[1]--;
                        }
                        break;
                    } else if(XLookupKeysym(&e.xkey, 0) == XK_Control_L) {
                        if(game.players_nb < 2) game.players_nb++;
                    }
                }
                if (XLookupKeysym(&e.xkey, 0) == XK_Escape) {
                    /*XFreeGC(display, gc);*/
                    XDestroyWindow(display, w);
                    XCloseDisplay(display);
                    game.is_open = 0;
                    return -1;
                }
                break;

            case KeyRelease:
                // player 1 inputs
                if (XLookupKeysym(&e.xkey, 0) == XK_Left) {
                    if (in_input_list(KEY_LEFT, 0))
                    {
                        pop(game.input_list[0], get_input_index(KEY_LEFT, 0));
                        free_inputs[0]++;
                    }
                    break;
                } else if (XLookupKeysym(&e.xkey, 0) == XK_Right) {
                    if (in_input_list(KEY_RIGHT, 0))
                    {
                        pop(game.input_list[0], get_input_index(KEY_RIGHT, 0));
                        free_inputs[0]++;
                    }
                    break;
                } else if ((XLookupKeysym(&e.xkey, 0) == XK_space)  || (XLookupKeysym(&e.xkey, 0) == XK_Up)) {
                    if (in_input_list(KEY_SPACE, 0))
                    {
                        pop(game.input_list[0], get_input_index(KEY_SPACE, 0));
                        free_inputs[0]++;
                    }
                    break;
                }
                // player 2 inputs
                if (XLookupKeysym(&e.xkey, 0) == XK_q) {
                    if (in_input_list(KEY_LEFT, 1))
                    {
                        pop(game.input_list[1], get_input_index(KEY_LEFT, 1));
                        free_inputs[1]++;
                    }
                    break;
                } else if (XLookupKeysym(&e.xkey, 0) == XK_d) {
                    if (in_input_list(KEY_RIGHT, 1))
                    {
                        pop(game.input_list[1], get_input_index(KEY_RIGHT, 1));
                        free_inputs[1]++;
                    }
                    break;
                } else if (XLookupKeysym(&e.xkey, 0) == XK_z) {
                    if (in_input_list(KEY_SPACE, 1)){
                        pop(game.input_list[1], get_input_index(KEY_SPACE, 1));
                        free_inputs[1]++;
                    }
                    break;
                }
                break;

            // closing game with mouse
            case ClientMessage:
                if (e.xclient.data.l[0] == wmDeleteMessage)
                {
                    XDestroyWindow(display, w);
                    XCloseDisplay(display);
                    game.is_open = 0;
                    return -1;
                }
        }
    }
    return 0;
}


int updateWindow()
{
    /* vérifications */
    if (!init)
        fprintf( stderr, "Warning (updateWindow) : initAffichage n'a pas encore été exécuté\n");

    /* affiche tout à l'écran */
    XCopyArea( display, pix, w, gc, 0,0, Largeur,Hauteur, 0,0);
    /* on nettoie l'affichage */
    XCopyArea(display, clear, pix, gc, 0,0, Largeur, Hauteur, 0, 0);
    /* copie du fond sur pix */
    XCopyArea( display, bg_stars1, pix, gc, 0,0, Largeur,Hauteur, bg_stars1_x, bg_stars1_y);
    XCopyArea( display, bg_stars2, pix, gc, 0,0, Largeur,Hauteur, bg_stars2_x, bg_stars2_y);
/*
    printf("Inputs P1 %d : ", free_inputs[1]);
    for (int f = 0; f < INPUT_SIZE; ++f) {
        printf("%d ", input_list[0][f]);
    }
    printf("\n");*/
    return 0;
}

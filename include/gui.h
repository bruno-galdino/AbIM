
#ifndef GUI_H
#define GUI_H

#include <stdbool.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "tad.h"


#define ID (__LINE__)
#define SQR(X) (X)*(X)

#define WINDOW_COLOR     al_map_rgb(227,237,245);
#define HOVER_COLOR      al_map_rgb(251,211,94)
#define MENU_COLOR       al_map_rgb(168,242,251)
#define BTN_COLOR        al_map_rgb(0,162,232)
#define BORDER_COLOR     al_map_rgb(68,68,68)
#define TOGGLED_COLOR    al_map_rgb(0,96,136)
#define COLOR_BLACK      al_map_rgb(0,0,0)
#define COLOR_WHITE      al_map_rgb(255,255,255)
#define COLOR_RED        al_map_rgb(255,0,0)
#define COLOR_GREEN      al_map_rgb(0,255,0)

#define COLOR_BLUE       BTN_COLOR //al_map_rgb(21,122,243)


typedef struct
{
    ALLEGRO_DISPLAY     *mainWindow;
    ALLEGRO_EVENT        event;
    ALLEGRO_EVENT_QUEUE *evtQueue;
    ALLEGRO_COLOR        windowColor;
    ALLEGRO_COLOR        textColor;
    ALLEGRO_COLOR        buttonColor;
    ALLEGRO_COLOR        btnBorderColor;
    ALLEGRO_FONT        *font;
    ALLEGRO_FONT        *smallFont;
    ALLEGRO_FONT        *bigFont;
    ALLEGRO_FONT        *curFont;
    int                  frameRadius;

} system_t;

typedef struct
{
    point_t mousePos;
    int     mouse[3];
    int     mouse2[3];
    int     mouseOld[3];
    int     mouseMoved;
    int     hotItem;
    int     activeItem;
    int     keyPressed;

} ui_state_t;

void InitGui   ( int w, int h );
bool MouseOver ( point_t a1, point_t a2 );
bool MouseOverCircle( point_t a1, int r );
void Update    ( );
void Die       ( const char *msg);
void GuiRefresh( );
int  TextHeight( const char *text );
int  TextWidth ( const char *text );

#endif

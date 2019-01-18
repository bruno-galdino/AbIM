
#ifndef WIDGETS_H
#define WIDGETS_H

#include "gui.h"
#include "tad.h"

extern system_t sys;
extern ui_state_t uiState;

int   Button      ( int id, int w, int h, point_t orig, const char *text );
void  Label       ( point_t orig, const char *text );
int   CheckButton ( int id, point_t orig, list_t *widgets );
int   ToggleButton( int id, int w, int h, point_t orig, const char *text , list_t *widgets );
int   Range       ( int id, point_t orig, int min, int max, int initVal, list_t *widgets );
void  Frame       ( int w, int h, point_t orig, ALLEGRO_COLOR color );
void  Box         ( int w, int h, point_t orig, ALLEGRO_COLOR color );
char *InputBox    ( int id, int w, int h, point_t orig, int maxLen, list_t *widgets );
int   RadioButton ( int id, point_t orig, list_t *group );
int   Menu        ( int id, int w, int h, point_t orig, const char *text, list_t *widgets );

#endif
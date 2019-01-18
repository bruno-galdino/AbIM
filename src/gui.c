
#include "../include/gui.h"

ui_state_t uiState;
system_t   sys;

void InitGui( int w, int h )
{
    al_init                 ( );
    al_init_primitives_addon( );
    al_init_font_addon      ( );
    al_init_ttf_addon       ( );
    al_install_mouse        ( );
    al_install_keyboard     ( );

    sys.mainWindow     = al_create_display(w,h);
    sys.evtQueue       = al_create_event_queue( );
    sys.font           = al_load_font("assets/envy.ttf",18,0);
    sys.smallFont      = al_load_font("assets/envy.ttf",14,0);
    sys.bigFont        = al_load_font("assets/envy.ttf",22,0);
    sys.curFont        = sys.font;/*a fonte que as funções usarão*/
    sys.windowColor    = WINDOW_COLOR;
    sys.textColor      = COLOR_BLACK;
    sys.buttonColor    = BTN_COLOR;
    sys.btnBorderColor = BORDER_COLOR;
    sys.frameRadius    = 2;

    if( !sys.mainWindow )
    {
        Die("Erro ao criar janela");
    }

    if( !sys.evtQueue)
    {
        Die("Erro ao criar fila de eventos");
    }

    if( !sys.font )
    {
        Die("Erro ao carregar fonte regular");
    }

    if( !sys.smallFont )
    {
        Die("Erro ao carregar fonte pequena");
    }

    if( !sys.bigFont )
    {
        Die("Erro ao carregar fonte grande");
    }

    al_register_event_source( sys.evtQueue, al_get_display_event_source( sys.mainWindow ) );
    al_register_event_source( sys.evtQueue, al_get_mouse_event_source( ) );
    al_register_event_source( sys.evtQueue, al_get_keyboard_event_source( ) );

}

bool MouseOver( point_t a1, point_t a2 )
{
    if( uiState.mousePos.x > a2.x || uiState.mousePos.x < a1.x )
    {
        return false;
    }

    if( uiState.mousePos.y > a2.y || uiState.mousePos.y < a1.y )
    {
        return false;
    }

    return true;

}

bool MouseOverCircle( point_t a1, int r )
{
    return SQR( a1.x - uiState.mousePos.x ) + SQR( a1.y - uiState.mousePos.y ) <= SQR(r);

}

void Update( )
{
    ALLEGRO_MOUSE_STATE mState;

    uiState.mouse2[0] = uiState.mouse2[1] = uiState.mouseMoved = uiState.keyPressed = 0;

    al_get_next_event( sys.evtQueue, &sys.event );

    switch( sys.event.type )
    {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            exit(0);

        case ALLEGRO_EVENT_MOUSE_AXES:

            uiState.mousePos.x     = sys.event.mouse.x;
            uiState.mousePos.y     = sys.event.mouse.y;
            uiState.mouseMoved     = 1;
            break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:

            if( !uiState.mouseOld[sys.event.mouse.button - 1 ] )
            {
                uiState.mouse2[ sys.event.mouse.button - 1 ] = 1;
            }
            uiState.mouse[ sys.event.mouse.button - 1 ] = 1;
            break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:

            uiState.mouse [ sys.event.mouse.button - 1 ]  = 0;
            uiState.mouse2[ sys.event.mouse.button - 1 ]  = 0;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:

            uiState.keyPressed = sys.event.keyboard.keycode;

        break;
    }

    al_get_mouse_state(&mState);
    uiState.mouseOld[0] = mState.buttons & 1;
    uiState.mouseOld[1] = mState.buttons & 2;

}

void Die(const char *msg)
{
    perror(msg);
    exit(-1);
}

void GuiRefresh( )
{

    Update( );

    uiState.hotItem = 0;
    if( uiState.mouse2[0] )
    {
        uiState.activeItem = 0;
    }

    al_flip_display( );
    al_clear_to_color( sys.windowColor );
    al_rest(0.001);
}

int TextHeight( const char *text )
{
    int ign, h,y;

    al_get_text_dimensions( sys.curFont, text, &ign, &y , &ign, &h );

    return h - y;
}

int TextWidth( const char *text )
{
    int ign, w,x;

    al_get_text_dimensions( sys.curFont, text, &x, &ign , &w, &ign );

    return w - x;

}

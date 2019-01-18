
#include "../include/widgets.h"

int Button( int id, int w, int h, point_t orig, const char *text )
{
    int ret = 0;

    if( MouseOver( orig, (point_t){  orig.x + w, orig.y + h } ) )
    {
        if( uiState.mouse2[0] )
        {
            ret = 1;
            orig.x++;
            orig.y++;

            Frame( w - 1, h - 1, orig, sys.buttonColor );
        }
        else
        {
            Frame( w, h, orig, HOVER_COLOR );
        }

    }
    else
    {
        Frame( w, h, orig, sys.buttonColor );
    }

    al_draw_text(

        sys.curFont,
        sys.textColor,
        orig.x + w/2,
        orig.y + h/2 - TextHeight(text)/2,
        ALLEGRO_ALIGN_CENTRE,
        text
    );

    return ret;
}

void Label( point_t orig, const char *text )
{
    al_draw_text( sys.curFont, sys.textColor, orig.x, orig.y, 0, text);
}

int CheckButton( int id, point_t orig, list_t *widgets )
{
    list_t *widget  = GetItemAdd( widgets, id );

    if( !widget )
    {
        return 0;
    }

    if( MouseOver( orig, (point_t){ orig.x + 20, orig.y + 20 } ) )
    {
        uiState.hotItem = id;

        if( uiState.mouse2[0] )
        {
            widget->state ^= 1;
        }

    }

    Frame( 20, 20, orig, al_map_rgba(0,0,0,0) );

    if( widget->state )
    {
        Box( 15, 15, (point_t){ orig.x+2, orig.y+2 }, COLOR_BLUE );
    }

    if( uiState.hotItem == id )
    {
        orig.x += 2;
        orig.y += 2;

        Box( 15, 15, orig, HOVER_COLOR );
    }

    return widget->state;
}

int ToggleButton( int id, int w, int h, point_t orig, const char *text , list_t *widgets )
{
    list_t *widget  = GetItemAdd( widgets, id );

    if( !widget )
    {
        return 0;
    }

    if( MouseOver( orig, (point_t){ orig.x + w, orig.y + h } ) )
    {
        uiState.hotItem = id;

        if( uiState.mouse2[0] )
        {
            widget->state ^= 1;
        }

    }

    if( widget->state )
    {

        Frame( w - 2, h - 2, (point_t){orig.x + 1, orig.y + 1} , TOGGLED_COLOR );
    }
    else
    {
        Frame( w , h, orig, sys.buttonColor );
    }

    if( uiState.hotItem == id )
    {
        Frame( w, h, orig, HOVER_COLOR );
    }

    al_draw_text(

        sys.curFont,
        sys.textColor,
        orig.x + w/2,
        orig.y + h/2 - TextHeight(text)/2,
        ALLEGRO_ALIGN_CENTRE,
        text

    );

    return widget->state;
}

int Range( int id, point_t orig, int min, int max, int initVal, list_t *widgets )
{

    int p1, p2, w, h;
    list_t *widget = GetItem( widgets, id );

    if( !widget )
    {
        widget = ListAppend( widgets, id, 0 );

        if( !widget )
        {
            return 0;
        }

        if( initVal <= max && initVal >= min )
        {
            widget->state = abs(initVal - min);
        }
        else
        {
            widget->state = 0;
        }
    }

    w  = max - min + 20;
    h  = 15;
    p1 = orig.x + widget->state;
    p2 = orig.y - 4;

    if( MouseOver( orig , (point_t){ orig.x + w, orig.y + h } ) )
    {
        uiState.hotItem = id;

        if( uiState.mouse[0] )
        {
            uiState.activeItem = id;
        }
    }

    if( uiState.activeItem == id )
    {
        if( !uiState.mouse[0] )
        {
            uiState.activeItem = 0;
        }

        widget->state = uiState.mousePos.x - orig.x - 10;

        if( widget->state > w - 20 )
        {
            widget->state = w - 20;
        }
        else if( widget->state < 0 )
        {
            widget->state = 0;
        }

    }

    sys.frameRadius  = 2;
    Frame( w, h, orig, sys.btnBorderColor );/*border*/
    Frame( w, h, orig, sys.buttonColor );/*slider*/

    sys.frameRadius--;

    Frame(

        20, h + 8, (point_t){ p1, p2 },
        uiState.hotItem == id ||
        uiState.activeItem == id ? HOVER_COLOR :
        sys.btnBorderColor
    );/*hanlder*/

    al_draw_textf( sys.curFont, sys.textColor, orig.x, orig.y + h + 4, 0, "%d", min + widget->state );/*range value*/

    return min + widget->state;/*retorna o valor do range*/
}


void Frame( int w, int h, point_t orig, ALLEGRO_COLOR color )
{
    int r = sys.frameRadius;

    al_draw_filled_rounded_rectangle( orig.x, orig.y, orig.x + w, orig.y + h, r, r, color );
    al_draw_rounded_rectangle( orig.x , orig.y , orig.x + w, orig.y + h, r, r, sys.btnBorderColor, 1 );
}


void Box( int w, int h, point_t orig, ALLEGRO_COLOR color )
{
    int r = sys.frameRadius;

    al_draw_filled_rounded_rectangle( orig.x, orig.y, orig.x + w, orig.y + h, r, r, color );

}

char *InputBox ( int id, int w, int h, point_t orig, int maxLen, list_t *widgets )
{
    return NULL;
    /*TODO: implementar*/
}

int RadioButton( int id, point_t orig, list_t *group )
{
    list_t *widget = GetItemAdd( group, id );
    list_t *aux;

    if( !widget )
    {
        return 0;
    }

    if( group == group->last )
    {
        group->state = 1;
    }

    if( MouseOverCircle( orig, 10 ) )
    {
        uiState.hotItem = id;

        if( uiState.mouse2[0] )
        {
            uiState.activeItem = id;
        }

    }

    if( widget->state )
    {
        al_draw_filled_circle( orig.x, orig.y, 6, COLOR_BLUE );
    }

    if( uiState.hotItem == id )
    {
        al_draw_filled_circle( orig.x, orig.y, 6, HOVER_COLOR );
    }

    if( uiState.activeItem == id )
    {
        aux = group;

        while( aux )
        {
            aux->state = 0;
            aux = aux->next;
        }

        widget->state = 1;
    }

    al_draw_circle( orig.x, orig.y , 10, COLOR_BLUE , 2 );

    return widget->state;
}

int Menu( int id, int w, int h, point_t orig, const char *text, list_t *widgets )
{

    list_t *widget = GetItemAdd( widgets, id );

    if( !widget )
    {
        return 0;
    }

    if( MouseOver( orig, (point_t){ orig.x + w, orig.y + h } ) )
    {
        uiState.hotItem = id;

        if( uiState.mouse2[0] )
        {
            uiState.activeItem = id;
            widget->state = 1;
        }

    }

    if( uiState.activeItem != id )
    {
        widget->state = 0;
    }

    if( uiState.hotItem == id )
    {
        Box( w, h, orig, HOVER_COLOR );
    }
    else
    {
        Box( w, h, orig, MENU_COLOR );
    }

    al_draw_text(

        sys.curFont,
        sys.textColor,
        orig.x + 1,
        orig.y + 2,
        0,
        text

    );

    return widget->state;
}

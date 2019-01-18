
#include "../include/gui.h"
#include "../include/widgets.h"

#define ABS(a) ( (a) > 0 ? (a) : -(a) )
#define SET_NUM(n){ temp = ABS( number) * 10; temp += n; number = temp <= 99999999 ? temp: ABS(number); }
#define SET_NUMBER(n) if( number < 0 ){ SET_NUM(n); number *= -1; } else{ SET_NUM(n); }
#define SET_OPER(op) if( oper == ' ' ){ num2 = number; number = 0;} oper = op;
#define TEST_KEY(key) (uiState.keyPressed == (ALLEGRO_KEY_##key) )

void Calc( )
{
    int  number = 0, num2 = 0, temp;
    char text[12] = "", oper = ' ';
    LIST_AUTOFREE list_t *widgets = CreateList( );
    LIST_AUTOFREE list_t *radios  = CreateList( );



    while(1)
    {

        if( Button( ID, 40, 40, (point_t){ 10, 40}, "9" ) || TEST_KEY(9) || TEST_KEY(PAD_9) )
        {
            SET_NUMBER(9);
        }

        else if( Button( ID, 40, 40, (point_t){ 60, 40}, "8" ) || TEST_KEY(8) || TEST_KEY(PAD_8) )
        {
            SET_NUMBER(8);
        }

        else if( Button( ID, 40, 40, (point_t){ 110, 40}, "7" ) || TEST_KEY(7) || TEST_KEY(PAD_7) )
        {
            SET_NUMBER(7);
        }

        else if( Button( ID, 40, 40, (point_t){ 10, 90}, "6" ) || TEST_KEY(6) || TEST_KEY(PAD_6) )
        {
            SET_NUMBER(6);
        }

        else if( Button( ID, 40, 40, (point_t){ 60, 90}, "5" ) || TEST_KEY(5) || TEST_KEY(PAD_5) )
        {
            SET_NUMBER(5);
        }

        else if( Button( ID, 40, 40, (point_t){ 110, 90}, "4" ) || TEST_KEY(4) || TEST_KEY(PAD_4) )
        {
            SET_NUMBER(4);
        }

        else if( Button( ID, 40, 40, (point_t){ 10, 140}, "3" ) || TEST_KEY(3) || TEST_KEY(PAD_3) )
        {
            SET_NUMBER(3);
        }

        else if( Button( ID, 40, 40, (point_t){ 60, 140}, "2" ) || TEST_KEY(2) || TEST_KEY(PAD_2) )
        {
            SET_NUMBER(2);
        }

        else if( Button( ID, 40, 40, (point_t){ 110, 140}, "1" ) || TEST_KEY(1) || TEST_KEY(PAD_1) )
        {
            SET_NUMBER(1);
        }

        else if( Button( ID, 40, 40, (point_t){ 160, 140}, "0" ) ||  TEST_KEY(0) || TEST_KEY(PAD_0) )
        {
            SET_NUMBER(0);
        }

        if( Button( ID, 40, 40, (point_t){ 160, 40}, "+" ) || TEST_KEY(PAD_PLUS) )
        {
            SET_OPER('+')
        }

        else if( Button( ID, 40, 40, (point_t){ 210, 40}, "-" ) || TEST_KEY(MINUS) || TEST_KEY(PAD_MINUS) )
        {
            SET_OPER('-');
        }

        else if( Button( ID, 40, 40, (point_t){ 160, 90}, "*" ) || TEST_KEY(PAD_ASTERISK) )
        {
            SET_OPER('*');
        }

        else if( Button( ID, 40, 40, (point_t){ 210, 90}, "/" ) || TEST_KEY(BACKSLASH) || TEST_KEY(PAD_SLASH)  )
        {
            SET_OPER('/');
        }

        if( Button( ID, 40, 40, (point_t){ 210, 140}, "=" ) ||  TEST_KEY(EQUALS) || TEST_KEY(ENTER ) || TEST_KEY(PAD_ENTER) )
        {
            switch( oper )
            {
                case '+':

                    number += num2;
                    break;

                case '-':

                    num2 -= number;
                    number = num2;
                    break;

                case '*':

                    number *= num2;
                    break;

                case '/':

                    number = number ? num2/number : 0;

                break;
            }

            oper = ' ';
        }

        else if( Button( ID, 40, 40, (point_t){ 260, 140}, "+/-" ) )
        {
            number *= -1;
        }

        else if( Button( ID, 40, 40, (point_t){ 260, 40}, "C" ) || TEST_KEY(ESCAPE) )
        {
            number = 0 ;
            oper = ' ';
        }

        else if( Button( ID, 40, 40, (point_t){ 260, 90}, "->" ) || TEST_KEY(BACKSPACE) )
        {
            number /= 10 ;
        }

        Frame( 290, 30, (point_t){ 10,4}, al_map_rgb( 6,60, 7 ));

        sys.textColor = COLOR_WHITE;
        sprintf(text,"%10d",number);
        Label( (point_t){170,5},text);

        if( oper != ' ')
        {
            sprintf(text,"%10d %c",num2,oper);
            Label( (point_t){2,5},text);
        }

        sys.textColor = COLOR_BLACK;

        sys.curFont = sys.smallFont;

        if( CheckButton( ID, (point_t){100,229 }, widgets ) )
        {
            sys.windowColor = al_map_rgb(1,10,82);
            sys.textColor   = COLOR_WHITE;

        }
        else
        {
            sys.windowColor = WINDOW_COLOR;
            sys.textColor   = COLOR_BLACK;
        }

        if( RadioButton( ID, (point_t){16,200}, radios ) )Label( (point_t){  30,190},"GRAU");
        if( RadioButton( ID, (point_t){16,230}, radios ) )Label( (point_t){  30,220},"RADIANO");

        Label( (point_t){2,260}, "AbIM GUI" );
        Label( (point_t){2,280}, "Allegro-based Immediate Mode GUI" );
        Label( (point_t){2,300}, "Bruno Soares Galdino - 2018 ;)");

        Range( ID, (point_t){100,189}, -128, 20, 10, widgets );

        if( ToggleButton( ID, 50, 20, (point_t){140,229 },"Ok", widgets ) ) Label( (point_t){ 200,229 },"Pressionado" );

        sys.curFont = sys.bigFont;


        GuiRefresh( );

    }

}

int main(void)
{
    InitGui( 310, 320 );
    Calc( );

    return 0;
}

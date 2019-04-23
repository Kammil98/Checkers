#include "Button.h"
Button::Button(int xx1, int yy1, int xx2, int yy2, char* ttext,  char* ttext2, int rr, int gg, int bb, int ttxtR, int ttxtG, int ttxtB, int bR, int bG, int bB){
    x1 = xx1;
    y1 = yy1;
    x2 = xx2;
    y2 = yy2;
    text1 = ttext;
    text2 = ttext2;
    R = rr;
    G = gg;
    B = bb;
    txtR = ttxtR;
    txtG = ttxtG;
    txtB = ttxtB;
    borderR = bR;
    borderG = bG;
    borderB = bB;
}
int Button::getx1() { return x1; }
void Button::setx1( int val ) { x1 = val; }
int Button::gety1() { return y1; }
void Button::sety1( int val ) { y1 = val; }
int Button::getx2() { return x2; }
void Button::setx2( int val ) { x2 = val; }
int Button::gety2() { return y2; }
void Button::sety2( int val ) { y2 = val; }
char* Button::gettext1() { return text1; }
void Button::settext1( char* val ) { text1 = val; }
char* Button::gettext2() { return text2; }
void Button::settext2( char* val ) { text2 = val; }
int Button::getR() { return R; }
void Button::setR( int val ) { R = val; }
int Button::getG() { return G; }
void Button::setG( int val ) { G = val; }
int Button::getB() { return B; }
void Button::setB( int val ) { B = val; }
void Button::setBackgroundColour( int val ) {
    setR( val );
    setG( val );
    setB( val );
}
int Button::gettxtR() { return txtR; }
void Button::settxtR( int val ) { txtR = val; }
int Button::gettxtG() { return txtG; }
void Button::settxtG( int val ) { txtG = val; }
int Button::gettxtB() { return txtB; }
void Button::settxtB( int val ) { txtB = val; }
void Button::settxtColour( int val ){
    settxtR( val );
    settxtG( val );
    settxtB( val );
}
int Button::getborderR() { return borderR; }
void Button::setborderR( int val ) { borderR = val; }
int Button::getborderG() { return borderG; }
void Button::setborderG( int val ) { borderG = val; }
int Button::getborderB() { return borderB; }
void Button::setborderB( int val ) { borderB = val; }
void Button::setborderColour( int val ) {
    setborderR( val );
    setborderG( val );
    setborderB( val );
}
void Button::show( BITMAP * place ){
    rectfill( place, x1-7, y1-7, x2+7, y2+7, makecol( borderR, borderG, borderB ) );
    rectfill( place, x1-4, y1-4, x2+4, y2+4, makecol( R, G, B ) );
    rectfill( place, x1-2, y1-2, x2+2, y2+2, makecol( borderR, borderG, borderB ) );
    rectfill( place, x1, y1, x2, y2, makecol( R, G, B ) );
    if( text2 == NULL )textout_ex( place, font, text1, x1 + ( x2 - x1 - text_length( font, text1 ) ) / 2, y1 + ( y2 - y1 - text_height( font ) ) / 2, makecol( txtR, txtG, txtB ), -1 );
    else{
        textout_ex( place, font, text1, x1 + ( x2 - x1 - text_length( font, text1 ) ) / 2, y1 + ( y2 - y1 - text_height( font ) ) / 4, makecol( txtR, txtG, txtB ), -1 );
        textout_ex( place, font, text2, x1 + ( x2 - x1 - text_length( font, text2 ) ) / 2, y1 + ( y2 - y1 - text_height( font ) ) / 4 * 3, makecol( txtR, txtG, txtB ), -1 );
    }
}
// tworzy ladny przycisk

void Button::hide( BITMAP * place ) {
    rectfill( place, x1-7, y1-7, x2+7, y2+7, makecol( 128, 128, 128 ) );
}
// usuwa ladny przycisk

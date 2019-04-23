#include "MouseAndKeyboard.h"

int MouseAndKeyboard::getmx(){ return mx; }
void MouseAndKeyboard::setmx( int val ){ mx = val; }
int MouseAndKeyboard::getmy(){ return my; }
void MouseAndKeyboard::setmy( int val ){ my = val; }
int MouseAndKeyboard::getmb(){ return mb; }
void MouseAndKeyboard::setmb( int val ){ mb = val; }
void MouseAndKeyboard::mouse(){
    if( mx != mouse_x ) mx = mouse_x;
    if( my != mouse_y ) my = mouse_y;
    if( mb != mouse_b ) mb = mouse_b;
}
//zapisuje wspolrzedne myszki i kliknietny przycisk

bool MouseAndKeyboard::clickInside( int x1, int y1, int x2, int y2 ) {
    if( x1 <= mx && mx <= x2 && y1 <= my && my <= y2 && mb == 1 ) return true;
    else return false;
}
// sprawdza, czy myszka kliknela na przycisk (tylko LPM)

bool MouseAndKeyboard::clickButton( Button button ) {
    if( clickInside( button.getx1(), button.gety1(), button.getx2(), button.gety2() ) ) return true;
    else return false;
}
void MouseAndKeyboard::mousePosition( Position& pos ) {
    mouse();
    while( mb != 1 ) mouse();
    pos.c = ( mx - 15 - ( mx - 15 ) % 80 ) / 80;
    pos.l = 7 -( my - 10 - ( my - 10 ) % 80 ) / 80;
    while( mb != 0 ) mouse();
}

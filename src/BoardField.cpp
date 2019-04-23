#include "BoardField.h"
#include <allegro.h>

BoardField::BoardField( int column, int line, int ID, int leftx, int upy,int pawnID, bool col )
{
    x = leftx;
    y = upy;
    id = ID;
    pawnId = pawnID;
    colour = col;
    pos.c = column;
    pos.l = line;
}
int BoardField::getid(){ return id; }
void BoardField::setid(int val){ id = val; }
int BoardField::getx() { return x; }
void BoardField::setx(int val) { x = val; }
int BoardField::gety() { return y; }
void BoardField::sety(int val) { y = val; }
int BoardField::getpawnId(){ return pawnId; }
void BoardField::setpawnId(int val){ pawnId = val; }
bool BoardField::getcolour() { return colour; }
void BoardField::setcolour(bool val) { colour = val; }
Position BoardField::getpos() { return pos; }
int BoardField::getcolumn() { return pos.c; }
int BoardField::getline() { return pos.l; }
void BoardField::setpos(Position val) { pos = val; }
void BoardField::show( BITMAP *bufor ) {
    if( colour ) { rectfill( bufor, x, y, x+80, y+80, makecol( 227, 224, 200 ) );} //bialy
    else{ rectfill ( bufor, x, y, x+80, y+80, makecol( 120, 63, 63 ) ); } //czarny

}

#include "pawn.h"

Pawn::Pawn( int ID, int pawnx, int pawny, int fieldID, bool col, int rad, bool beat, bool qqueen ){
    id = ID;
    fieldId = fieldID;
    x = pawnx;
    y = pawny;
    radius = rad;
    colour = col;
    beated = beat;
    queen = qqueen;
}


void Pawn::setid( int val){ id = val; }
void Pawn::setfieldId( int val ){ fieldId = val; }
void Pawn::setRadius( int val ){ radius = val; }
void Pawn::setX( int val ){ x = val; }
void Pawn::setY( int val ){ y = val; }
void Pawn::setBeated( bool val ){beated = val; }
void Pawn::setColour( bool val ){colour = val; }
void Pawn::setQueen( bool val ){queen = val; }
int Pawn::getid(){ return id; }
int Pawn::getfieldId(){ return fieldId; }
int Pawn::getRadius(){ return radius; }
int Pawn::getX(){ return x; }
int Pawn::getY(){ return y; }
bool Pawn::getBeated(){ return beated; }
bool Pawn::getColour(){ return colour; }
bool Pawn::getQueen(){ return queen; }
void Pawn::show( BITMAP *bufor, bool selected ) {
    int red = 0;
    if( ! colour ) {
        circlefill( bufor, x, y, radius, makecol( 120, 120, 120 ) );
        if( queen ) {
            rectfill( bufor, x-5, y-30, x+5, y+30, makecol( 255, 255, 255 ) );
            rectfill( bufor, x-20, y-5, x+20, y-15, makecol( 255, 255, 255 ) );
        }
    }
    else {
        circlefill( bufor, x, y, radius, makecol( 255, 255, 255 ) );
        if( queen ) {
            rectfill( bufor, x-5, y-30, x+5, y+30, makecol( 0, 0, 0 ) );
            rectfill( bufor, x-20, y-5, x+20, y-15, makecol( 0, 0, 0 ) );
        }
    }
    if( selected ) red = 180;
    circle( bufor, x, y, radius, makecol( red, 0, 0 ) );
    circle( bufor, x, y, radius-3, makecol( red, 0, 0 ) );
    floodfill( bufor, x+radius-1, y, makecol( red, 0, 0 ) );
    blit( bufor, screen, 0, 0, 0, 0, 900, 700 );

}
void Pawn::go( BITMAP *bufor, BoardField &lastField, BoardField &newField ) {
    if( fieldId != -1 ) {
        lastField.setpawnId( -1 );
        lastField.show( bufor );
    }
    newField.setpawnId( id );
    x = newField.getx() + 40;
    y = newField.gety() + 40;
    fieldId = newField.getid();
    show( bufor );
}

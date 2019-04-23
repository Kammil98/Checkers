#include<allegro.h>
#include "BoardField.h"
#ifndef PAWN_H
#define PAWN_H


class Pawn
{
    private:
        int id; //0-11 black 12-23 white
        int fieldId; // -100 mean not on board
        int radius;
        int x;
        int y;
        bool colour;//true = white, false = black
        bool beated;
        bool queen;
    public:
        Pawn( int =-1, int = 0 , int = 0, int = -1, bool = true, int= 35, bool= false, bool=false );
        void setid( int );
        void setfieldId( int );
        void setRadius( int );
        void setX( int );
        void setY( int );
        void setBeated( bool );
        void setColour( bool );
        void setQueen( bool );
        int getid();
        int getfieldId();
        int getRadius();
        int getX();
        int getY();
        bool getBeated();
        bool getColour();
        bool getQueen();
        void show( BITMAP *, bool = false );
        void go( BITMAP *, BoardField &, BoardField & );
};

#endif // PAWN_H

#include "BoardField.h"
#include "Pawn.h"
#include "MouseAndKeyboard.h"
#ifndef MOVINGPAWN_H
#define MOVINGPAWN_H


class MovingPawn
{
    public:
        bool canBeat( Jump[4] );
        bool inRangeOfBoard( int, int );
        void isItQueen( BITMAP*, Pawn&, int& );
        void checkJump( BoardField[ 8 ][ 8 ], Pawn, int, Jump&, int, int );
        int canGo( Position, Position, Jump[ 4 ] );//sprawdza, czy wybrany pionek moze tam isc lub bic
        void possibleJumps( BoardField[ 8 ][ 8 ], Pawn, Position, int, Jump[ 4 ] );//obliczanie lini i kolumn mozliwych ruchow
        void removingPawn( BITMAP*, Pawn[ 2 ][ 12 ], BoardField[ 8 ][ 8 ], Position, Position );//usuwanie zbitego pionka
        bool mandatoryJump( Pawn[ 2 ][ 12 ], BoardField[ 8 ][ 8 ], int ); // sprawdza, czy sa obowiazkowe bicia
        void movePawn( BITMAP*, Pawn[ 2 ][ 12 ], BoardField[ 8 ][ 8 ], int&, MouseAndKeyboard, Button, Button );//przemieszcza pionek
    protected:
    private:
};

#endif // MOVINGPAWN_H

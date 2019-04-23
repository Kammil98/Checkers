#include "MovingPawn.h"
#ifndef NPC_H
#define NPC_H
struct Pawnchoosing{
    Pawn pawn;
    Jump jump[4];
    bool use;
};

class Npc
{
    public:
        void correctSimulation( Pawn[ 2 ][ 12 ], BoardField[ 8 ][ 8 ], Jump, int, int, bool& );//przesowa na symulacji szachownicy pionka, ktory atakowal i zbija starego pionka
        bool safeJump( Position, BoardField[ 8 ][ 8 ], int); // sprawdza, czy pionek bedzie zbity przez inny pionek(nie patrzy na damki)
        void cpBoardandField( Pawn[ 2 ][ 12 ], Pawn[ 2 ][ 12 ], BoardField[ 8 ][ 8 ], BoardField[ 8 ][ 8 ] );
        void haveBeat( Pawn[ 2 ][ 12 ], BoardField[ 8 ][ 8 ], int=0 );//sprawdza ile mozna maksymalnie zbic pionkow z uwzglednieniem stracenia pionka, ktory bil
        void closeToEdge();// wybiera przemieszczanie sie w kierunku krawedzi
        void guardEnd();
        bool isOcuppied( BoardField fields[ 8 ][ 8 ], Position pos, int dir );// sprawdza, czy pionek za wskazana pozycja moze byc zbity
        void antyMultikill( BoardField[ 8 ][ 8 ] );//sprawdza czy mozliwe jest stracenie tylko jednego pionka
        void npcThink( BITMAP*, Pawn[ 2 ][ 12 ], BoardField[ 8 ][ 8 ], int&, Button, Button );//mysli, ktory pionek wybrac
        void movePawn(BITMAP *, Pawn[ 2 ][ 12 ], BoardField[ 8 ][ 8 ], int );//wykonuje ruch
        void willNotDieByPawn( Pawn[ 2 ][ 12 ], BoardField[ 8 ][ 8 ] );//sprawdza czy istnieje pionek, ktory nie bedzie zbity
    protected:
    private:
        Pawnchoosing choosePawn[ 12 ];
        MovingPawn moving;
};

#endif // NPC_H

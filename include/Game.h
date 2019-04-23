#include <allegro.h>
#include "pawn.h"
#include "BoardField.h"
#include "MouseAndKeyboard.h"
#include "MovingPawn.h"
#ifndef GAME_H
#define GAME_H

#include <Pawn.h>


class Game
{
    public:
        Game();
        ~Game();
        int GetTurn();
        void SetTurn( int );
        bool GetSi();
        void SetSi( bool );
        //void showFields();
        //void showPawns();
        void CheckWinner( BITMAP *, bool& );
        //sprawdza czy jest Zwyciezca
        void createFields();
        //tworzy oiekty - pola planszy
        void createBoardSurroundings(BITMAP *, int, int );
        //tworzy cyfry i litery dookola planszy
        void createPawns();
        // tworzy obiekty - pionki
        void setPawns();
        // ustawia pionki
        void saveGame();
        // zapisuje do pliku stan gry
        void play( int=15, int=10 );
        //tworzy plansze, jej otoczenie, oraz ustawia pionki na pozycjach poczatkowych
        void newGame();
        //rozpoczyna nowa gre
        void loadGame();
        //wczytuje zapisana gre i ja wznawia
        void startGame();
        //uruchamia gre
    protected:
    private:
        int turn;// turn = 1 mean white turn 0 mean black
        bool si;
        MouseAndKeyboard m;
        BoardField fields[ 8 ][ 8 ];
        Pawn allPawns[ 2 ][ 12 ];
        BITMAP *bufor;
};

#endif // GAME_H

#include<allegro.h>
#ifndef BOARDFIELD_H
#define BOARDFIELD_H

struct Position{
    int l;
    int c;
};
struct Jump{
    Position pos;
    bool beat;
};
class BoardField
{
    private:
        int id;
        int x;
        int y;
        int pawnId; // -100 mean no pawn on this field
        bool colour;  //true = white, false = black
        Position pos;   //0, 1,2,...,7 for line and 0, 1,2,...,7 for column
    public:
        BoardField( int = 0, int = 0, int=-1, int=0, int=0, int =-1, bool=true );
        int getid();
        void setid( int );
        int getx();
        void setx( int );
        int gety();
        void sety( int );
        int getpawnId();
        void setpawnId( int );
        bool getcolour();
        void setcolour( bool );
        Position getpos();
        int getcolumn();
        int getline();
        void setpos( Position );
        void show( BITMAP * );
};

#endif // BOARDFIELD_H

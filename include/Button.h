#include<allegro.h>
#ifndef BUTTON_H
#define BUTTON_H


class Button
{
    private:
        int x1;
        int y1;
        int x2;
        int y2;
        char* text1;
        char* text2;
        int R;
        int G;
        int B;
        int txtR;
        int txtG;
        int txtB;
        int borderR;
        int borderG;
        int borderB;
    public:
        Button( int, int, int, int, char*, char* = NULL, int = 128, int = 128, int = 128, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0 );
        int getx1();
        void setx1( int );
        int gety1();
        void sety1( int );
        int getx2();
        void setx2( int );
        int gety2();
        void sety2( int );
        char* gettext1();
        void settext1( char* );
        char* gettext2();
        void settext2( char* );
        int getR();
        void setR( int );
        int getG();
        void setG( int );
        int getB();
        void setB( int );
        void setBackgroundColour( int);
        int gettxtR();
        void settxtR( int );
        int gettxtG();
        void settxtG( int );
        int gettxtB();
        void settxtB( int );
        void settxtColour( int );
        int getborderR();
        void setborderR( int );
        int getborderG();
        void setborderG( int );
        int getborderB();
        void setborderB( int );
        void setborderColour( int );
        void show( BITMAP * );// tworzy ladny przycisk
        void hide( BITMAP * );// usuwa ladny przycisk

};

#endif // BUTTON_H

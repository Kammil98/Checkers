#include<allegro.h>
#include"Button.h"
#include "BoardField.h"

#ifndef MOUSEANDKEYBOARD_H
#define MOUSEANDKEYBOARD_H


class MouseAndKeyboard
{
    private:
        int mx;
        int my;
        int mb;
    public:
        int getmx();
        void setmx(int);
        int getmy();
        void setmy(int);
        int getmb();
        void setmb(int);
        void mouse(); //zapisuje wspolrzedne myszki i kliknietny przycisk
        bool clickInside( int, int, int, int ); // sprawdza, czy myszka kliknela w wybrane miejsce (tylko LPM)
        bool clickButton( Button ); // sprawdza, czy myszka kliknela na przycisk (tylko LPM)
        void mousePosition( Position& );
};

#endif // MOUSEANDKEYBOARD_H

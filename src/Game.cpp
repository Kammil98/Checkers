#include <fstream>
#include "Game.h"
#include "Button.h"
#include<time.h>
#include "Npc.h"
Game::Game(){
    allegro_init();
    set_color_depth( 16 );
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 900, 700, 0, 0 );
    bufor = create_bitmap( 900, 700 );
    install_keyboard();
    install_mouse();
    show_mouse(screen);
    unscare_mouse();
}

Game::~Game(){
    destroy_bitmap( bufor );
    allegro_exit();
}

int Game::GetTurn() { return turn; }

void Game::SetTurn( int val ) { turn = val; }

bool Game::GetSi() { return si; }

void Game::SetSi( bool val ) { si = val; }

/*void Game::showPawns(){
    for( int colour = 0; colour < 2; colour++ ) {
        for( int id = 0; id < 12 ; id++ ) {
            std::cout<<"allPawns["<<colour<<"]["<<id<<"].getid() ="<<allPawns[ colour ][ id ].getid()<<std::endl;
            std::cout<<"allPawns["<<colour<<"]["<<id<<"].getX() ="<<allPawns[ colour ][ id ].getX()<<std::endl;
            std::cout<<"allPawns["<<colour<<"]["<<id<<"].getY() ="<<allPawns[ colour ][ id ].getY()<<std::endl;
            std::cout<<"allPawns["<<colour<<"]["<<id<<"].getColour() ="<<allPawns[ colour ][ id ].getColour()<<std::endl;
            std::cout<<"allPawns["<<colour<<"]["<<id<<"].getfieldId() ="<<allPawns[ colour ][ id ].getfieldId()<<std::endl;
            std::cout<<"allPawns["<<colour<<"]["<<id<<"].getQueen() ="<<allPawns[ colour ][ id ].getQueen()<<std::endl;
            std::cout<<std::endl;
        }
    }
}
//pokazuje wartosci obiektow w tablicy allPawns

void Game::showFields() {
    for( int line = 0; line < 8; line++ ) {
        for( int c = 0; c < 8 ; c++ ) {
            std::cout<<"fields["<<c<<"]["<<line<<"].getid() ="<<fields[ c ][ line ].getid()<<std::endl;
            std::cout<<"fields["<<c<<"]["<<line<<"].getpawnId() ="<<fields[ c ][ line ].getpawnId()<<std::endl;
            std::cout<<"fields["<<c<<"]["<<line<<"].getx() ="<<fields[ c ][ line ].getx()<<std::endl;
            std::cout<<"fields["<<c<<"]["<<line<<"].gety() ="<<fields[ c ][ line ].gety()<<std::endl;
            std::cout<<"fields["<<c<<"]["<<line<<"].getcolour() ="<<fields[ c ][ line ].getcolour()<<std::endl;
            std::cout<<std::endl;
        }
    }
}
//pokazuje wartosci obiektow w tablicy fields
*/

void Game::CheckWinner( BITMAP *win, bool& menu) {
    int sum;
    bool movable;
    Position pos;
    Jump jump[4];
    MovingPawn moving;
    sum = 0;
    for( int i = 0; i < 12; i++) {
        movable = false;
        pos.c = allPawns[ turn ][ i ].getfieldId() % 8;
        pos.l = allPawns[ turn ][ i ].getfieldId() / 8;
        moving.possibleJumps(fields, allPawns[ turn ][ i ], pos, turn, jump );
        for ( int k = 0; k < 4; k++ ){
            if( jump[ k ].pos.c != -100 ) movable = true;
        }
        if( ! movable ) sum ++;
    }
    if( sum == 12 ) {
        win = load_bmp("zwyciestwo.bmp", default_palette );
        if( ! win ) {
            set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
            allegro_message( "nie moge zaladowac obrazka zwyciestwo.bmp !" );
        }
        masked_blit( win, bufor, 0, 0, 80, 310, win->w, win->h );
        blit( bufor, screen, 0, 0, 0, 0, 900, 700 );
        menu = true;
        while ( m.getmb() != 0 ) m.mouse();
        while ( m.getmb() == 0 ) m.mouse();
    }
}
//sprawdza czy jest Zwyciezca



void Game::createFields() {
    Position pos;
    pos.c = 0;
    pos.l = 0;
    BoardField field( 0, 0, 0, 0, 0, -1, true );
    for( int i = 0; i < 8; i++ ) {
        for( int j = 0; j < 8 ; j++ ) {
            field.setid( ( 8 - 1 - i ) * 8 + j );
            field.setx( 25 + j * 80 );
            field.sety( 20 + i * 80 );
            pos.l = ( 8 - 1 - i );
            pos.c = ( j );
            field.setpos( pos );
            if( ( i + j ) % 2 == 0 ) field.setcolour( false );
            else field.setcolour( true );
            fields[ j ][ 8 - 1 - i ] = field;
        }
    }
}
//tworzy oiekty - pola planszy

void Game::createBoardSurroundings( BITMAP *surrounding, int left, int up ) {
    rectfill( bufor, left , up, 660 + left, 660 + up, makecol( 120, 63, 63 ) );
    rectfill( bufor, left + 5, up + 5, 660 + left - 5, 660 + up - 5, makecol( 227, 224, 200 ) );
    rectfill( bufor, left + 8, up + 8, 660 + left - 8, 660 + up - 8, makecol( 120, 63, 63 ) );
    textout_ex( bufor, font, "Warcaby", 325, 0, makecol( 0, 0, 0 ), -1 );
    //surrounding = load_bmp("cyfry3.bmp", default_palette );
   // if( ! surrounding ) {
   //     set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
   //     allegro_message( "nie moge zaladowac obrazka cyfry3.bmp !" );
   // }
   // masked_blit( surrounding, bufor, 0,10, 65, 850, 50, 50 );//A
   // masked_blit( surrounding, bufor, 40,70, 0, 660, 50, 50 );//2

}
//tworzy cyfry i litery dookola planszy

void Game::createPawns() {
    for( int i = 0; i < 3; i++ ) {
        for( int j = 0; j < 4; j++ ) {
            //white
            allPawns[ 1 ][ i * 4 + j ].setid( i * 4 + j + 12 );
            allPawns[ 1 ][ i * 4 + j ].setX( fields[ j * 2 + ( i + 1 ) % 2 ][ i ].getx() + 40 );
            allPawns[ 1 ][ i * 4 + j ].setY( fields[ j * 2 + ( i + 1 ) % 2 ][ i ].gety() + 40 );
            allPawns[ 1 ][ i * 4 + j ].setfieldId( fields[ j * 2 + ( i + 1 ) % 2 ][ i ].getid() );
            allPawns[ 1 ][ i * 4 + j ].setQueen( false );
            fields[ j * 2 + ( i + 1 ) % 2 ][ i ].setpawnId( i * 4 + j + 12 );
            //black
            allPawns[ 0 ][ i * 4 + j ].setid( i * 4 + j );
            allPawns[ 0 ][ i * 4 + j ].setX( fields[ j * 2 + i % 2 ][ 7 - i ].getx() + 40 );
            allPawns[ 0 ][ i * 4 + j ].setY( fields[ j * 2 + i % 2 ][ 7 - i ].gety() + 40 );
            allPawns[ 0 ][ i * 4 + j ].setfieldId( fields[ j * 2 + i % 2 ][ 7 - i ].getid());
            allPawns[ 0 ][ i * 4 + j ].setColour( false );
            allPawns[ 0 ][ i * 4 + j ].setQueen( false );
             fields[ j * 2 + i % 2 ][ 7 - i ].setpawnId( i * 4 + j );
        }
    }
}
// tworzy obiekty - pionki

void Game::setPawns() {
    for( int i = 0; i < 12; i++ ) {
        if( allPawns[ 1 ][ i ].getfieldId() != -1 )allPawns[ 1 ][ i ].show( bufor );
        if( allPawns[ 0 ][ i ].getfieldId() != -1 )allPawns[ 0 ][ i ].show( bufor );
    }
}
// ustawia pionki

void Game::saveGame() {
    std::ofstream p;
    p.open( "saved.txt", std::ios::out | std::ios::trunc );
    p<<si<<" "<<turn<<"\n";
    for( int i = 0; i < 8; i++ ) {
        for( int j = 0; j < 8; j++ ) {
            p<<fields[ j ][ i ].getpawnId()<<" "<<fields[ j ][ i ].getid()<<"\n";
        }
    }
    for( int i = 0; i < 2; i++ ) {
        for( int j = 0; j < 12; j++ ) {
            p<<allPawns[ i ][ j ].getfieldId()<<" "<<allPawns[ i ][ j ].getX()<<" "<<allPawns[ i ][ j ].getY()<<" "<<allPawns[ i ][ j ].getQueen()<<"\n";
        }
    }
    p.close();
}
// zapisuje do pliku stan gry

void Game::play( int left, int up ) {
    BITMAP * surrounding = NULL;
    MovingPawn movep;
    Npc npc;
    bool menu = false;
    Button saveb( 725, 500, 785, 535, "zapisz" ),
    menub( 725, 565, 785, 600, "menu" ),
    savemeb( 700, 565, 810, 600, "na pewno?" ), yesb( 700, 620, 745, 655, "tak" ), nob( 765, 620, 810, 655, "nie" ),
    whob( 700, 230, 810, 265, "ruch gracza: ", "bialego", 128, 128, 128, 255, 255, 255, 255, 255, 255 ),
    warningb( 700, 300, 810, 360, "obowiazkowe", "bicie!", 128, 128, 128, 200 );
    if( turn == 0 ) {
        whob.settxtColour( 0 );
        whob.setborderColour( 0 );
        whob.settext2( "czarnego" );
    }
    clear_to_color( bufor, makecol( 128, 128, 128 ) );
    createBoardSurroundings( surrounding, left, up );
    if( movep.mandatoryJump( allPawns, fields, turn ) )warningb.show( bufor );
    menub.show( bufor );
    saveb.show( bufor );
    whob.show( bufor );
    srand( time( 0 ) );
    for( int i = 0; i < 8; i++ ) {
        for( int j = 0; j < 8 ; j++ ) fields[ i ][ j ].show( bufor );
    }
    setPawns();
    //_sleep(500);
    while( ! key[ KEY_ESC ] && ! menu ) {
        m.mouse();
        if( si && ! turn ) {
            _sleep(500);
            npc.npcThink( bufor, allPawns, fields, turn, whob, warningb );
        }
        CheckWinner( surrounding, menu);
        if( m.clickInside( left, up, 640 + left, 640 + up ) && ( ! si || turn == 1 ) && ! menu ) {
            movep.movePawn( bufor, allPawns, fields, turn, m, whob, warningb );
        }
        CheckWinner( surrounding, menu);
        if( m.clickButton( saveb ) ) {
            saveb.setborderR(130);
            saveb.show( bufor );
            blit( bufor, screen, 0, 0, 0, 0, 900, 700 );
            saveGame();
            while( m.getmb() == 1 ) m.mouse();
            saveb.setborderColour(0);
            saveb.show( bufor );
        }
        if( m.clickButton( menub ) ) {
            menub.hide( bufor );
            savemeb.show( bufor );
            yesb.show( bufor );
            nob.show( bufor );
            blit( bufor, screen, 0, 0, 0, 0, 900, 700 );
            while( !( m.clickButton( yesb ) || m.clickButton( nob ) ) )m.mouse();
            if( m.clickButton( yesb ) ) menu = true;
            else {
                savemeb.hide( bufor );
                yesb.hide( bufor );
                nob.hide( bufor );
                menub.show( bufor );
            }
            blit( bufor, screen, 0, 0, 0, 0, 900, 700 );
        }
        blit( bufor, screen, 0, 0, 0, 0, 900, 700 );
        clear_keybuf();
    }
    key[ KEY_ESC ] = 0;
    destroy_bitmap( surrounding );
}
//tworzy plansze, jej otoczenie, oraz ustawia pionki na pozycjach poczatkowych

void Game::newGame() {
    createFields();
    createPawns();
    play();
}
//rozpoczyna nowa gre

void Game::loadGame() {
    std::ifstream p;
    int take;
    createFields();
    p.open( "saved.txt", std::ios::in );
    p>>si;
    p>>turn;
    for( int i = 0; i < 8; i++ ) {
        for( int j = 0; j < 8; j++ ) {
            p>>take;
            fields[ j ][ i ].setpawnId( take );
            p>>take;
        }
    }
    for( int i = 0; i < 2; i++ ) {
        for( int j = 0; j < 12; j++ ) {
            allPawns[ i ][ j ].setid( i * 12 + j );
            p>>take;
            allPawns[ i ][ j ].setfieldId(static_cast< int >( take ) );
            p>>take;
            allPawns[ i ][ j ].setX(static_cast< int >( take ) );
            p>>take;
            allPawns[ i ][ j ].setY(static_cast< int >( take ) );
            p>>take;
            allPawns[ i ][ j ].setQueen( static_cast< bool >( take ) );
            if( i == 0 ) allPawns[ i ][ j ].setColour( false );
        }
    }
    p.close();
    play();
}
//wczytuje zapisana gre i ja wznawia

void Game::startGame() {
    Button pvpb( 375, 300, 525, 335, "Player vs Player" ), npcb( 375, 240, 525, 275, "Player vs Computer" ),
    loadb( 375, 360, 525, 395, "Wczytaj gre" ), outb( 375, 420, 525, 455, "Wyjdz z gry" );
    bool endGame = false;
    if( ! bufor ) {
        set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
        allegro_message( "Nie moge utworzyc bufora !" );
    }
    while( ! key[ KEY_ESC ] && ! endGame ) {
        clear_to_color( bufor, makecol( 128, 128, 128 ) );
        npcb.show( bufor );
        pvpb.show( bufor );
        loadb.show( bufor );
        outb.show( bufor );
        m.mouse();
        if( m.clickButton( npcb ) ) {
            si = true;
            turn = 1;
            newGame();
        }
        if( m.clickButton( pvpb ) ) {
            si = false;
            turn = 1;
            newGame();
        }
        if( m.clickButton( loadb ) ) loadGame();
        if( m.clickButton( outb ) ) endGame = true;
        blit( bufor, screen, 0, 0, 0, 0, 900, 700 );
        clear_keybuf();
    }
}
//uruchamia gre

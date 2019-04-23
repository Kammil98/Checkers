#include "Npc.h"

void Npc::correctSimulation( Pawn simulatedPawns[ 2 ][ 12 ], BoardField simulatedfields[ 8 ][ 8 ], Jump jump, int turn, int i, bool& changed ){
    Position pos, newpos = jump.pos;
    MovingPawn moving;
    pos.c = simulatedPawns[ turn ][ i ].getfieldId() % 8;
    pos.l = simulatedPawns[ turn ][ i ].getfieldId() / 8;
    if( jump.beat ){
        changed = true;
        moving.removingPawn( NULL, simulatedPawns, simulatedfields, pos, newpos );
        simulatedPawns[ turn ][ i ].setfieldId( jump.pos.l * 8 + jump.pos.c );
        simulatedfields[ jump.pos.c ][ jump.pos.l ].setpawnId( simulatedPawns[ turn ][ i ].getid() );
    }
}
//przesowa na symulacji szachownicy pionka, ktory atakowal i zbija starego pionka

bool Npc::safeJump( Position pos, BoardField fields[ 8 ][ 8 ], int id ) {
    if( pos.c == -100 ) return false;
    if( pos.l > 0 && pos.l < 7 &&  pos.c > 0 && pos.c < 7 ) {
        if( fields[ pos.c + 1 ][ pos.l - 1 ].getpawnId() > 11 && ( fields[ pos.c - 1 ][ pos.l + 1 ].getpawnId() == -1 || fields[ pos.c - 1 ][ pos.l + 1 ].getpawnId() == id ) )return false;
        if( fields[ pos.c - 1 ][ pos.l - 1 ].getpawnId() > 11 && ( fields[ pos.c + 1 ][ pos.l + 1 ].getpawnId() == -1 || fields[ pos.c + 1 ][ pos.l + 1 ].getpawnId() == id ) )return false;
    }
    return true;
}
// sprawdza, czy pionek bedzie zbity przez inny pionek(nie patrzy na damki)

void Npc::cpBoardandField( Pawn allPawns[ 2 ][ 12 ], Pawn simulatedPawns[ 2 ][ 12 ], BoardField fields[ 8 ][ 8 ], BoardField simulatedfields[ 8 ][ 8 ] ) {
    if( allPawns != NULL ){
        for( int i = 0; i < 2; i++ ) {
            for( int j = 0; j < 12; j++ )simulatedPawns[ i ][ j ] = allPawns[ i ][ j ];
        }
    }
    if( fields != NULL ){
        for( int i = 0; i < 8; i++ ){
            for( int j = 0; j < 8; j++ )simulatedfields[ i ][ j ] = fields[ i ][ j ];
        }
    }
}

void Npc::willNotDieByPawn( Pawn allPawns[ 2 ][ 12 ], BoardField fields[ 8 ][ 8 ] ) {
    bool cansurvive = false;
    bool livingPawn[ 12 ][ 4 ];
    for( int i = 0; i < 12; i++ ) if( choosePawn[ i ].use ) {
        for( int j = 0; j < 4; j++ ) {
            livingPawn[ i ][ j ] = safeJump( choosePawn[ i ].jump[ j ].pos, fields, choosePawn[ i ].pawn.getid() );
        }
    }
    else{
        for( int j = 0; j < 4; j++ )livingPawn[ i ][ j ] = false;
    }
    for( int i = 0; i < 12; i++ ) {
        for( int j = 0; j < 4; j++ )if( livingPawn[ i ][ j ] ) cansurvive = true;
    }
    if( cansurvive ) {
        for( int i = 0; i < 12; i++ ) {
            for( int j = 0; j < 4; j++ ) {
                if( ! livingPawn[ i ][ j ] ) choosePawn[ i ].jump[ j ].pos.c = choosePawn[ i ].jump[ j ].pos.l = -100;
            }
            if( choosePawn[ i ].jump[ 0 ].pos.c + choosePawn[ i ].jump[ 1 ].pos.c + choosePawn[ i ].jump[ 2 ].pos.c + choosePawn[ i ].jump[ 3 ].pos.c == -400 ) choosePawn[ i ].use = false;
        }
    }
}
//sprawdza czy istnieje pionek, ktory nie bedzie zbity

void Npc::haveBeat( Pawn allPawns[ 2 ][ 12 ], BoardField fields[ 8 ][ 8 ], int turn ) {
    Pawn simulatedPawns[ 2 ][ 12 ];
    BoardField simulatedfields[ 8 ] [8 ];
    bool changed = false;
    int beatingPawn[ 12 ], maks = 0;
    Position pos;
    Jump jump[4];
    for( int i = 0; i < 12; i++ ) beatingPawn[ i ] = 0;
    for( int i = 0; i < 12; i++ ) {
        if( choosePawn[ i ].use ) {
            cpBoardandField( allPawns, simulatedPawns, fields, simulatedfields );
            do{
                pos.c = simulatedPawns[ turn ][ i ].getfieldId() % 8;
                pos.l = simulatedPawns[  turn ][ i ].getfieldId() / 8;
                moving.possibleJumps( simulatedfields, simulatedPawns[ turn ][ i ], pos, turn, jump );
                for( int j = 0; j < 4; j++) correctSimulation( simulatedPawns, simulatedfields, jump[ j ], turn, i, changed );
                if( changed ) {
                    beatingPawn[ i ] += 2;
                    changed = false;
                }
            }while( moving.canBeat( jump ) );
            if( ! safeJump(pos, fields, simulatedPawns[ turn ][ i ].getfieldId() ) ) beatingPawn[ i ] -= 1;
        }
    }
    for( int i = 0; i < 12 ;i++ ) { //sprawdza ile mozna maksymalnie zbic
        if( maks < beatingPawn[ i ] )maks = beatingPawn[ i ];
    }
    if( maks != 0 ){ //wybiera maksymalna liczbe zbic, jesli mozna w ogole cos zbic
        for( int i = 0; i < 12 ;i++ ) {
            if( maks != beatingPawn[ i ] ) {
                for( int j = 0; j < 4; j++ )choosePawn[ i ].jump[ j ].pos.c = choosePawn[ i ].jump[ j ].pos.l = -100;
                choosePawn[ i ].use = false;
            }
            else{
                for( int j =0; j < 4; j++ ) {
                    if( ! choosePawn[ i ].jump[ j ].beat )choosePawn[ i ].jump[ j ].pos.c = choosePawn[ i ].jump[ j ].pos.l = -100;
                }
            }
        }
    }
}
//sprawdza ile mozna maksymalnie zbic pionkow z uwzglednieniem stracenia pionka, ktory bil

void Npc::closeToEdge() {
    int fieldId, maks = 0, priority[ 12 ][ 4 ];
    Position pos, newpos;
    for( int i = 0; i < 12; i++ ) if( choosePawn[ i ].use ) {
        fieldId = choosePawn[ i ].pawn.getfieldId();
        pos.c = fieldId % 8;
        pos.l = fieldId / 8;
        for( int j = 0; j < 4; j++ ) {
            newpos = choosePawn[ i ].jump[ j ].pos;
            priority[ i ][ j ] = 0;
            if( newpos.c != -100 ) {
                if( choosePawn[ i ].pawn.getQueen() ) {
                    if( newpos.l == 7 ) priority[ i ][ j ] += 30; //tylko dla czarnej damki - idzie na linie poczatkowa
                    if( ( ( 7 - newpos.c < 3 && pos.c < newpos.c ) || ( newpos.c < 3 && newpos.c < pos.c ) ) && pos.l != 7  ) priority[ i ][ j ] += 25; // idzie do krawedzi bocznej
                }
                else{
                    if( newpos.l == 0 && ! choosePawn[ i ].pawn.getQueen() ) priority[ i ][ j ] += 100; //czarny pionek zamienia sie w damke
                    if( newpos.l < 3 && pos.l > newpos.l ) priority[ i ][ j ] += 20; //idzie do konca planszy
                    if( newpos.c == 0 || newpos.c == 7 ) priority[ i ][ j ] += 10; //dochodzi do krawedzi bocznej
                    if( ( 7 - newpos.c < 3 && pos.c < newpos.c ) || ( newpos.c < 3 && newpos.c < pos.c ) ) priority[ i ][ j ] += 5; // idzie do krawedzi bocznej
                }
                if( pos.c == 7 || pos.c == 0 || pos.l == 0 || pos.l == 7 ) priority[ i ][ j ] -= 25; //jest na krawedzi
            }
        }
    }
    else{
        for( int j = 0; j < 4; j++ ) priority[ i ][ j ] = 0;
    }
    for( int i = 0; i < 12; i++ ) {
        for( int j = 0; j < 4; j++ ) {
            if( maks < priority[ i ][ j ] ) maks = priority[ i ][ j ];
        }
    }
    if( maks != 0 ) {
        for( int i = 0; i < 12; i++ ) {
            for( int j = 0; j < 4; j++ ) {
                if( maks != priority[ i ][ j ] )choosePawn[ i ].jump[ j ].pos.c = choosePawn[ i ].jump[ j ].pos.l = -100;
            }
            if( choosePawn[ i ].jump[ 0 ].pos.c + choosePawn[ i ].jump[ 1 ].pos.c + choosePawn[ i ].jump[ 2 ].pos.c + choosePawn[ i ].jump[ 3 ].pos.c == -400 ) choosePawn[ i ].use = false;
        }
    }
}
//wybiera pionka, ktory najkorzystniej zbliza sie do krawedzi

void Npc::guardEnd() {
    bool movable = false;
    for( int i = 0; i < 12; i++ ) if( choosePawn[ i ].use ) {
        if( choosePawn[ i ].pawn.getfieldId() / 8 != 7 ) movable = true;
    }
    if(movable){
        for( int i = 0; i < 12; i++ ) {
            if( choosePawn[ i ].pawn.getfieldId() / 8 == 7 ) {
                choosePawn[ i ].use = false;
                for( int j = 0; j < 4; j++ )choosePawn[ i ].jump[ j ].pos.c = choosePawn[ i ].jump[ j ].pos.l = -100;
            }
        }
    }
}

bool Npc::isOcuppied( BoardField fields[ 8 ][ 8 ], Position pos, int dir ) {
    return  ! ( fields[ pos.c + dir ][ pos.l + 1 ].getpawnId() != -1 && fields[ pos.c + dir ][ pos.l + 1 ].getpawnId() < 12  && fields[ pos.c + 2 * dir ][ pos.l + 2 ].getpawnId() == -1 );
}
// sprawdza, czy pionek za wskazana pozycja moze byc zbity

void Npc::antyMultikill( BoardField fields[ 8 ][ 8 ] ) {
    int fieldId;
    Position pos;
    bool multikill[ 12 ], movable = false;
    for( int i = 0; i < 12; i++ ){
        multikill[ i ] = true;
        if( choosePawn[ i ].use ) {
            fieldId = choosePawn[ i ].pawn.getfieldId();
            pos.c = fieldId % 8;
            pos.l = fieldId / 8;
            if( pos.l < 2 || ( ( pos.c < 2 || isOcuppied( fields, pos, -1 ) ) && ( pos.c > 5 || isOcuppied( fields, pos, 1 ) ) ) ) multikill[ i ] = false;
        }
    }
    for( int i = 0; i < 12; i++ ) {
        if( ! multikill[ i ] ) movable = true;
    }
    if( movable ){
        for( int i = 0; i < 12; i++ ) {
            if( multikill[ i ] ) choosePawn[ i ].use = false;
        }
    }
}
//sprawdza czy mozliwe jest stracenie tylko jednego pionka

void Npc::movePawn(BITMAP *bufor, Pawn allPawns[ 2 ][ 12 ], BoardField fields[ 8 ][ 8 ], int turn ){
    int chosedpawn = 0, chosedjump = 0, fieldId;
    Position pos, newpos;
    while( ! choosePawn[ chosedpawn ].use ) chosedpawn++;
    while( choosePawn[ chosedpawn ].jump[ chosedjump ].pos.c == -100 ) chosedjump++;
    if( choosePawn[ chosedpawn ].jump[ chosedjump ].beat ) {
        while( moving.canBeat( choosePawn[ chosedpawn ].jump ) ) {
            fieldId = choosePawn[ chosedpawn ].pawn.getfieldId();
            pos.c = fieldId % 8;
            pos.l = fieldId / 8;
            chosedjump = 0;
            while( ! choosePawn[ chosedpawn ].jump[ chosedjump ].beat ) chosedjump++;
            newpos = choosePawn[ chosedpawn ].jump[ chosedjump ].pos;
            moving.removingPawn( bufor, allPawns, fields, pos, newpos );
            allPawns[ turn ][ chosedpawn ].go( bufor, fields[ pos.c ][ pos.l ], fields[ newpos.c ][ newpos.l ] );
            choosePawn[ chosedpawn ].pawn.go( bufor, fields[ pos.c ][ pos.l ], fields[ newpos.c ][ newpos.l ] );
            pos = newpos;
            moving.possibleJumps( fields, choosePawn[ chosedpawn ].pawn, pos, turn, choosePawn[ chosedpawn ].jump );
        }
    }
    else{
        fieldId = choosePawn[ chosedpawn ].pawn.getfieldId();
        pos.c = fieldId % 8;
        pos.l = fieldId / 8;
        newpos = choosePawn[ chosedpawn ].jump[ chosedjump ].pos;
        allPawns[ turn ][ chosedpawn ].go( bufor, fields[ pos.c ][ pos.l ], fields[ newpos.c ][ newpos.l ] );
        pos = newpos;
    }
    moving.isItQueen( bufor, allPawns[ turn ][ chosedpawn ], turn );
}
//wykonuje ruch

void Npc::npcThink( BITMAP *bufor, Pawn allPawns[ 2 ][ 12 ], BoardField fields[ 8 ][ 8 ], int& turn, Button whob, Button warningb ) {
    int fieldId;
    bool mandatory = false;
    Position pos;
    for( int i = 0; i < 12; i++ ) {
        choosePawn[ i ].pawn = allPawns[ turn ][ i ];
        fieldId = choosePawn[ i ].pawn.getfieldId();
        pos.c = fieldId % 8;
        pos.l = fieldId / 8;
        moving.possibleJumps( fields, choosePawn[ i ].pawn, pos, turn, choosePawn[ i ].jump );
        if( ! mandatory && moving.canBeat( choosePawn[ i ].jump ) ) mandatory = true; //czy jest obowiazkowe bicie
        if( choosePawn[ i ].jump[ 0 ].pos.c + choosePawn[ i ].jump[ 1 ].pos.c + choosePawn[ i ].jump[ 2 ].pos.c + choosePawn[ i ].jump[ 3 ].pos.c == -400 || fieldId == -1 )
            choosePawn[ i ].use = false; //czy pionek moze sie ruszyc
        else
            choosePawn[ i ].use = true;
    }
    haveBeat( allPawns, fields,turn );
    willNotDieByPawn( allPawns, fields );
    closeToEdge();
    antyMultikill( fields );
    guardEnd();
    movePawn( bufor, allPawns, fields, turn );
    if( turn ) {
        whob.settext2( "czarnego" );
        whob.settxtColour( 0 );
        whob.setborderColour( 0 );
    }
    else{
        whob.settext2( "bialego" );
        whob.settxtColour( 255 );
        whob.setborderColour( 255 );
    }
    whob.show( bufor );
    turn = ( turn + 1 ) % 2;
    if( moving.mandatoryJump( allPawns, fields, turn ) )warningb.show( bufor ); //czy obowiazkowe bicie w turze przeciwnika
    else warningb.hide( bufor );
    blit( bufor, screen, 0, 0, 0, 0, 900, 700 );
}
//mysli, ktory pionek wybrac

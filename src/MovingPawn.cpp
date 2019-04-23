#include "MovingPawn.h"
#include "Button.h"
bool MovingPawn::canBeat(Jump jump[4]){
    return jump[ 0 ].beat || jump[ 1 ].beat || jump[ 2 ].beat || jump[ 3 ].beat;
}
bool MovingPawn::inRangeOfBoard(int column, int line ) {
    return ( column < 8 && line < 8 && column >= 0 && line >= 0 );
}
void MovingPawn::isItQueen( BITMAP *bufor, Pawn& pawn, int& turn ){
    if( turn == 1 && pawn.getfieldId() > 55 ){
        pawn.setQueen( true );
        pawn.show( bufor ) ;
    }
    if( turn == 0 && pawn.getfieldId() < 8 ){
        pawn.setQueen( true );
        pawn.show( bufor );
    }
}
void MovingPawn::checkJump( BoardField fields[ 8 ][ 8 ], Pawn pawn, int turn, Jump& jump, int dirc, int dirl ){
    bool moved = false;
    int startPosition = jump.pos.c ;
    if( inRangeOfBoard( jump.pos.c + dirc, jump.pos.l + dirl ) && fields[ jump.pos.c + dirc ][ jump.pos.l + dirl ].getpawnId() == -1 ){ //ruszenie do przodu
        jump.pos.c += dirc;
        jump.pos.l += dirl;
        moved=true;
    }
    while( pawn.getQueen() && inRangeOfBoard( jump.pos.c + dirc, jump.pos.l + dirl ) && fields[ jump.pos.c + dirc ][ jump.pos.l + dirl ].getpawnId() == -1 ) { //ruszenie do przodu damki
        jump.pos.c += dirc;
        jump.pos.l += dirl;
    }
    if(( pawn.getQueen() || ! moved ) && inRangeOfBoard( jump.pos.c + 2 * dirc, jump.pos.l + 2 * dirl )
       && fields[ jump.pos.c + dirc ][ jump.pos.l + dirl ].getpawnId() != -1
       && fields[ jump.pos.c + dirc ][ jump.pos.l + dirl ].getpawnId() / 12 == 1 - turn && fields[ jump.pos.c + 2 * dirc ][ jump.pos.l + 2 * dirl ].getpawnId() == -1 ){ //zbicie
        jump.pos.c += 2 * dirc;
        jump.pos.l += 2 * dirl;
        jump.beat = true;
    }
    if( jump.pos.c == startPosition || pawn.getfieldId() == -1 ){
        jump.pos.c = -100;
        jump.pos.l = -100;
    }
}
void MovingPawn::possibleJumps( BoardField fields[ 8 ][ 8 ],Pawn pawn, Position pos, int turn, Jump jump[ 4 ] ){
    jump[ 0 ].beat = jump[ 1 ].beat = jump[ 2 ].beat = jump[ 3 ].beat = false;// jump1 bicie w prawo i gore 2 bicie w lewo i gore 3 bicie w prawo i dol 4 bicie w lewo i dol
    if(pawn.getQueen()){
        jump[ 0 ].pos.c = jump[ 1 ].pos.c = jump[ 2 ].pos.c = jump[ 3 ].pos.c = pos.c;
        jump[ 0 ].pos.l = jump[ 1 ].pos.l = jump[ 2 ].pos.l = jump[ 3 ].pos.l = pos.l;
        checkJump( fields, pawn, turn, jump[ 0 ], 1, 1 );
        checkJump( fields, pawn, turn, jump[ 1 ], -1, 1 );
        checkJump( fields, pawn, turn, jump[ 2 ], 1, -1 );
        checkJump( fields, pawn, turn, jump[ 3 ], -1, -1 );
    }
    else{
        if( turn == 1 ){
            jump[ 0 ].pos.c = jump[ 1 ].pos.c = pos.c;
            jump[ 0 ].pos.l = jump[ 1 ].pos.l = pos.l;
            jump[ 2 ].pos.c = jump[ 3 ].pos.c = jump[ 2 ].pos.l = jump[ 3 ].pos.l = -100;
            checkJump( fields, pawn, turn, jump[ 0 ], 1, 1 );
            checkJump( fields, pawn, turn, jump[ 1 ], -1, 1 );
        }
        else{
            jump[ 2 ].pos.c = jump[ 3 ].pos.c = pos.c;
            jump[ 2 ].pos.l = jump[ 3 ].pos.l = pos.l;
            jump[ 0 ].pos.c = jump[ 1 ].pos.c = jump[ 0 ].pos.l = jump[ 1 ].pos.l = -100;
            checkJump( fields, pawn, turn, jump[ 2 ], 1, -1 );
            checkJump( fields, pawn, turn, jump[ 3 ], -1, -1 );
        }
    }
}
void MovingPawn::removingPawn( BITMAP* bufor, Pawn allPawns[ 2 ][ 12 ], BoardField fields[ 8 ][ 8 ], Position pos, Position newpos ){
    Position beatpos = newpos;
    if( beatpos.c - pos.c > 0 )beatpos.c--;
    if( beatpos.c - pos.c < 0 )beatpos.c++;
    if( beatpos.l - pos.l > 0 )beatpos.l--;
    if( beatpos.l - pos.l < 0 )beatpos.l++;
    int pawnId = fields[ beatpos.c ][ beatpos.l ].getpawnId();
    allPawns[ pawnId / 12 ][ pawnId % 12 ].setBeated( true );
    allPawns[ pawnId / 12 ][ pawnId % 12 ].setfieldId( -1 );
    fields[ beatpos.c ][ beatpos.l ].setpawnId( -1 );
    if( bufor != NULL )fields[ beatpos.c ][ beatpos.l ].show( bufor );
}
bool MovingPawn::mandatoryJump( Pawn allPawns[ 2 ][ 12 ], BoardField fields[ 8 ][ 8 ], int turn ){
    Position pos;
    int pawnId;
    Jump jump[ 4 ];
    for( int i = 0; i < 12; i++ ){
        pawnId = allPawns[ turn ][ i ].getfieldId();
        if( pawnId != -1 ){
            pos.c = pawnId % 8;
            pos.l = pawnId / 8;
            possibleJumps( fields, allPawns[ turn ][ i ], pos, turn, jump );
            if( canBeat( jump ) ) return true;
        }
    }
    return false;
}
int MovingPawn::canGo( Position pos, Position newpos, Jump jump[ 4 ] ){
    //return 0 == nie mozna tam isc 1== mozna tam isc 2== mozna tam bic
    if( jump[ 0 ].beat && jump[ 0 ].pos.c == newpos.c && jump[ 0 ].pos.l == newpos.l ) return 2;
    else{
        if( pos.c < newpos.c && pos.l < newpos.l && newpos.c <= jump[ 0 ].pos.c && newpos.l <= jump[ 0 ].pos.l && jump[ 0 ].pos.c - newpos.c == jump[ 0 ].pos.l - newpos.l ) return 1;
    }
    if( jump[ 1 ].beat && jump[ 1 ].pos.c == newpos.c && jump[ 1 ].pos.l == newpos.l ) return 2;
    else{
        if( pos.c > newpos.c && pos.l < newpos.l && newpos.c >= jump[ 1 ].pos.c && newpos.l <= jump[ 1 ].pos.l && newpos.c - jump[ 1 ].pos.c == jump[ 1 ].pos.l - newpos.l ) return 1;
    }
    if( jump[ 2 ].beat && jump[ 2 ].pos.c == newpos.c && jump[ 2 ].pos.l == newpos.l )return 2;
    else{
        if(pos.c < newpos.c && pos.l > newpos.l && newpos.c <= jump[ 2 ].pos.c && newpos.l >= jump[ 2 ].pos.l && jump[ 2 ].pos.c - newpos.c == newpos.l - jump[ 2 ].pos.l ) return 1;
    }
    if( jump[ 3 ].beat && jump[ 3 ].pos.c == newpos.c && jump[ 3 ].pos.l == newpos.l )return 2;
    else{
        if( pos.c > newpos.c && pos.l > newpos.l && newpos.c >= jump[ 3 ].pos.c && newpos.l >= jump[ 3 ].pos.l && newpos.c - jump[ 3 ].pos.c == newpos.l - jump[ 3 ].pos.l ) return 1;
    }
    return 0;
}
void MovingPawn::movePawn( BITMAP *bufor, Pawn allPawns[ 2 ][ 12 ], BoardField fields[ 8 ][ 8 ], int& turn, MouseAndKeyboard m, Button whob, Button warningb ){
    Position pos, newpos;
    int pawnId;
    Jump jump[ 4 ];// jumpX = -100 znaczy, ze skok jest niemozliwy jump. 1 bicie w prawo i gore 2 bicie w lewo i gore 3 bicie w prawo i dol 4 bicie w lewo i dol
    bool moved = false, mandatory = mandatoryJump( allPawns, fields, turn );
    do{//moge dokonac wybranym pionkiem bicia i mam pionka ktorym moge dokonac bicia
        m.mousePosition( pos );
        if( inRangeOfBoard( pos.c, pos.l ) ) {
            possibleJumps( fields, allPawns[ turn ][ fields[ pos.c ][ pos.l ].getpawnId() % 12 ], pos, turn, jump );
        }
    }while( inRangeOfBoard( pos.c, pos.l ) &&  mandatory && ! canBeat( jump ) );

    if( inRangeOfBoard( pos.c, pos.l ) ) {
        pawnId = fields[ pos.c ][ pos.l ].getpawnId();
        if( pawnId >= 12 * turn && pawnId < 12 * turn + 12 ) { //pionek nalezy do wlasciwej druzyny
            allPawns[ pawnId / 12 ][ pawnId % 12 ].show( bufor, true );
            m.mousePosition( newpos );
            if( canGo( pos, newpos, jump ) == 2 || ( ! mandatory && canGo( pos, newpos, jump ) == 1 )) { //wybrany pionek moze tam bic lub (isc, gdy nie ma mozliwego bicia)
                while( mandatory && canBeat( jump ) ) { //jest obowiazkowe bicie i mozliwe kolejne bicie wybranym pionkiem
                    if( canGo( pos, newpos, jump ) == 2 ) { //uzytkownik chce zbic pionek i wybiera jeden z mozliwych ruchow
                        removingPawn( bufor, allPawns, fields, pos, newpos );
                        allPawns[ turn ][ pawnId % 12 ].go( bufor, fields[ pos.c ][ pos.l ], fields[ newpos.c ][ newpos.l ] );
                        moved = true;
                        pos = newpos;
                        pawnId = fields[ pos.c ][ pos.l ].getpawnId();
                        possibleJumps( fields, allPawns[ turn ][ pawnId % 12 ], pos, turn, jump );
                        mandatory = mandatoryJump( allPawns, fields, turn );
                    }
                    blit( bufor, screen, 0, 0, 0, 0, 900, 700 );
                    if( canBeat( jump ) ){//mozliwe jest kolejne bicie tym pionkiem
                        allPawns[ turn ][ pawnId % 12 ].show( bufor, true );
                        m.mousePosition( newpos );
                    }
                }
                if( ! moved ){
                    allPawns[ turn ][ pawnId % 12 ].go( bufor, fields[ pos.c ][ pos.l ], fields[ newpos.c ][ newpos.l ] );
                    pos = newpos;
                    pawnId = fields[ pos.c ][ pos.l ].getpawnId();
                    moved = true;
                }
            }
            else {
                allPawns[ turn ][ pawnId % 12 ].show( bufor );
            }
            if( moved ){
                isItQueen( bufor, allPawns[ turn ][ pawnId % 12 ], turn );
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
                if( mandatoryJump( allPawns, fields, turn ) )warningb.show( bufor ); //czy obowiazkowe bicie w turze przeciwnika
                else warningb.hide( bufor );
            }
        }
    }
}

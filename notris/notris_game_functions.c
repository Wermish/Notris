#include <stdio.h>
#include <Windows.h>
#include "../shared/shared_game_functions.h"
#include "../shared/shared_graphics_functions.h"
#include "notris_game_functions.h"
#include "notris_graphics_functions.h"
#include "notris_structures.h"

/*
 * Shape of piece is formed relative to coord of leading block, blockOne.
 */

struct notrisPiece* notris_create_piece( enum notrisPieceShape pieceShape, struct notrisPlayFieldInfo* npfiInfo ){

    notrisPiece *piece = malloc( sizeof( notrisPiece ) ) ;
    
    piece->pieceShape = pieceShape ;
    piece->piecePhase = 0 ;
    piece->pieceLook.Char.AsciiChar = 219 ;

    piece->blockOne.X = ( npfiInfo->playFieldArea.Left + npfiInfo->playFieldArea.Right ) / 2 ; // 24
    piece->blockOne.Y = npfiInfo->playFieldArea.Top ; // 4

    switch( pieceShape )
    {   // Square
        case 1:
            piece->blockTwo.X = piece->blockOne.X + 1 ; 
            piece->blockTwo.Y = piece->blockOne.Y ;
            piece->blockThree.X = piece->blockOne.X ;
            piece->blockThree.Y = piece->blockOne.Y + 1 ;
            piece->blockFour.X = piece->blockOne.X + 1 ;
            piece->blockFour.Y = piece->blockOne.Y + 1 ;
            piece->pieceLook.Attributes = FOREGROUND_RED ;
            
            break ;
        // Line
        case 2:
            piece->blockTwo.X = piece->blockOne.X ;
            piece->blockTwo.Y = piece->blockOne.Y + 1 ;
            piece->blockThree.X = piece->blockOne.X ;
            piece->blockThree.Y = piece->blockOne.Y + 2 ;
            piece->blockFour.X = piece->blockOne.X ;
            piece->blockFour.Y = piece->blockOne.Y + 3 ;
            piece->pieceLook.Attributes = FOREGROUND_GREEN ;
            break ;
        // 'L'
        case 3:
            piece->blockTwo.X = piece->blockOne.X ;
            piece->blockTwo.Y = piece->blockOne.Y + 1 ;
            piece->blockThree.X = piece->blockOne.X ;
            piece->blockThree.Y = piece->blockOne.Y + 2 ;
            piece->blockFour.X = piece->blockOne.X + 1 ;
            piece->blockFour.Y = piece->blockOne.Y + 2 ;
            piece->pieceLook.Attributes = FOREGROUND_GREEN | FOREGROUND_RED ;
            break ;
        // Mirrored 'L'
        case 4:
            piece->blockTwo.X = piece->blockOne.X ;
            piece->blockTwo.Y = piece->blockOne.Y + 1 ;
            piece->blockThree.X = piece->blockOne.X ;
            piece->blockThree.Y = piece->blockOne.Y + 2 ;
            piece->blockFour.X = piece->blockOne.X - 1 ;
            piece->blockFour.Y = piece->blockOne.Y + 2 ;
            piece->pieceLook.Attributes = FOREGROUND_BLUE | FOREGROUND_RED ;
            break ;
        // 'Z'
        case 5:
            piece->blockTwo.X = piece->blockOne.X + 1 ;
            piece->blockTwo.Y = piece->blockOne.Y ;
            piece->blockThree.X = piece->blockOne.X + 1 ;
            piece->blockThree.Y = piece->blockOne.Y + 1 ;
            piece->blockFour.X = piece->blockOne.X + 2 ;
            piece->blockFour.Y = piece->blockOne.Y + 1 ;
            piece->pieceLook.Attributes = FOREGROUND_GREEN | FOREGROUND_BLUE ;
            break ;
        // Mirrored 'Z'
        case 6:
            piece->blockTwo.X = piece->blockOne.X - 1 ;
            piece->blockTwo.Y = piece->blockOne.Y ;
            piece->blockThree.X = piece->blockOne.X - 1 ;
            piece->blockThree.Y = piece->blockOne.Y + 1 ;
            piece->blockFour.X = piece->blockOne.X - 2 ;
            piece->blockFour.Y = piece->blockOne.Y + 1 ;
            piece->pieceLook.Attributes =  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY ;
            break ;
        // 'Hat'    
        case 7:
            piece->blockTwo.X = piece->blockOne.X ;
            piece->blockTwo.Y = piece->blockOne.Y + 1 ;
            piece->blockThree.X = piece->blockOne.X - 1 ;
            piece->blockThree.Y = piece->blockOne.Y + 1 ;
            piece->blockFour.X = piece->blockOne.X + 1 ;
            piece->blockFour.Y = piece->blockOne.Y + 1 ;
            piece->pieceLook.Attributes = FOREGROUND_BLUE ;
            break ;  
    }

    return piece ;
}

void notris_move_piece( HANDLE* phInputBuffer, struct notrisPlayFieldInfo* npfiInfo, struct notrisPiece* piece )
{
    DWORD numberOfEvents = 0 ;
    DWORD numberOfEventsRead = 0 ;

    GetNumberOfConsoleInputEvents( *phInputBuffer, &numberOfEvents ) ;

        if( numberOfEvents )
        {
            INPUT_RECORD* inputRecordArray = malloc( sizeof( INPUT_RECORD ) * numberOfEvents ) ;

            ReadConsoleInput( *phInputBuffer, inputRecordArray, numberOfEvents, &numberOfEventsRead ) ;

            for( int i = 0; i < numberOfEventsRead; i++ )
            {
                if( inputRecordArray[i].EventType == KEY_EVENT )
                {
                    
                    if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE )
                    {
                        if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                        {
                            exit( EXIT_SUCCESS ) ;
                        }
                    }
                    // Pauses the game. Incidentally also causes the piece to vanish while paused as loop is entered before piece is redrawn.
                    if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_TAB )
                    {
                        BOOL loopBreak = 1 ;

                        if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                        {
                            while( loopBreak )
                            {   
                                 DWORD numberOfEventsInner = 0 ;
                                 DWORD numberOfEventsReadInner = 0 ;

                                GetNumberOfConsoleInputEvents( *phInputBuffer, &numberOfEventsInner ) ;

                                if( numberOfEventsInner )
                                {
                                    INPUT_RECORD* inputRecordArrayInner = malloc( sizeof( INPUT_RECORD ) * numberOfEventsInner ) ;

                                    ReadConsoleInput( *phInputBuffer, inputRecordArrayInner, numberOfEventsInner, &numberOfEventsReadInner ) ;

                                    for( int i = 0; i < numberOfEventsReadInner; i++ )
                                    {
                                        if( inputRecordArrayInner[i].EventType == KEY_EVENT )
                                        {
                                            if( inputRecordArrayInner[i].Event.KeyEvent.wVirtualKeyCode == VK_TAB )
                                            {
                                                if( inputRecordArrayInner[i].Event.KeyEvent.bKeyDown )
                                                {
                                                    free( inputRecordArrayInner ) ;
                                                    loopBreak = 0 ;
                                                }
                                            }
                                        }
                                    }
                                }            
                            }
                        }
                    }

                    else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_SPACE )
                    {
                        if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                        {
                            notris_rotate_piece_clockwise( piece ) ;
                        }
                    }

                    else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_DOWN )
                    {
                        if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                        {
                            piece->blockOne.Y++ ;
                            piece->blockTwo.Y++ ;
                            piece->blockThree.Y++ ;
                            piece->blockFour.Y++ ;
                        }
                    }
                    else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_LEFT )
                    {
                        if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                        {
                                piece->blockOne.X-- ;
                                piece->blockTwo.X-- ;
                                piece->blockThree.X-- ;
                                piece->blockFour.X-- ;
                        }
                    }
                    else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_RIGHT )
                    {
                        if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                        {
                            piece->blockOne.X++ ;
                            piece->blockTwo.X++ ;
                            piece->blockThree.X++ ;
                            piece->blockFour.X++ ;
                        }
                    }
                }
            }
            free( inputRecordArray ) ;
        }
}

/*
 * Rotates piece based on current 'phase', or the degree of rotation from starting position.
 */

void notris_rotate_piece_clockwise( struct notrisPiece* piece )
{
    switch( piece->pieceShape ){
        // Square
        case 1:
            break ;
        // Line
        case 2:
             switch( piece->piecePhase )
            {
                case 0:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.X -= 2 ;
                    piece->blockFour.Y -= 2 ;
                    piece->piecePhase = 1 ;
                break ;

                case 1:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.X += 2 ;
                    piece->blockFour.Y += 2 ;
                    piece->piecePhase = 0 ;
                break ;
            }
        break ;
        // 'L'
        case 3:
             switch( piece->piecePhase )
            {
                case 0:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.X -= 2 ;
                    piece->piecePhase = 1 ;
                break ;

                case 1:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.Y -= 2 ;
                    piece->piecePhase = 2 ;
                break ;

                case 2:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.X += 2 ;
                    piece->piecePhase = 3 ;
                break ;

                case 3:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.Y += 2 ;
                    piece->piecePhase = 0 ;
                break ;
            }
            break ;
        // Mirrored 'L'
        case 4:
            switch( piece->piecePhase )
            {
                case 0:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.Y -= 2 ;
                    piece->piecePhase = 1 ;
                break ;

                case 1:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.X += 2 ;
                    piece->piecePhase = 2 ;
                break ;

                case 2:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.Y += 2 ;
                    piece->piecePhase = 3 ;
                break ;

                case 3:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.X -= 2 ;
                    piece->piecePhase = 0 ;
                break ;
            }
            break ;
        // 'Z'
        case 5:
            switch( piece->piecePhase )
            {
                case 0:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.X -= 2 ;
                    piece->piecePhase = 1 ;
                break ;

                case 1:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.X += 2 ;
                    piece->piecePhase = 0 ;
                break ;
            }
            break ;
        // Mirrored 'Z'
        case 6:
            switch( piece->piecePhase )
            {
                case 0:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.Y -= 2 ;
                    piece->piecePhase = 1 ;
                break ;

                case 1:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.Y += 2 ;
                    piece->piecePhase = 0 ;
                break ;
            }
            break ;
        // 'Hat'
        case 7:
            switch( piece->piecePhase )
            {
                case 0:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.X-- ;
                    piece->blockFour.Y++ ;
                    piece->piecePhase = 1 ;
                break ;

                case 1:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.X-- ;
                    piece->blockFour.Y-- ;
                    piece->piecePhase = 2 ;
                break ;

                case 2:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.X++ ;
                    piece->blockFour.Y-- ;
                    piece->piecePhase = 3 ;
                break ;

                case 3:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.X++ ;
                    piece->blockFour.Y++ ;
                    piece->piecePhase = 0 ;
                break ;
            }
        break ;
    }
}

void notris_setup( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisPlayFieldInfo* npfiInfo )
{
    npfiInfo->playFieldArea.Left = ( csbiInfo->srWindow.Right / 2 ) - 6 ;
    npfiInfo->playFieldArea.Top =  (csbiInfo->srWindow.Bottom / 2) - 10 ;
    npfiInfo->playFieldArea.Right = ( csbiInfo->srWindow.Right / 2 ) + 6 ;
    npfiInfo->playFieldArea.Bottom =  (csbiInfo->srWindow.Bottom / 2) + 10 ;

    npfiInfo->notrisScore = 0 ;

    npfiInfo->nextPiece = random_number_in_range( 1, 7 ) ; 
}

void play_notris( HANDLE* hScreenBufferOne, HANDLE* hScreenBufferTwo, HANDLE* hInputBuffer, 
                  CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisPlayFieldInfo* npfiInfo )
{ 
    HANDLE* phVisible= hScreenBufferOne ;
    HANDLE* phNotVisible = hScreenBufferTwo ;

    WORD pieceDropRate = 0 ;
    BOOL pieceFalling = 1 ;

    notris_setup( csbiInfo, npfiInfo ) ;

    srand( time( 0 ) ) ;

    notrisPiece *p = notris_create_piece( random_number_in_range( 1, 7 ), npfiInfo ) ;
       
    while( pieceFalling )
    {   
        clear_screen_buffer( phNotVisible, csbiInfo ) ;

        notris_draw_UI( phNotVisible, csbiInfo, npfiInfo ) ;

        notris_move_piece( hInputBuffer, npfiInfo, p ) ;

        notris_draw_piece( phNotVisible , p ) ;

        SetConsoleActiveScreenBuffer( *phNotVisible ) ;
        
        if( *phNotVisible == hScreenBufferTwo )
        {
            phNotVisible = hScreenBufferOne ;
            phVisible= hScreenBufferTwo ;
        }
        else
        {
            phNotVisible = hScreenBufferTwo ;
            phVisible= hScreenBufferOne ;
        }

        pieceDropRate++ ;

        if( pieceDropRate == 10 )
        {
            pieceDropRate = 0 ;

            p->blockOne.Y++ ;
            p->blockTwo.Y++ ;
            p->blockThree.Y++ ;
            p->blockFour.Y++ ;
        }

        

        Sleep( 50 ) ;
    }

    free( p ) ;
}
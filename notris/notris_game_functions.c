#include <stdio.h>
#include <Windows.h>
#include "../shared/shared_game_functions.h"
#include "notris_game_functions.h"
#include "notris_structures.h"

/*
 * Shape of piece is formed relative to coord of leading block, blockOne.
 */

struct notrisPiece* generate_notris_piece( enum notrisPieceShape pieceShape, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo ){

    notrisPiece *piece = malloc( sizeof( notrisPiece ) ) ;
    
    piece->pieceShape = pieceShape ;
    piece->piecePhase = 0 ;
    piece->pieceLook.Char.AsciiChar = 219 ;

    
    piece->blockOne.X = csbiInfo->dwSize.X / 2 ;
    piece->blockOne.Y = csbiInfo->dwSize.Y / 10 ;

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

void move_notris_piece( HANDLE* phInputBuffer, notrisPiece* piece )
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

                    else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_SPACE )
                    {
                        if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                        {
                            rotate_notris_piece( piece ) ;
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

void rotate_notris_piece( struct notrisPiece* piece )
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

void setup_notris( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisPlayFieldInfo* npfiInfo )
{
    
    npfiInfo->playFieldArea.Left = ( csbiInfo->srWindow.Right / 2 ) - 6 ;
    npfiInfo->playFieldArea.Top =  (csbiInfo->srWindow.Bottom / 2) - 10 ;
    npfiInfo->playFieldArea.Right = ( csbiInfo->srWindow.Right / 2 ) + 6 ;
    npfiInfo->playFieldArea.Bottom =  (csbiInfo->srWindow.Bottom / 2) + 10 ;

    npfiInfo->notrisScore = 0 ;

    npfiInfo->nextPiece = generate_random_number( 1, 7 ) ;   
}
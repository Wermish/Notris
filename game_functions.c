#include <stdio.h>
#include <Windows.h>
#include "game_functions.h"
#include "game_entities.h"

struct notrisPiece* generate_notris_piece( int notrisPieceShape, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo ){

    notrisPiece *piece = malloc( sizeof( notrisPiece ) ) ;
    
    piece->pieceShape = notrisPieceShape ;
    piece->pieceLook.Char.AsciiChar = 219 ;
    piece->blockOne.X = csbiInfo->dwSize.X / 2 ;
    piece->blockOne.Y = csbiInfo->dwSize.Y / 10 ;

    // Shape of piece is formed relative to coord of leading block, blockOne.
    switch( notrisPieceShape )
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

                    if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_DOWN )
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

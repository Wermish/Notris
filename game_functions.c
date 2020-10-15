#include <stdio.h>
#include <Windows.h>
#include "game_functions.h"
#include "game_entities.h"

struct notrisPiece* generate_notris_piece( int pt ){

    notrisPiece *piece = malloc( sizeof( notrisPiece ) ) ;
    
    piece->pieceType = pt ;
    piece->pieceLook.Char.AsciiChar = 219 ;
    piece->leadPart.X = 50 ;
    piece->leadPart.Y = 5 ;

    // Shape of piece is worked out based on coord of leading block, leadPart.
    switch( pt )
    {   // Square
        case 1:
            piece->partTwo.X = piece->leadPart.X + 1 ; 
            piece->partTwo.Y = piece->leadPart.Y ;
            piece->partThree.X = piece->leadPart.X ;
            piece->partThree.Y = piece->leadPart.Y + 1 ;
            piece->partFour.X = piece->leadPart.X + 1 ;
            piece->partFour.Y = piece->leadPart.Y + 1 ;
            piece->pieceLook.Attributes = FOREGROUND_RED ;
            
            break ;
        // Line
        case 2:
            piece->partTwo.X = piece->leadPart.X ;
            piece->partTwo.Y = piece->leadPart.Y + 1 ;
            piece->partThree.X = piece->leadPart.X ;
            piece->partThree.Y = piece->leadPart.Y + 2 ;
            piece->partFour.X = piece->leadPart.X ;
            piece->partFour.Y = piece->leadPart.Y + 3 ;
            piece->pieceLook.Attributes = FOREGROUND_GREEN ;
            break ;
        // 'L'
        case 3:
            piece->partTwo.X = piece->leadPart.X ;
            piece->partTwo.Y = piece->leadPart.Y + 1 ;
            piece->partThree.X = piece->leadPart.X ;
            piece->partThree.Y = piece->leadPart.Y + 2 ;
            piece->partFour.X = piece->leadPart.X + 1 ;
            piece->partFour.Y = piece->leadPart.Y + 2 ;
            piece->pieceLook.Attributes = FOREGROUND_GREEN | FOREGROUND_RED ;
            break ;
        // Mirrored 'L'
        case 4:
            piece->partTwo.X = piece->leadPart.X ;
            piece->partTwo.Y = piece->leadPart.Y + 1 ;
            piece->partThree.X = piece->leadPart.X ;
            piece->partThree.Y = piece->leadPart.Y + 2 ;
            piece->partFour.X = piece->leadPart.X - 1 ;
            piece->partFour.Y = piece->leadPart.Y + 2 ;
            piece->pieceLook.Attributes = FOREGROUND_GREEN | FOREGROUND_RED ;
            break ;
        // 'Z'
        case 5:
            piece->partTwo.X = piece->leadPart.X + 1 ;
            piece->partTwo.Y = piece->leadPart.Y ;
            piece->partThree.X = piece->leadPart.X + 1 ;
            piece->partThree.Y = piece->leadPart.Y + 1 ;
            piece->partFour.X = piece->leadPart.X + 2 ;
            piece->partFour.Y = piece->leadPart.Y + 1 ;
            piece->pieceLook.Attributes = FOREGROUND_GREEN | FOREGROUND_BLUE ;
            break ;
        // Mirrored 'Z'
        case 6:
            piece->partTwo.X = piece->leadPart.X - 1 ;
            piece->partTwo.Y = piece->leadPart.Y ;
            piece->partThree.X = piece->leadPart.X - 1 ;
            piece->partThree.Y = piece->leadPart.Y + 1 ;
            piece->partFour.X = piece->leadPart.X - 2 ;
            piece->partFour.Y = piece->leadPart.Y + 1 ;
            piece->pieceLook.Attributes = FOREGROUND_GREEN | FOREGROUND_BLUE ;
            break ;
        // 'Hat'    
        case 7:
            piece->partTwo.X = piece->leadPart.X ;
            piece->partTwo.Y = piece->leadPart.Y + 1 ;
            piece->partThree.X = piece->leadPart.X - 1 ;
            piece->partThree.Y = piece->leadPart.Y + 1 ;
            piece->partFour.X = piece->leadPart.X + 1 ;
            piece->partFour.Y = piece->leadPart.Y + 1 ;
            piece->pieceLook.Attributes = FOREGROUND_BLUE ;
            break ;  
    }
    return piece ;
}

/*
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
                    
                    if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_DOWN )
                    {
                        if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                        {
                            playerLocation->Y++ ;
                        }
                    }
                    else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_LEFT )
                    {
                        if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                        {
                            playerLocation->X-- ;
                        }
                    }
                    else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_RIGHT )
                    {
                        if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                        {
                            playerLocation->X++ ;
                        }
                    }
                }
            }
            free( inputRecordArray ) ;
        }
    }
}
*/
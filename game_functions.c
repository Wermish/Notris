#include <stdio.h>
#include <Windows.h>
#include "game_functions.h"
#include "game_entities.h"

struct notrisPiece* generate_notris_piece( int pt ){

    notrisPiece *piece = malloc( sizeof( notrisPiece ) ) ;
    piece->pieceType = pt ;
    piece->pieceLook.Char.AsciiChar = 219 ;
    piece->partOne.X = 50 ;
    piece->partOne.Y = 5 ;

    switch( pt )
    {   // Square
        case 1:
            piece->partTwo.X = 51 ; 
            piece->partTwo.Y = 5 ;
            piece->partThree.X = 50 ;
            piece->partThree.Y = 6 ;
            piece->partFour.X = 51 ;
            piece->partFour.Y = 6 ;
            piece->pieceLook.Attributes = FOREGROUND_RED ;
            
            break ;
        // Line
        case 2:
            piece->partTwo.X = 50 ;
            piece->partTwo.Y = 6 ;
            piece->partThree.X = 50 ;
            piece->partThree.Y = 7 ;
            piece->partFour.X = 50 ;
            piece->partFour.Y = 8 ;
            piece->pieceLook.Attributes = FOREGROUND_GREEN ;
            break ;
        // 'L'
        case 3:
            piece->partTwo.X = 50 ;
            piece->partTwo.Y = 6 ;
            piece->partThree.X = 50 ;
            piece->partThree.Y = 7 ;
            piece->partFour.X = 51 ;
            piece->partFour.Y = 7 ;
            piece->pieceLook.Attributes = FOREGROUND_GREEN | FOREGROUND_RED ;
            break ;
        // Mirrored 'L'
        case 4:
            piece->partTwo.X = 50 ;
            piece->partTwo.Y = 6 ;
            piece->partThree.X = 50 ;
            piece->partThree.Y = 7 ;
            piece->partFour.X = 49 ;
            piece->partFour.Y = 7 ;
            piece->pieceLook.Attributes = FOREGROUND_GREEN | FOREGROUND_RED ;
            break ;
        // 'Z'
        case 5:
            piece->partTwo.X = 51 ;
            piece->partTwo.Y = 5 ;
            piece->partThree.X = 51 ;
            piece->partThree.Y = 6 ;
            piece->partFour.X = 52 ;
            piece->partFour.Y = 6 ;
            piece->pieceLook.Attributes = FOREGROUND_GREEN | FOREGROUND_BLUE ;
            break ;
        // Mirrored 'Z'
        case 6:
            piece->partTwo.X = 49 ;
            piece->partTwo.Y = 5 ;
            piece->partThree.X = 49 ;
            piece->partThree.Y = 6 ;
            piece->partFour.X = 48 ;
            piece->partFour.Y = 6 ;
            piece->pieceLook.Attributes = FOREGROUND_GREEN | FOREGROUND_BLUE ;
            break ;
        // 'Hat'    
        case 7:
            piece->partTwo.X = 50 ;
            piece->partTwo.Y = 6 ;
            piece->partThree.X = 49 ;
            piece->partThree.Y = 6 ;
            piece->partFour.X = 51 ;
            piece->partFour.Y = 6 ;
            piece->pieceLook.Attributes = FOREGROUND_BLUE ;
            break ;  
    }
    return piece ;
}

void move_player( HANDLE* phInputBuffer, COORD* playerLocation )
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
                        if( !inputRecordArray[i].Event.KeyEvent.bKeyDown )
                        {   
                            exit( EXIT_SUCCESS ) ;
                        }
                    }
                    else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_UP )
                    {
                        if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                        {
                            playerLocation->Y-- ;
                        }
                        
                    }
                    else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_DOWN )
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
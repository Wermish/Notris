#include <stdio.h>
#include <Windows.h>
#include "game_functions.h"

void move_player( HANDLE* phInput, COORD* playerLocation )
{
    DWORD numberOfEvents = 0 ;
    DWORD numberOfEventsRead = 0 ;

    GetNumberOfConsoleInputEvents( *phInput, &numberOfEvents ) ;

        if( numberOfEvents )
        {
            INPUT_RECORD* inputRecordArray = malloc( sizeof( INPUT_RECORD ) * numberOfEvents ) ;

            ReadConsoleInput( *phInput, inputRecordArray, numberOfEvents, &numberOfEventsRead ) ;

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
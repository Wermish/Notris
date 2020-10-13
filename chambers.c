#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "console_functions.h"
#include "graphics_functions.h"

HANDLE hMainBuffer ;
HANDLE hBackBuffer ;
HANDLE hStdInput ;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo ;
CONSOLE_CURSOR_INFO cciInfo ;
CONSOLE_FONT_INFOEX cfiInfo ;

int main( void )
{   

    initial_setup( &hMainBuffer, &hBackBuffer, &hStdInput, &csbiInfo, &cciInfo, &cfiInfo, 100, 40 ) ;

    draw_rectangle( &hMainBuffer, &csbiInfo, 219, FOREGROUND_RED | FOREGROUND_GREEN, 0, 0, 100, 1 ) ;
    draw_rectangle( &hMainBuffer, &csbiInfo, 219, FOREGROUND_RED | FOREGROUND_GREEN, 0, 39, 100, 40 ) ;
    draw_rectangle( &hMainBuffer, &csbiInfo, 219, FOREGROUND_RED | FOREGROUND_GREEN, 0, 0, 2, 40 ) ;
    draw_rectangle( &hMainBuffer, &csbiInfo, 219, FOREGROUND_RED | FOREGROUND_GREEN, 98, 0, 100, 40 ) ; 

    DWORD numberOfEvents = 0 ;
    DWORD numberOfEventsRead = 0 ;
    COORD playerLocation = { 50, 20 } ;
    CHAR playerIcon = '@' ;
    DWORD written = 0 ;

    while(1)
    {
        GetNumberOfConsoleInputEvents( hStdInput, &numberOfEvents ) ;

        if( numberOfEvents )
        {

            INPUT_RECORD* inputRecordArray = malloc( sizeof( INPUT_RECORD ) * numberOfEvents ) ;

            ReadConsoleInput( hStdInput, inputRecordArray, numberOfEvents, &numberOfEventsRead ) ;

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
                            playerLocation.Y-- ;
                        }
                        
                    }
                    else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_DOWN )
                    {
                        if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                        {
                            playerLocation.Y++ ;
                        }
                    }
                    else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_LEFT )
                    {
                        if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                        {
                            playerLocation.X-- ;
                        }
                    }
                    else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_RIGHT )
                    {
                        if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                        {
                            playerLocation.X++ ;
                        }
                    }
                }
            }
            free( inputRecordArray ) ;
        }
        WriteConsoleOutputCharacter( hMainBuffer, &playerIcon, 1, playerLocation, &written ) ;
        // ~around 50FPS and prevents game dominating CPU.
        Sleep( 20 ) ;
    }

    CloseHandle( hMainBuffer ) ;
    CloseHandle( hBackBuffer ) ;
    CloseHandle( hStdInput ) ;

    return EXIT_SUCCESS ;

}
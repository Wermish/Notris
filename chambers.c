#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "console_functions.h"
#include "graphics_functions.h"

HANDLE hMainBuffer ;
HANDLE hBackBuffer ;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo ;
CONSOLE_CURSOR_INFO cciInfo ;
CONSOLE_FONT_INFOEX cfiInfo ;

int main( void )
{   /*

    initial_setup( &hMainBuffer, &hBackBuffer, &csbiInfo, &cciInfo, &cfiInfo, 100, 40 ) ;

    draw_rectangle( &hMainBuffer, &csbiInfo, 219, FOREGROUND_RED | FOREGROUND_GREEN, 0, 0, 100, 1 ) ;
    draw_rectangle( &hMainBuffer, &csbiInfo, 219, FOREGROUND_RED | FOREGROUND_GREEN, 0, 39, 100, 40 ) ;
    draw_rectangle( &hMainBuffer, &csbiInfo, 219, FOREGROUND_RED | FOREGROUND_GREEN, 0, 0, 2, 40 ) ;
    draw_rectangle( &hMainBuffer, &csbiInfo, 219, FOREGROUND_RED | FOREGROUND_GREEN, 98, 0, 100, 40 ) ; 

    CloseHandle( hMainBuffer ) ;
    CloseHandle( hBackBuffer ) ;

     */

    HANDLE hStdOutput = GetStdHandle( STD_OUTPUT_HANDLE ) ;
    HANDLE hstdInput = GetStdHandle( STD_INPUT_HANDLE ) ;

    DWORD numberOfEvents = 0 ;
    DWORD numberOfEventsRead = 0 ;

    system( "cls" ) ; 

    while(1)
    {
        GetNumberOfConsoleInputEvents( hstdInput, &numberOfEvents ) ;

        if( numberOfEvents )
        {

            INPUT_RECORD* inputRecordArray = malloc( sizeof( INPUT_RECORD ) * numberOfEvents ) ;

            ReadConsoleInput( hstdInput, inputRecordArray, numberOfEvents, &numberOfEventsRead ) ;

            for( int i = 0; i < numberOfEventsRead; i++ )
            {
                if( inputRecordArray[i].EventType == KEY_EVENT )
                {
                    if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE )
                    {
                        if( !inputRecordArray[i].Event.KeyEvent.bKeyDown )
                        {   
                            system( "cls" ) ;
                            exit( EXIT_SUCCESS ) ;
                        }
                    }
                    else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_UP )
                    {
                        if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                        {
                            fprintf( stdout, "UP\n" ) ;
                        }
                        
                    }
                    else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_DOWN )
                    {
                        if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                        {
                            fprintf( stdout, "DOWN\n" ) ;
                        }
                    }
                    else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_LEFT )
                    {
                        if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                        {
                            fprintf( stdout, "LEFT\n" ) ;
                        }
                    }
                    else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_RIGHT )
                    {
                        if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                        {
                            fprintf( stdout, "RIGHT\n" ) ;
                        }
                    }
                }
            }
            free( inputRecordArray ) ;
        }

    }

    system( "cls" ) ;

    return EXIT_SUCCESS ;

}
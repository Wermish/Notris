#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "console_functions.h"
#include "graphics_functions.h"
#include "game_functions.h"

HANDLE hScreenBufferOne ;
HANDLE hScreenBufferTwo ;
HANDLE hInputBuffer ;

HANDLE* phCurrent ;
HANDLE* phDouble ;

CONSOLE_SCREEN_BUFFER_INFO csbiInfo ;
CONSOLE_CURSOR_INFO cciInfo ;
CONSOLE_FONT_INFOEX cfiInfo ;

int main( void )
{   

    initial_setup( &hScreenBufferOne, &hScreenBufferTwo, &hInputBuffer, &csbiInfo, &cciInfo, &cfiInfo, 100, 40 ) ;

    phCurrent = &hScreenBufferOne ;
    phDouble = &hScreenBufferTwo ;

    DWORD numberOfEvents = 0 ;
    DWORD numberOfEventsRead = 0 ;
    COORD playerLocation = { 50, 20 } ;
    CHAR playerIcon = '@' ;
    CHAR space = ' ' ;
    DWORD written = 0 ;

    while(1)
    {   
        SetConsoleActiveScreenBuffer( *phCurrent ) ;

        draw_rectangle( phDouble, &csbiInfo, 219, FOREGROUND_RED | FOREGROUND_GREEN, 0, 0, 100, 1 ) ;
        draw_rectangle( phDouble, &csbiInfo, 219, FOREGROUND_RED | FOREGROUND_GREEN, 0, 39, 100, 40 ) ;
        draw_rectangle( phDouble, &csbiInfo, 219, FOREGROUND_RED | FOREGROUND_GREEN, 0, 0, 2, 40 ) ;
        draw_rectangle( phDouble, &csbiInfo, 219, FOREGROUND_RED | FOREGROUND_GREEN, 98, 0, 100, 40 ) ; 

        WriteConsoleOutputCharacter( *phDouble, &space, 1, playerLocation, &written ) ;
        WriteConsoleOutputCharacter( *phCurrent, &space, 1, playerLocation, &written ) ;

        move_player( &hInputBuffer, &playerLocation ) ;

        WriteConsoleOutputCharacter( *phDouble, &playerIcon, 1, playerLocation, &written ) ;
        SetConsoleActiveScreenBuffer( *phDouble ) ;

        if( *phDouble == hScreenBufferTwo )
        {
            phDouble = &hScreenBufferOne ;
            phCurrent = &hScreenBufferTwo ;
        }
        else
        {
            phDouble = &hScreenBufferTwo ;
            phCurrent = &hScreenBufferOne ;
        }
        // ~around 50FPS and prevents game dominating CPU.
        Sleep( 20 ) ;
    }

    CloseHandle( hScreenBufferOne ) ;
    CloseHandle( hScreenBufferTwo ) ;
    CloseHandle( hInputBuffer ) ;

    return EXIT_SUCCESS ;

}
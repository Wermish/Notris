#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "console_functions.h"

HANDLE hMainBuffer ;
HANDLE hBackBuffer ;

int main( void )
{   
    initial_setup( &hMainBuffer, &hBackBuffer ) ;

    COORD start_write = { 0, 0 } ;
    DWORD chars_written = 0 ;
    CONSOLE_SCREEN_BUFFER_INFO csbi ;
    SetConsoleActiveScreenBuffer( hMainBuffer ) ;
    FillConsoleOutputCharacter( hMainBuffer, ' ', 4000, start_write, &chars_written ) ;
    FillConsoleOutputCharacter( hBackBuffer, '.', 4000, start_write, &chars_written ) ;
    SetConsoleActiveScreenBuffer( hBackBuffer ) ;
    Sleep(1000) ;
    SetConsoleActiveScreenBuffer( hMainBuffer ) ;
    Sleep(1000) ;
    SetConsoleActiveScreenBuffer( hBackBuffer ) ;
    Sleep(1000) ;
    SetConsoleActiveScreenBuffer( hMainBuffer ) ;
    Sleep( 1000 ) ;
    SetConsoleActiveScreenBuffer( hBackBuffer ) ;
    Sleep( 1000 ) ;
    CloseHandle( hMainBuffer ) ;
    CloseHandle( hBackBuffer ) ;

    return EXIT_SUCCESS ;

}
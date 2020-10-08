#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "console_functions.h"
#include "graphics_functions.h"

HANDLE hMainBuffer ;
HANDLE hBackBuffer ;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo ;

int main( void )
{   
    initial_setup( &hMainBuffer, &hBackBuffer, &csbiInfo, 100, 40 ) ;

    draw_rectangle( &hMainBuffer, &csbiInfo ) ;

    getchar() ;

    CloseHandle( hMainBuffer ) ;
    CloseHandle( hBackBuffer ) ;
    
    return EXIT_SUCCESS ;

}
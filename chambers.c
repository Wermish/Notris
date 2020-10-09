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
{   
    initial_setup( &hMainBuffer, &hBackBuffer, &csbiInfo, &cciInfo, &cfiInfo, 100, 40 ) ;

    draw_rectangle( &hMainBuffer, &csbiInfo, 0, 0, 100, 30 ) ;
    draw_rectangle( &hMainBuffer, &csbiInfo, 5, 31, 15, 39 ) ;
    draw_rectangle( &hMainBuffer, &csbiInfo, 16, 31, 26, 39 ) ;
    draw_rectangle( &hMainBuffer, &csbiInfo, 27, 31, 37, 39 ) ;
    

    getchar() ;

    CloseHandle( hMainBuffer ) ;
    CloseHandle( hBackBuffer ) ;
    
    return EXIT_SUCCESS ;

}
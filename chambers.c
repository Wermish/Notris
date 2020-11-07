#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "shared/console_functions.h"
#include "shared/shared_graphics_functions.h"
#include "shared/shared_game_functions.h"
#include "notris/notris_graphics_functions.h"
#include "notris/notris_game_functions.h"
#include "notris/notris_structures.h"

HANDLE hScreenBufferOne ;
HANDLE hScreenBufferTwo ;
HANDLE hInputBuffer ;
    
HANDLE* phVisible;
HANDLE* phNotVisible ;

CONSOLE_SCREEN_BUFFER_INFO csbiInfo ;
CONSOLE_CURSOR_INFO cciInfo ;
CONSOLE_FONT_INFOEX cfiInfo ;

notrisInfo npfiInfo ;

int main( void )
{
    setup_console( &hScreenBufferOne, &hScreenBufferTwo, &hInputBuffer, &csbiInfo, &cciInfo, &cfiInfo, 50, 30 ) ;

    play_notris( &hScreenBufferOne, &hScreenBufferTwo, &hInputBuffer, &csbiInfo, &npfiInfo ) ;

    CloseHandle( hScreenBufferOne ) ;
    CloseHandle( hScreenBufferTwo ) ;
    CloseHandle( hInputBuffer ) ;

    return EXIT_SUCCESS ;

}
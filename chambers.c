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

HANDLE hScreenBuffer ;
HANDLE hInputBuffer ;
    
CONSOLE_SCREEN_BUFFER_INFO csbiInfo ;
CONSOLE_CURSOR_INFO cciInfo ;
CONSOLE_FONT_INFOEX cfiInfo ;

notrisInfo npfiInfo ;

int main( void )
{
    setup_console( &hScreenBuffer, &hInputBuffer, &csbiInfo, &cciInfo, &cfiInfo, 51, 41 ) ;

    play_notris( &hScreenBuffer, &hInputBuffer, &csbiInfo, &npfiInfo ) ;

    CloseHandle( hScreenBuffer ) ;
    CloseHandle( hInputBuffer ) ;

    return EXIT_SUCCESS ;

}
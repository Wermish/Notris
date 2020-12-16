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

notrisInfo niInfo ;

BOOL playingNotris = 0 ;
BOOL browsingMenu = 1 ;

int main( void )
{   
    srand( ( unsigned )time( 0 ) ) ;

    setup_console( &hScreenBuffer, &hInputBuffer, &csbiInfo, &cciInfo, &cfiInfo, 40, 40 ) ;

    while( browsingMenu )
    {
        display_buffer( &hScreenBuffer, &csbiInfo, niInfo.ciNotrisMainMenu ) ;

        if( notris_menu_selection( &hInputBuffer, &niInfo ) )
        {
            playingNotris = 1 ;
        }

        while( playingNotris )
        {
            notris_setup( &csbiInfo, &niInfo ) ;

            if( play_notris( &hScreenBuffer, &hInputBuffer, &csbiInfo, &niInfo ) )
            {
                playingNotris = 0 ;
            }

            notris_cleanup( &csbiInfo, &niInfo ) ;
        }
    }

    CloseHandle( hScreenBuffer ) ;
    CloseHandle( hInputBuffer ) ;

    return EXIT_SUCCESS ;
}
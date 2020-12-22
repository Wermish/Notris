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

notrisMenu nmMenu ;
notrisInfo niInfo ;

BOOL browsingMenu ;

SHORT menuChoice ;

SHORT levelChoice ;

int main( void )
{   
    srand( ( unsigned )time( 0 ) ) ;

    setup_console( &hScreenBuffer, &hInputBuffer, &csbiInfo, &cciInfo, &cfiInfo, 41, 41 ) ;

    notris_setup_menu( &csbiInfo, &nmMenu ) ;

    notris_draw_menu( &csbiInfo, &nmMenu ) ;

    browsingMenu = 1 ;

    while( browsingMenu )
    {
        display_buffer( &hScreenBuffer, &csbiInfo, nmMenu.ciNotrisMainMenu ) ;

        menuChoice = notris_menu_selection( &hInputBuffer, &csbiInfo, &niInfo, &nmMenu, 0 ) ;

        if( menuChoice == 1 )
        {
            notris_setup_game( &csbiInfo, &niInfo ) ;

            while( !levelChoice )
            {

                display_buffer( &hScreenBuffer, &csbiInfo, nmMenu.ciNotrisMainMenu ) ;

                levelChoice = notris_menu_selection( &hInputBuffer, &csbiInfo, &niInfo, &nmMenu, 1 ) ;
            }

            if( levelChoice )
            {
                niInfo.level = levelChoice ;

                play_notris( &hScreenBuffer, &hInputBuffer, &csbiInfo, &niInfo ) ;
            }

            notris_cleanup_game( &csbiInfo, &niInfo ) ;
        }
        else if( menuChoice == 2 )
        {
            // Display scoreboard.
        }
        else if( menuChoice == 3 )
        {
            browsingMenu = 0 ;
        }

        Sleep( 50 ) ;
    }

    notris_cleanup_menu( &csbiInfo, &nmMenu ) ;

    CloseHandle( hScreenBuffer ) ;
    CloseHandle( hInputBuffer ) ;

    return EXIT_SUCCESS ;
}
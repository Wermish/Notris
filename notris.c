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

FILE *fTopScores ;

notrisMenu nmMenu ;
notrisInfo niInfo ;
notrisScore nsScore ;

BOOL browsingMenu ;

BOOL selectingLevel ;

SHORT menuChoice ;

SHORT levelChoice ;

int main( void )
{   
    notris_setup_scores_file( &fTopScores, &nsScore );

    for( int i = 0; i < 10; i++ )
    {
        fread( &nsScore, sizeof( struct notrisScore ), 1, fTopScores ) ;
        fprintf( stdout, "%c%c%c, %i\n", nsScore.chPlayerTag[0], nsScore.chPlayerTag[1], nsScore.chPlayerTag[2], nsScore.dwScore ) ;
    }

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

            selectingLevel = 1 ;

            while( selectingLevel )
            {
                levelChoice = notris_menu_selection( &hInputBuffer, &csbiInfo, &niInfo, &nmMenu, 1 ) ;
            
                if( levelChoice != 0 )
                {
                    selectingLevel = 0 ;
                }

                notris_draw_level_options( &csbiInfo, &niInfo, &nmMenu ) ;

                display_buffer( &hScreenBuffer, &csbiInfo, nmMenu.ciNotrisMainMenu ) ;

                Sleep(50) ;
            }

            notris_draw_menu_options( &csbiInfo, &nmMenu ) ;

            if( levelChoice > 0 )
            {
                if( !play_notris( &hScreenBuffer, &hInputBuffer, &csbiInfo, &niInfo ) )
                {
                    // Write score to file.
                    nsScore.chPlayerTag[0] = 67 ;
                    nsScore.chPlayerTag[1] = 72 ;
                    nsScore.chPlayerTag[2] = 65 ;

                    nsScore.dwScore = niInfo.notrisScore ;

                    notris_update_scores_file( &fTopScores, &nsScore ) ;
                }
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
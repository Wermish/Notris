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

notrisPlayFieldInfo npfiInfo ;

int main( void )
{
    setup_console( &hScreenBufferOne, &hScreenBufferTwo, &hInputBuffer, &csbiInfo, &cciInfo, &cfiInfo, 101, 40 ) ;

    phVisible= &hScreenBufferOne ;
    phNotVisible = &hScreenBufferTwo ;

    notrisPiece *p = generate_notris_piece( generate_random_number( 1, 7 ), &csbiInfo ) ;

    WORD pieceDropRate = 0 ;

    srand( time( 0 ) ) ;

    setup_notris( &csbiInfo, &npfiInfo ) ;

    while( 1 )
    {   
        clear_screen_buffer( phNotVisible, &csbiInfo ) ;

        //draw_notris_play_field( phNotVisible, &npfiInfo ) ;

        draw_rectangle( phNotVisible, 0, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY,
                  npfiInfo.playFieldArea.Left, npfiInfo.playFieldArea.Top,
                  npfiInfo.playFieldArea.Right, npfiInfo.playFieldArea.Top + 1  ) ;
        draw_rectangle( phNotVisible, 0, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY,
                  npfiInfo.playFieldArea.Left, npfiInfo.playFieldArea.Bottom,
                  npfiInfo.playFieldArea.Right, npfiInfo.playFieldArea.Bottom + 1 ) ;

        draw_rectangle( phNotVisible, 0, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY,
                  npfiInfo.playFieldArea.Left, npfiInfo.playFieldArea.Top,
                  npfiInfo.playFieldArea.Left + 1, npfiInfo.playFieldArea.Bottom  ) ;

        draw_rectangle( phNotVisible, 0, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY,
                  npfiInfo.playFieldArea.Right, npfiInfo.playFieldArea.Top,
                  npfiInfo.playFieldArea.Right + 1, npfiInfo.playFieldArea.Bottom  ) ;

        move_notris_piece( &hInputBuffer, p ) ;

        draw_notris_piece( phNotVisible, &csbiInfo, p ) ;

        SetConsoleActiveScreenBuffer( *phNotVisible ) ;

        if( *phNotVisible == hScreenBufferTwo )
        {
            phNotVisible = &hScreenBufferOne ;
            phVisible= &hScreenBufferTwo ;
        }
        else
        {
            phNotVisible = &hScreenBufferTwo ;
            phVisible= &hScreenBufferOne ;
        }

        pieceDropRate++ ;

        if( pieceDropRate == 10 )
        {
            pieceDropRate = 0 ;

            p->blockOne.Y++ ;
            p->blockTwo.Y++ ;
            p->blockThree.Y++ ;
            p->blockFour.Y++ ;
        }

        Sleep( 50 ) ;
    }

    CloseHandle( hScreenBufferOne ) ;
    CloseHandle( hScreenBufferTwo ) ;
    CloseHandle( hInputBuffer ) ;

    return EXIT_SUCCESS ;

}
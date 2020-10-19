#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "console_functions.h"
#include "graphics_functions.h"
#include "game_functions.h"
#include "game_entities.h"

HANDLE hScreenBufferOne ;
HANDLE hScreenBufferTwo ;
HANDLE hInputBuffer ;
    
HANDLE* phVisible;
HANDLE* phNotVisible ;

CONSOLE_SCREEN_BUFFER_INFO csbiInfo ;
CONSOLE_CURSOR_INFO cciInfo ;
CONSOLE_FONT_INFOEX cfiInfo ;

int main( void )
{ 
    initial_setup( &hScreenBufferOne, &hScreenBufferTwo, &hInputBuffer, &csbiInfo, &cciInfo, &cfiInfo, 100, 40 ) ;

    phVisible= &hScreenBufferOne ;
    phNotVisible = &hScreenBufferTwo ;

    notrisPiece *p = generate_notris_piece( generate_random_number( 1, 7 ), &csbiInfo ) ;

    int pieceDropRate = 0 ;

    while( 1 )
    {   
        clear_screen_buffer( phVisible, &csbiInfo ) ;

        move_notris_piece( &hInputBuffer, p ) ;

        pieceDropRate++ ;

        if( pieceDropRate == 10 )
        {
            pieceDropRate = 0 ;

            p->blockOne.Y++ ;
            p->blockTwo.Y++ ;
            p->blockThree.Y++ ;
            p->blockFour.Y++ ;
        }

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

        Sleep( 50 ) ;
    }

    CloseHandle( hScreenBufferOne ) ;
    CloseHandle( hScreenBufferTwo ) ;
    CloseHandle( hInputBuffer ) ;

    return EXIT_SUCCESS ;

}
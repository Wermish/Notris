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
    
HANDLE* phCurrent ;
HANDLE* phDouble ;

CONSOLE_SCREEN_BUFFER_INFO csbiInfo ;
CONSOLE_CURSOR_INFO cciInfo ;
CONSOLE_FONT_INFOEX cfiInfo ;

int main( void )
{ 
    initial_setup( &hScreenBufferOne, &hScreenBufferTwo, &hInputBuffer, &csbiInfo, &cciInfo, &cfiInfo, 100, 40 ) ;

    phCurrent = &hScreenBufferOne ;
    phDouble = &hScreenBufferTwo ;

    notrisPiece *p = generate_notris_piece( generate_random_number( 1, 7 ), &csbiInfo ) ;

    while( 1 )
    {   
        SetConsoleActiveScreenBuffer( *phCurrent ) ;

        erase_notris_piece( phDouble, &csbiInfo, p ) ;

        erase_notris_piece( phCurrent, &csbiInfo, p ) ;

        move_notris_piece( &hInputBuffer, p ) ;

        draw_notris_piece( phDouble, &csbiInfo, p ) ;

        SetConsoleActiveScreenBuffer( *phDouble ) ;

        if( *phDouble == hScreenBufferTwo )
        {
            phDouble = &hScreenBufferOne ;
            phCurrent = &hScreenBufferTwo ;
        }
        else
        {
            phDouble = &hScreenBufferTwo ;
            phCurrent = &hScreenBufferOne ;
        }

        Sleep( 50 ) ;
    }

    CloseHandle( hScreenBufferOne ) ;
    CloseHandle( hScreenBufferTwo ) ;
    CloseHandle( hInputBuffer ) ;

    return EXIT_SUCCESS ;

}
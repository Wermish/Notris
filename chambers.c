#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "console_functions.h"
#include "graphics_functions.h"
#include "game_functions.h"
#include "game_entities.h"

int main( void )
{ 
    HANDLE hScreenBufferOne ;
    HANDLE hScreenBufferTwo ;
    HANDLE hInputBuffer ;
    
    HANDLE* phCurrent ;
    HANDLE* phDouble ;

    CONSOLE_SCREEN_BUFFER_INFO csbiInfo ;
    CONSOLE_CURSOR_INFO cciInfo ;
    CONSOLE_FONT_INFOEX cfiInfo ;

    initial_setup( &hScreenBufferOne, &hScreenBufferTwo, &hInputBuffer, &csbiInfo, &cciInfo, &cfiInfo, 100, 40 ) ;

    phCurrent = &hScreenBufferOne ;
    phDouble = &hScreenBufferTwo ;

    notrisPiece *p = generate_notris_piece( 1, &csbiInfo ) ;

    draw_notris_piece( &hScreenBufferOne, &csbiInfo, p ) ;

    getchar() ;

    CloseHandle( hScreenBufferOne ) ;
    CloseHandle( hScreenBufferTwo ) ;
    CloseHandle( hInputBuffer ) ;

    return EXIT_SUCCESS ;

}
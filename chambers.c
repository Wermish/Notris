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
    setup_console( &hScreenBufferOne, &hScreenBufferTwo, &hInputBuffer, &csbiInfo, &cciInfo, &cfiInfo, 50, 30 ) ;

    //play_notris( &hScreenBufferOne, &hScreenBufferTwo, &hInputBuffer, &csbiInfo, &npfiInfo ) ;

    SHORT bufferWidth = csbiInfo.dwSize.X ;
    SHORT bufferHeight = csbiInfo.dwSize.Y ;

    SHORT width = csbiInfo.srWindow.Right ;
    SHORT height = csbiInfo.srWindow.Bottom ;

    COORD bufferSize = { bufferWidth, 1 } ;
    COORD startPoint = { 0, 0 } ;

    SMALL_RECT srWriteRegion = { .Left = csbiInfo.srWindow.Left, .Top = csbiInfo.srWindow.Top,
                                 .Right = csbiInfo.srWindow.Right, .Bottom = csbiInfo.srWindow.Top + 1 } ;

    DWORD dwWritten = 0 ;

    CHAR_INFO* ciPointer ;

    CHAR_INFO** ciBuffer = ( CHAR_INFO** ) malloc( bufferHeight  * sizeof( CHAR_INFO* ) ) ;

    for( int i = 0; i < bufferHeight; i++ )
    {
        ciBuffer[i] = ( CHAR_INFO* ) malloc( bufferWidth * sizeof( CHAR_INFO ) ) ;
    }

    for( int y = 0; y < bufferHeight; y++ )
    {
        for( int x = 0; x < bufferWidth; x++ )
        {
            ciBuffer[y][x].Char.AsciiChar = 49 ;
            ciBuffer[y][x].Attributes = BACKGROUND_GREEN | BACKGROUND_INTENSITY ;
        }
    }

    SetConsoleActiveScreenBuffer( hScreenBufferOne ) ;
    SetConsoleCursorPosition( hScreenBufferOne, startPoint ) ;

    ciBuffer[height][width].Char.AsciiChar = 1 ;
    ciBuffer[height][width].Attributes = BACKGROUND_RED ;

    for( int j = 0; j < bufferHeight; j++ )
    {
        ciPointer = ciBuffer[j] ;

        if( !WriteConsoleOutputA( hScreenBufferOne, ciPointer, bufferSize, startPoint, &srWriteRegion ) )
        {
            report_error( "WriteConsoleOutputA( hScreenBufferOne, ciBuffer, bufferSize, startPoint, &csbiInfo.srWindow )" ) ;
        }

        srWriteRegion.Top++ ;
        srWriteRegion.Bottom++ ;
    }

    getchar() ;

    CloseHandle( hScreenBufferOne ) ;
    CloseHandle( hScreenBufferTwo ) ;
    CloseHandle( hInputBuffer ) ;

    return EXIT_SUCCESS ;

}
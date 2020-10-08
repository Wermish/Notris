#include <stdio.h>
#include <Windows.h>
#include "console_functions.h"
#include "graphics_functions.h"

int draw_rectangle( HANDLE* hScreen )
{
    // TODO: parameters for drawing coords, colour, character etc...
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo ;

    if( !GetConsoleScreenBufferInfo( *hScreen, &csbiInfo ) )
    {
        report_error( "GetConsoleScreenBufferInfo( *hScreen, &csbiInfo )" ) ;
    }

    SHORT bufferWidth = csbiInfo.dwSize.X ;
    SHORT bufferHeight = csbiInfo.dwSize.Y ;

    COORD characterPosition = { 0, 0 } ;
    COORD characterBufferSize = { bufferWidth, bufferHeight } ;
    SMALL_RECT consoleWriteArea = { 0, 0, bufferWidth - 1, bufferHeight - 1 } ;

    // Note that it's a one-dimensional array.
    CHAR_INFO* consoleBuffer  = ( CHAR_INFO* ) malloc( ( bufferWidth * bufferWidth ) * sizeof( CHAR_INFO ) ) ;

    if( consoleBuffer == NULL )
    {
      report_error( "Failed: CHAR_INFO* consoleBuffer  = ( CHAR_INFO* ) malloc( ( bufferWidth * bufferWidth ) * sizeof( CHAR_INFO ) )" ) ;
    }

    // Accessed like a matrix by using offset. bufferWidth * y gives the first cell of each row, and column given by adding x to it.
    for (int y = 0; y < bufferHeight; ++y)
    {
      for (int x = 0; x < bufferWidth; ++x)
      {
        consoleBuffer[ x + bufferWidth * y ].Char.AsciiChar = ( unsigned char )rand() % 255;
        consoleBuffer[ x + bufferWidth * y ].Attributes = rand() % 256;
      }
    }

    if( !WriteConsoleOutputA( *hScreen, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea ) )
    {
      report_error( "WriteConsoleOutputA( *hScreen, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea )" ) ;
    }

    free( consoleBuffer ) ;

    return EXIT_SUCCESS ;
}
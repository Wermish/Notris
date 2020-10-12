#include <stdio.h>
#include <Windows.h>
#include "console_functions.h"
#include "graphics_functions.h"

// To draw a line, the breadth of the line must increase by 1. E.g, startX = 0, startY = 0, endX = 10, endY = 1.

int draw_rectangle( HANDLE* hScreen, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, 
                    CHAR asciiValue, WORD asciiAttributes, 
                    SHORT startX, SHORT startY, SHORT endX, SHORT endY )
{
    // TODO: parameters for drawing coords, colour, character etc...

    if( !GetConsoleScreenBufferInfo( *hScreen, csbiInfo ) )
    {
        report_error( "GetConsoleScreenBufferInfo( *hScreen, &csbiInfo )" ) ;
    }

    SHORT bufferWidth = endX ;
    SHORT bufferHeight = endY ;

    COORD characterPosition = { startX, startY } ;
    COORD characterBufferSize = { bufferWidth, bufferHeight } ;
    SMALL_RECT consoleWriteArea = { startX, startY, bufferWidth - 1, bufferHeight - 1 } ;

    // Note that it's a one-dimensional array.
    CHAR_INFO* consoleBuffer  = ( CHAR_INFO* ) malloc( ( bufferWidth * bufferHeight ) * sizeof( CHAR_INFO ) ) ;

    if( consoleBuffer == NULL )
    {
      report_error( "Failed: CHAR_INFO* consoleBuffer  = ( CHAR_INFO* ) malloc( ( bufferWidth * bufferWidth ) * sizeof( CHAR_INFO ) )" ) ;
    }

    // Accessed like a matrix by using offset. bufferWidth * y gives the first cell of each row, and column given by adding x to it.
    for (int y = 0; y < bufferHeight; ++y)
    {
      for (int x = 0; x < bufferWidth; ++x)
      {
        consoleBuffer[ x + bufferWidth * y ].Char.AsciiChar = asciiValue ;
        consoleBuffer[ x + bufferWidth * y ].Attributes = asciiAttributes ;
      }
    }

    if( !WriteConsoleOutputA( *hScreen, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea ) )
    {
      report_error( "WriteConsoleOutputA( *hScreen, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea )" ) ;
    }

    free( consoleBuffer ) ;

    return EXIT_SUCCESS ;
}
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "console_functions.h"
#include "shared_graphics_functions.h"
#include "../notris/notris_structures.h"

void clear_screen_buffer( HANDLE* phScreenBuffer, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo )
{
  // This seems to have fixed the flickering. Must have been leaving artifacts before. Now whole screen is drawn to.
  COORD coordStartClearing;
  coordStartClearing.X = 0;
  coordStartClearing.Y = 0;

  SetConsoleCursorPosition( *phScreenBuffer, coordStartClearing);

  draw_rectangle( phScreenBuffer, 0, 0, 
                  0, 0, csbiInfo->dwSize.X, csbiInfo->dwSize.Y ) ;
}

// endX and endY must be at least 1 unit greater than startX and endX respectively.
void draw_rectangle( HANDLE* phScreenBuffer, 
                     CHAR asciiValue, WORD asciiAttributes, 
                     SHORT startX, SHORT startY, SHORT endX, SHORT endY )
{
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

    if( !WriteConsoleOutputA( *phScreenBuffer, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea ) )
    {
      report_error( "WriteConsoleOutputA( *phScreenBuffer, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea )" ) ;
    }

    free( consoleBuffer ) ;
}
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "console_functions.h"
#include "shared_graphics_functions.h"
#include "../notris/notris_structures.h"

void clear_buffer( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, CHAR_INFO** buffer )
{
  SHORT bufferWidth = csbiInfo->dwSize.X ;
  SHORT bufferHeight = csbiInfo->dwSize.Y ;

  for( int y = 0; y < bufferHeight; y++ )
    {
        for( int x = 0; x < bufferWidth; x++ )
        {
            buffer[y][x].Char.AsciiChar = 0 ;
            buffer[y][x].Attributes = 0 ;
        }
    }
}

void draw_buffer( HANDLE *hScreen, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, CHAR_INFO** buffer )
{
    SHORT bufferWidth = csbiInfo->dwSize.X ;
    SHORT bufferHeight = csbiInfo->dwSize.Y ;

    COORD bufferSize = { bufferWidth, 1 } ;
    COORD startPoint = { 0, 0 } ;

    SMALL_RECT srWriteRegion = { .Left = csbiInfo->srWindow.Left, .Top = csbiInfo->srWindow.Top,
                                 .Right = csbiInfo->srWindow.Right, .Bottom = csbiInfo->srWindow.Top + 1 } ;

    CHAR_INFO* ciPointer ;

    SetConsoleActiveScreenBuffer( *hScreen ) ;
    SetConsoleCursorPosition( *hScreen, startPoint ) ;

    for( int j = 0; j < bufferHeight; j++ )
    {
        ciPointer = buffer[j] ;

        if( !WriteConsoleOutputA( *hScreen, ciPointer, bufferSize, startPoint, &srWriteRegion ) )
        {
            report_error( "WriteConsoleOutputA( hScreenBufferOne, buffer, bufferSize, startPoint, &csbiInfo.srWindow )" ) ;
        }

        srWriteRegion.Top++ ;
        srWriteRegion.Bottom++ ;
    }
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
    // Ensures drawing is started from correct position. Important for fullscreen drawing, i.e clearing screen buffer.
    //SetConsoleCursorPosition( *phScreenBuffer, characterPosition ) ;

    if( !WriteConsoleOutputA( *phScreenBuffer, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea ) )
    {
      report_error( "WriteConsoleOutputA( *phScreenBuffer, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea )" ) ;
    }

    free( consoleBuffer ) ;
}
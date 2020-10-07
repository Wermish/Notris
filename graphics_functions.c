#include <stdio.h>
#include <Windows.h>
#include "graphics_functions.h"

int draw_rectangle( HANDLE* hScreen )
{
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo ;

    if( !GetConsoleScreenBufferInfo( *hScreen, &csbiInfo ) ){
        fprintf( stderr, "Failed: GetConsoleScreenBufferInfo( *hScreen, &csbiInfo )\n" ) ;
        return EXIT_FAILURE ;
    }

    int bufferWidth = 100 ;
    int bufferHeight = 40 ;

    COORD characterPosition = { 0, 0 } ;
    COORD characterBufferSize = { bufferWidth, bufferHeight } ;
    SMALL_RECT consoleWriteArea = { 0, 0, bufferWidth - 1, bufferHeight - 1 } ;

    CHAR_INFO consoleBuffer[100 * 40] ;

    int x, y ;

    for (y = 0; y < bufferHeight; ++y)
  {
    for (x = 0; x < bufferWidth; ++x)
    {
      consoleBuffer[x + bufferWidth * y].Char.AsciiChar = (unsigned char)219;
      consoleBuffer[x + bufferWidth * y].Attributes = rand() % 256;
    }
  }

  /* Write our character buffer (a single character currently) to the console buffer */
  if( !WriteConsoleOutputA(*hScreen, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea) )
  {
      fprintf( stderr, "%i", GetLastError() ) ;
      return EXIT_FAILURE ;
  }

    return EXIT_SUCCESS ;
}
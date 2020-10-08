#include <stdio.h>
#include <Windows.h>
#include "console_functions.h"
#include "graphics_functions.h"

int draw_rectangle( HANDLE* hScreen )
{
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo ;

    if( !GetConsoleScreenBufferInfo( *hScreen, &csbiInfo ) ){
        report_error( "GetConsoleScreenBufferInfo( *hScreen, &csbiInfo )" ) ;
    }

    SHORT bufferWidth = csbiInfo.dwSize.X ;
    SHORT bufferHeight = csbiInfo.dwSize.Y ;

    COORD characterPosition = { 0, 0 } ;
    COORD characterBufferSize = { bufferWidth, bufferHeight } ;
    SMALL_RECT consoleWriteArea = { 0, 0, bufferWidth - 1, bufferHeight - 1 } ;

    CHAR_INFO* consoleBuffer  = ( CHAR_INFO* ) malloc( ( bufferWidth * bufferWidth ) * sizeof( CHAR_INFO ) ) ;

    if( consoleBuffer == NULL )
    {
      report_error( "Failed: CHAR_INFO* consoleBuffer  = ( CHAR_INFO* ) malloc( ( bufferWidth * bufferWidth ) * sizeof( CHAR_INFO ) )\n" ) ;
      exit( EXIT_FAILURE ) ;
    }

    for (int y = 0; y < bufferHeight; ++y)
    {
      for (int x = 0; x < bufferWidth; ++x)
      {
        consoleBuffer[ x + bufferWidth * y ].Char.AsciiChar = ( unsigned char )219;
        consoleBuffer[ x + bufferWidth * y ].Attributes = rand() % 256;
      }
    }

    /* Write our character buffer (a single character currently) to the console buffer */
    if( !WriteConsoleOutputA( *hScreen, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea ) )
    {
      fprintf( stderr, "%i", GetLastError() ) ;
      return EXIT_FAILURE ;
    }

    free( consoleBuffer ) ;

    return EXIT_SUCCESS ;
}
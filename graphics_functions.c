#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "console_functions.h"
#include "graphics_functions.h"
#include "game_entities.h"

int draw_notris_piece( HANDLE* phScreenBuffer, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, notrisPiece* piece )
{
  


  switch( piece->pieceShape )
  {
    // Square.
    case 1:
      break ;

    // Line.
    case 2:
      
      break ;

    // 'L'.
    case 3:
      break ;

    // Mirrored 'L'.
    case 4:
      break ;

    // 'Z'.
    case 5:
      break ;
    
    // Mirrored 'Z'.
    case 6:
      break ;

    // 'Hat'. 
    case 7:
      break ;
  }

  draw_rectangle( phScreenBuffer, csbiInfo, piece->pieceLook.Char.AsciiChar, piece->pieceLook.Attributes, 
                       piece->blockOne.X, piece->blockOne.Y, piece->blockTwo.X + 1, piece->blockTwo.Y + 1 ) ;

  draw_rectangle( phScreenBuffer, csbiInfo, piece->pieceLook.Char.AsciiChar, piece->pieceLook.Attributes, 
                       piece->blockThree.X, piece->blockThree.Y, piece->blockFour.X + 1, piece->blockFour.Y + 1 ) ;

  return EXIT_SUCCESS ;
}


// To draw a line, the breadth of the line must increase by 1. E.g, startX = 0, startY = 0, endX = 10, endY = 1.
int draw_rectangle( 
                    HANDLE* phScreenBuffer, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, 
                    CHAR asciiValue, WORD asciiAttributes, 
                    SHORT startX, SHORT startY, SHORT endX, SHORT endY 
                  )
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

    return EXIT_SUCCESS ;
}
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "../shared/console_functions.h"
#include "../shared/shared_graphics_functions.h"
#include "notris_graphics_functions.h"
#include "notris_structures.h"

void notris_clear_play_field( HANDLE* hScreenBuffer, struct notrisPlayFieldInfo* npfiInfo )
{
  draw_rectangle( hScreenBuffer, 0, 0, 
                  npfiInfo->playFieldArea.Left, npfiInfo->playFieldArea.Top, npfiInfo->playFieldArea.Right, npfiInfo->playFieldArea.Bottom ) ;
}

void notris_draw_piece( HANDLE* phScreenBuffer, notrisPiece* piece )
{
  DWORD charsWritten = 0 ;
  DWORD attributesWritten = 0 ;

  FillConsoleOutputAttribute( *phScreenBuffer, piece->pieceLook.Attributes, 1, piece->blockOne, &attributesWritten ) ;
  FillConsoleOutputCharacterA( *phScreenBuffer, piece->pieceLook.Char.AsciiChar, 1, piece->blockOne, &charsWritten ) ;

  FillConsoleOutputAttribute( *phScreenBuffer, piece->pieceLook.Attributes, 1, piece->blockTwo, &attributesWritten ) ;
  FillConsoleOutputCharacterA( *phScreenBuffer, piece->pieceLook.Char.AsciiChar, 1, piece->blockTwo, &charsWritten ) ;

  FillConsoleOutputAttribute( *phScreenBuffer, piece->pieceLook.Attributes, 1, piece->blockThree, &attributesWritten ) ;
  FillConsoleOutputCharacterA( *phScreenBuffer, piece->pieceLook.Char.AsciiChar, 1, piece->blockThree, &charsWritten ) ;

  FillConsoleOutputAttribute( *phScreenBuffer, piece->pieceLook.Attributes, 1, piece->blockFour, &attributesWritten ) ;
  FillConsoleOutputCharacterA( *phScreenBuffer, piece->pieceLook.Char.AsciiChar, 1, piece->blockFour, &charsWritten ) ;
}

void notris_draw_UI( HANDLE* hScreenBuffer, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisPlayFieldInfo* npfiInfo )
{
  draw_rectangle( hScreenBuffer, 219, FOREGROUND_RED | FOREGROUND_INTENSITY,
                  npfiInfo->playFieldArea.Left - 1, npfiInfo->playFieldArea.Top - 1,
                  npfiInfo->playFieldArea.Right + 1, npfiInfo->playFieldArea.Top  ) ;

  draw_rectangle( hScreenBuffer, 219, FOREGROUND_RED | FOREGROUND_INTENSITY,
                  npfiInfo->playFieldArea.Left - 1, npfiInfo->playFieldArea.Bottom,
                  npfiInfo->playFieldArea.Right + 1, npfiInfo->playFieldArea.Bottom + 1 ) ;

  draw_rectangle( hScreenBuffer, 219, FOREGROUND_RED | FOREGROUND_INTENSITY,
                  npfiInfo->playFieldArea.Left - 1, npfiInfo->playFieldArea.Top - 1,
                  npfiInfo->playFieldArea.Left, npfiInfo->playFieldArea.Bottom ) ;

  draw_rectangle( hScreenBuffer, 219, FOREGROUND_RED | FOREGROUND_INTENSITY,
                  npfiInfo->playFieldArea.Right, npfiInfo->playFieldArea.Top - 1,
                  npfiInfo->playFieldArea.Right + 1, npfiInfo->playFieldArea.Bottom  ) ;
}

void notris_erase_piece( HANDLE* phScreenBuffer, struct notrisPiece* piece )
{
  /*
  CHAR formerChar = piece->pieceLook.Char.AsciiChar ;
  CHAR formerAttribute = piece->pieceLook.Attributes ;

  piece->pieceLook.Char.AsciiChar = ' ' ;
  piece->pieceLook.Attributes = 0 ;

  draw_notris_piece( phScreenBuffer, csbiInfo, piece ) ;

  piece->pieceLook.Char.AsciiChar = formerChar ;
  piece->pieceLook.Attributes = formerAttribute ;
   */

  DWORD charsWritten = 0 ;
  DWORD attributesWritten = 0 ;

  FillConsoleOutputAttribute( *phScreenBuffer, 0, 1, piece->blockOne, &attributesWritten ) ;
  FillConsoleOutputCharacterA( *phScreenBuffer, 0, 1, piece->blockOne, &charsWritten ) ;

  FillConsoleOutputAttribute( *phScreenBuffer, 0, 1, piece->blockTwo, &attributesWritten ) ;
  FillConsoleOutputCharacterA( *phScreenBuffer, 0, 1, piece->blockTwo, &charsWritten ) ;

  FillConsoleOutputAttribute( *phScreenBuffer, 0, 1, piece->blockThree, &attributesWritten ) ;
  FillConsoleOutputCharacterA( *phScreenBuffer, 0, 1, piece->blockThree, &charsWritten ) ;

  FillConsoleOutputAttribute( *phScreenBuffer, 0, 1, piece->blockFour, &attributesWritten ) ;
  FillConsoleOutputCharacterA( *phScreenBuffer, 0, 1, piece->blockFour, &charsWritten ) ;

}
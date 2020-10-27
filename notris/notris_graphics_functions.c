#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "../shared/console_functions.h"
#include "../shared/shared_graphics_functions.h"
#include "notris_graphics_functions.h"
#include "notris_structures.h"

void notris_clear_play_area( HANDLE* hScreenBuffer, struct notrisPlayFieldInfo* npfiInfo )
{
  draw_rectangle( hScreenBuffer, 0, 0, 
                  npfiInfo->playFieldArea.Left + 1, npfiInfo->playFieldArea.Top + 1, npfiInfo->playFieldArea.Right, npfiInfo->playFieldArea.Bottom ) ;
}

/*
 * Unsure which method is better. draw_rectangle() initialises and declares a few variables and creates a malloc'd array, which it later has to
 * free. It has to populate this array too. It eventually calls WriteConsoleOutputA() to copy array into Screen Buffer. I think that writing the
 * characters and attributes directly to the console with the API is probably faster, using pairs of FillConsoleOutputAttribute/Character, as
 * there's only 4 of them.
 */

void notris_draw_piece( HANDLE* phScreenBuffer, notrisPiece* piece )
{
  /*
    draw_rectangle( phScreenBuffer, csbiInfo, piece->pieceLook.Char.AsciiChar, piece->pieceLook.Attributes,
                    piece->blockOne.X, piece->blockOne.Y, piece->blockOne.X + 1, piece->blockOne.Y + 1 ) ;

    draw_rectangle( phScreenBuffer, csbiInfo, piece->pieceLook.Char.AsciiChar, piece->pieceLook.Attributes,
                    piece->blockTwo.X, piece->blockTwo.Y, piece->blockTwo.X + 1, piece->blockTwo.Y + 1) ;

    draw_rectangle( phScreenBuffer, csbiInfo, piece->pieceLook.Char.AsciiChar, piece->pieceLook.Attributes,
                    piece->blockThree.X, piece->blockThree.Y, piece->blockThree.X + 1, piece->blockThree.Y + 1 ) ;

    draw_rectangle( phScreenBuffer, csbiInfo, piece->pieceLook.Char.AsciiChar, piece->pieceLook.Attributes,
                    piece->blockFour.X, piece->blockFour.Y, piece->blockFour.X + 1, piece->blockFour.Y + 1 ) ;
   */

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


void notris_draw_play_field( HANDLE* phScreenBuffer, struct notrisPlayFieldInfo* npfiInfo )
{

  draw_rectangle( phScreenBuffer, 0, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY,
                  npfiInfo->playFieldArea.Left, npfiInfo->playFieldArea.Top,
                  npfiInfo->playFieldArea.Right, npfiInfo->playFieldArea.Top + 1  ) ;

  draw_rectangle( phScreenBuffer, 0, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY,
                  npfiInfo->playFieldArea.Left, npfiInfo->playFieldArea.Bottom,
                  npfiInfo->playFieldArea.Right, npfiInfo->playFieldArea.Bottom + 1 ) ;

  draw_rectangle( phScreenBuffer, 0, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY,
                  npfiInfo->playFieldArea.Left, npfiInfo->playFieldArea.Top,
                  npfiInfo->playFieldArea.Left + 1, npfiInfo->playFieldArea.Bottom  ) ;

  draw_rectangle( phScreenBuffer, 0, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY,
                  npfiInfo->playFieldArea.Right, npfiInfo->playFieldArea.Top,
                  npfiInfo->playFieldArea.Right + 1, npfiInfo->playFieldArea.Bottom + 1  ) ;
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
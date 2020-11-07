#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "../shared/console_functions.h"
#include "../shared/shared_graphics_functions.h"
#include "notris_graphics_functions.h"
#include "notris_structures.h"

void notris_clear_play_field( HANDLE* hScreenBuffer, struct notrisInfo* niInfo )
{
  draw_rectangle( hScreenBuffer, 0, 0, 
                  niInfo->playFieldArea.Left, niInfo->playFieldArea.Top, niInfo->playFieldArea.Right, niInfo->playFieldArea.Bottom ) ;
}

void notris_draw_piece( struct notrisInfo* niInfo, struct notrisPiece* piece )
{
  niInfo->ciNotrisScreenBuffer[piece->blockOne.Y][piece->blockOne.X].Char.AsciiChar = piece->pieceLook.Char.AsciiChar ;
  niInfo->ciNotrisScreenBuffer[piece->blockOne.Y][piece->blockOne.X].Attributes = piece->pieceLook.Attributes ;

  niInfo->ciNotrisScreenBuffer[piece->blockTwo.Y][piece->blockTwo.X].Char.AsciiChar = piece->pieceLook.Char.AsciiChar ;
  niInfo->ciNotrisScreenBuffer[piece->blockTwo.Y][piece->blockTwo.X].Attributes = piece->pieceLook.Attributes ;

  niInfo->ciNotrisScreenBuffer[piece->blockThree.Y][piece->blockThree.X].Char.AsciiChar = piece->pieceLook.Char.AsciiChar ;
  niInfo->ciNotrisScreenBuffer[piece->blockThree.Y][piece->blockThree.X].Attributes = piece->pieceLook.Attributes ;

  niInfo->ciNotrisScreenBuffer[piece->blockFour.Y][piece->blockFour.X].Char.AsciiChar = piece->pieceLook.Char.AsciiChar ;
  niInfo->ciNotrisScreenBuffer[piece->blockFour.Y][piece->blockFour.X].Attributes = piece->pieceLook.Attributes ;
}

void notris_draw_UI( HANDLE* hScreenBuffer, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisInfo* niInfo )
{
  draw_rectangle( hScreenBuffer, 219, FOREGROUND_RED | FOREGROUND_INTENSITY,
                  niInfo->playFieldArea.Left - 1, niInfo->playFieldArea.Top - 1,
                  niInfo->playFieldArea.Right + 1, niInfo->playFieldArea.Top  ) ;

  draw_rectangle( hScreenBuffer, 219, FOREGROUND_RED | FOREGROUND_INTENSITY,
                  niInfo->playFieldArea.Left - 1, niInfo->playFieldArea.Bottom,
                  niInfo->playFieldArea.Right + 1, niInfo->playFieldArea.Bottom + 1 ) ;

  draw_rectangle( hScreenBuffer, 219, FOREGROUND_RED | FOREGROUND_INTENSITY,
                  niInfo->playFieldArea.Left - 1, niInfo->playFieldArea.Top - 1,
                  niInfo->playFieldArea.Left, niInfo->playFieldArea.Bottom ) ;

  draw_rectangle( hScreenBuffer, 219, FOREGROUND_RED | FOREGROUND_INTENSITY,
                  niInfo->playFieldArea.Right, niInfo->playFieldArea.Top - 1,
                  niInfo->playFieldArea.Right + 1, niInfo->playFieldArea.Bottom  ) ;
}

void notris_erase_piece( struct notrisInfo* niInfo, struct notrisPiece* piece )
{
  niInfo->ciNotrisScreenBuffer[piece->blockOne.Y][piece->blockOne.X].Char.AsciiChar = 0 ;
  niInfo->ciNotrisScreenBuffer[piece->blockOne.Y][piece->blockOne.X].Attributes = 0 ;

  niInfo->ciNotrisScreenBuffer[piece->blockTwo.Y][piece->blockTwo.X].Char.AsciiChar = 0 ;
  niInfo->ciNotrisScreenBuffer[piece->blockTwo.Y][piece->blockTwo.X].Attributes = 0 ;

  niInfo->ciNotrisScreenBuffer[piece->blockThree.Y][piece->blockThree.X].Char.AsciiChar = 0 ;
  niInfo->ciNotrisScreenBuffer[piece->blockThree.Y][piece->blockThree.X].Attributes = 0 ;

  niInfo->ciNotrisScreenBuffer[piece->blockFour.Y][piece->blockFour.X].Char.AsciiChar = 0 ;
  niInfo->ciNotrisScreenBuffer[piece->blockFour.Y][piece->blockFour.X].Attributes = 0 ;
}
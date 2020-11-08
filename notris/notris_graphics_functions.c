#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "../shared/console_functions.h"
#include "../shared/shared_graphics_functions.h"
#include "notris_graphics_functions.h"
#include "notris_structures.h"

/*
 * These functions don't draw to the screen directly. Instead they set values in the NotrisScreenBuffer which is then drawn.
 * They also toggle BOOLs in the NotrisCollisionArray to signal that the cell is occupied.
 */

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

void notris_draw_UI( struct notrisInfo* niInfo )
{
  for( int roof = niInfo->playFieldArea.Left - 1; roof < niInfo->playFieldArea.Right + 1 ; roof++ )
  {
    niInfo->ciNotrisScreenBuffer[niInfo->playFieldArea.Top - 1][roof].Char.AsciiChar = 219 ;
    niInfo->ciNotrisScreenBuffer[niInfo->playFieldArea.Top - 1][roof].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY ;
    niInfo->boNotrisCollisionArray[niInfo->playFieldArea.Top - 1][roof] = 1 ;
  }

  for( int floor = niInfo->playFieldArea.Left - 1; floor < niInfo->playFieldArea.Right + 1; floor++ )
  {
    niInfo->ciNotrisScreenBuffer[niInfo->playFieldArea.Bottom][floor].Char.AsciiChar = 219 ;
    niInfo->ciNotrisScreenBuffer[niInfo->playFieldArea.Bottom][floor].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY ;
    niInfo->boNotrisCollisionArray[niInfo->playFieldArea.Bottom][floor] = 1 ;
  }

  for( int leftWall = niInfo->playFieldArea.Top; leftWall < niInfo->playFieldArea.Bottom; leftWall++ )
  {
    niInfo->ciNotrisScreenBuffer[leftWall][niInfo->playFieldArea.Left - 1].Char.AsciiChar = 219 ;
    niInfo->ciNotrisScreenBuffer[leftWall][niInfo->playFieldArea.Left - 1].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY ;
    niInfo->boNotrisCollisionArray[leftWall][niInfo->playFieldArea.Left - 1] = 1 ;
  }

  for( int rightWall = niInfo->playFieldArea.Top; rightWall < niInfo->playFieldArea.Bottom; rightWall++ )
  {
    niInfo->ciNotrisScreenBuffer[rightWall][niInfo->playFieldArea.Right].Char.AsciiChar = 219 ;
    niInfo->ciNotrisScreenBuffer[rightWall][niInfo->playFieldArea.Right].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY ;
    niInfo->boNotrisCollisionArray[rightWall][niInfo->playFieldArea.Right] = 1 ;
  }
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
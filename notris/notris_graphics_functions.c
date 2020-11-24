#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "../shared/console_functions.h"
#include "../shared/shared_game_functions.h"
#include "../shared/shared_graphics_functions.h"
#include "notris_graphics_functions.h"
#include "notris_structures.h"

/*
 * These functions don't draw to the screen directly. Instead they set values in the NotrisScreenBuffer which is then drawn.
 */

void notris_clear_play_field( HANDLE* hScreenBuffer, struct notrisInfo* niInfo )
{
  draw_rectangle( hScreenBuffer, 0, 0, 
                  niInfo->srPlayFieldArea.Left, niInfo->srPlayFieldArea.Top, niInfo->srPlayFieldArea.Right, niInfo->srPlayFieldArea.Bottom ) ;
}

void notris_draw_piece( struct notrisInfo* niInfo, struct notrisPiece* piece )
{
  niInfo->ciNotrisScreenBuffer[piece->blockOne.Y][piece->blockOne.X].Char.AsciiChar = 49 /*piece->pieceLook.Char.AsciiChar*/ ;
  niInfo->ciNotrisScreenBuffer[piece->blockOne.Y][piece->blockOne.X].Attributes = piece->pieceLook.Attributes ;
  niInfo->boNotrisCollisionArray[piece->blockOne.Y][piece->blockOne.X] = 1 ;

  niInfo->ciNotrisScreenBuffer[piece->blockTwo.Y][piece->blockTwo.X].Char.AsciiChar = 50 /*piece->pieceLook.Char.AsciiChar*/ ;
  niInfo->ciNotrisScreenBuffer[piece->blockTwo.Y][piece->blockTwo.X].Attributes = piece->pieceLook.Attributes ;
  niInfo->boNotrisCollisionArray[piece->blockTwo.Y][piece->blockTwo.X] = 1 ;

  niInfo->ciNotrisScreenBuffer[piece->blockThree.Y][piece->blockThree.X].Char.AsciiChar = 51 /*piece->pieceLook.Char.AsciiChar*/ ;
  niInfo->ciNotrisScreenBuffer[piece->blockThree.Y][piece->blockThree.X].Attributes = piece->pieceLook.Attributes ;
  niInfo->boNotrisCollisionArray[piece->blockThree.Y][piece->blockThree.X] = 1 ;

  niInfo->ciNotrisScreenBuffer[piece->blockFour.Y][piece->blockFour.X].Char.AsciiChar = 52 /*piece->pieceLook.Char.AsciiChar*/ ;
  niInfo->ciNotrisScreenBuffer[piece->blockFour.Y][piece->blockFour.X].Attributes = piece->pieceLook.Attributes ;
  niInfo->boNotrisCollisionArray[piece->blockFour.Y][piece->blockFour.X] = 1 ;
}

void notris_draw_UI( struct notrisInfo* niInfo )
{
  for( int roof = niInfo->srPlayFieldArea.Left - 1; roof < niInfo->srPlayFieldArea.Right + 1 ; roof++ )
  {
    niInfo->ciNotrisScreenBuffer[niInfo->srPlayFieldArea.Top - 1][roof].Char.AsciiChar = 0 ;
    niInfo->ciNotrisScreenBuffer[niInfo->srPlayFieldArea.Top - 1][roof].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY ;
  }

  for( int floor = niInfo->srPlayFieldArea.Left - 1; floor < niInfo->srPlayFieldArea.Right + 1; floor++ )
  {
    niInfo->ciNotrisScreenBuffer[niInfo->srPlayFieldArea.Bottom][floor].Char.AsciiChar = 0 ;
    niInfo->ciNotrisScreenBuffer[niInfo->srPlayFieldArea.Bottom][floor].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY ;
  }

  for( int leftWall = niInfo->srPlayFieldArea.Top; leftWall < niInfo->srPlayFieldArea.Bottom; leftWall++ )
  {
    niInfo->ciNotrisScreenBuffer[leftWall][niInfo->srPlayFieldArea.Left - 1].Char.AsciiChar = 0 ;
    niInfo->ciNotrisScreenBuffer[leftWall][niInfo->srPlayFieldArea.Left - 1].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY ;
  }

  for( int rightWall = niInfo->srPlayFieldArea.Top; rightWall < niInfo->srPlayFieldArea.Bottom; rightWall++ )
  {
    niInfo->ciNotrisScreenBuffer[rightWall][niInfo->srPlayFieldArea.Right].Char.AsciiChar = 0 ;
    niInfo->ciNotrisScreenBuffer[rightWall][niInfo->srPlayFieldArea.Right].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY ;
  }
}

void notris_erase_piece( struct notrisInfo* niInfo, struct notrisPiece* piece )
{
  niInfo->ciNotrisScreenBuffer[piece->blockOne.Y][piece->blockOne.X].Char.AsciiChar = 0 ;
  niInfo->ciNotrisScreenBuffer[piece->blockOne.Y][piece->blockOne.X].Attributes = 0 ;
  niInfo->boNotrisCollisionArray[piece->blockOne.Y][piece->blockOne.X] = 0 ;

  niInfo->ciNotrisScreenBuffer[piece->blockTwo.Y][piece->blockTwo.X].Char.AsciiChar = 0 ;
  niInfo->ciNotrisScreenBuffer[piece->blockTwo.Y][piece->blockTwo.X].Attributes = 0 ;
  niInfo->boNotrisCollisionArray[piece->blockTwo.Y][piece->blockTwo.X] = 0 ;

  niInfo->ciNotrisScreenBuffer[piece->blockThree.Y][piece->blockThree.X].Char.AsciiChar = 0 ;
  niInfo->ciNotrisScreenBuffer[piece->blockThree.Y][piece->blockThree.X].Attributes = 0 ;
  niInfo->boNotrisCollisionArray[piece->blockThree.Y][piece->blockThree.X] = 0 ;

  niInfo->ciNotrisScreenBuffer[piece->blockFour.Y][piece->blockFour.X].Char.AsciiChar = 0 ;
  niInfo->ciNotrisScreenBuffer[piece->blockFour.Y][piece->blockFour.X].Attributes = 0 ;
  niInfo->boNotrisCollisionArray[piece->blockFour.Y][piece->blockFour.X] = 0 ;
}

/*
 * Counts BOOLs in each row of notrisInfo.boCollisionArray with cellCounter. If all 1, increments rowCounter, thus marking row for deletion, and adds it to 
 * toErase array.
 * qsort() rows into descending order. The row with greatest y value, i.e. the lowest spatially, is first in array.
 * toErase is iterated over. If toErase[n] has value > 0, all row values from y == toErase[n] decreasing are shifted down, i.e. 
 * niInfo.ciNotrisScreenBuffer[y][x] = niInfo.ciNotrisScreenBuffer[y - 1][x].
 */

void notris_erase_row( struct notrisInfo* niInfo )
{
  SHORT floor = niInfo->srPlayFieldArea.Bottom - 1 ;
  SHORT ceiling = niInfo->srPlayFieldArea.Top + 1 ;
  SHORT left = niInfo->srPlayFieldArea.Left ;
  SHORT right = niInfo->srPlayFieldArea.Right ;

  SHORT cellCounter = 0 ;
  SHORT rowCounter = 0 ;

  SHORT toErase[4] = { 0, 0, 0, 0 } ;

  for( int y = floor; y > ceiling; y-- )
  {
    for( int x = left; x < right; x++ )
    {
      if( niInfo->boNotrisCollisionArray[y][x] )
      {
        cellCounter++ ;
      }
    }
    if( cellCounter / ( right - left ) == 1 )
    {
      toErase[rowCounter] = y ;
      rowCounter++ ;
    }
    cellCounter = 0 ;
  }

  qsort( toErase, 4, sizeof( SHORT ), comparator_descending ) ;

  if( rowCounter )
  {
    for( int r = 0; r < 4; r++ )
    {
      if( toErase[r] )
      {
        for( int y = toErase[r]; y >= ceiling; y -- )
        {
          for( int x = left; x < right; x++ ) 
          {
            if( y == ceiling )
            {
              niInfo->ciNotrisScreenBuffer[y][x].Char.AsciiChar = 0 ;
              niInfo->ciNotrisScreenBuffer[y][x].Attributes = 0 ;
              niInfo->boNotrisCollisionArray[y][x] = 0 ;
            }
            else
            {
              niInfo->ciNotrisScreenBuffer[y][x].Char.AsciiChar = niInfo->ciNotrisScreenBuffer[y - 1][x].Char.AsciiChar ;
              niInfo->ciNotrisScreenBuffer[y][x].Attributes = niInfo->ciNotrisScreenBuffer[y - 1][x].Attributes ;
              niInfo->boNotrisCollisionArray[y][x] = niInfo->boNotrisCollisionArray[y - 1][x] ;
            }
          }
        }
      }
    }
  }
}
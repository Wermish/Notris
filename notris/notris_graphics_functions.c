#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "../shared/console_functions.h"
#include "../shared/shared_game_functions.h"
#include "../shared/shared_graphics_functions.h"
#include "notris_game_functions.h"
#include "notris_graphics_functions.h"
#include "notris_structures.h"

/*
 * These functions don't draw to the screen directly. Instead they set values in the NotrisScreenBuffer which is then drawn.
 */

void notris_clear_play_field( CHAR_INFO** buffer, struct notrisInfo* niInfo )
{
  draw_rectangle( buffer, 0, 0, 
                  niInfo->srPlayFieldArea.Left, niInfo->srPlayFieldArea.Top, niInfo->srPlayFieldArea.Right, niInfo->srPlayFieldArea.Bottom ) ;
}

void notris_draw_hiscore_table( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, CHAR_INFO** buffer )
{

}

void notris_draw_level( CHAR_INFO** buffer, struct notrisInfo* niInfo, SHORT startX, SHORT startY )
{
  CHAR level[2] ;

  sprintf( level, "%i", niInfo->level ) ;

  draw_string( level, buffer, startX, startY, FOREGROUND_BLUE | FOREGROUND_INTENSITY ) ;
}

void notris_draw_level_options( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisInfo* niInfo, struct notrisMenu* nmMenu )
{
  draw_rectangle( nmMenu->ciNotrisMainMenu, 0, 0, 1, 11, 39, 39 ) ;
  draw_string( "LEVEL:", nmMenu->ciNotrisMainMenu, 18, 18, 0x0004 | 0x0002 | 0x0001 | 0x0008 ) ;
  notris_draw_level( nmMenu->ciNotrisMainMenu, niInfo, 24, 18 ) ;
}

void notris_draw_logo( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, CHAR_INFO** buffer, SHORT startX, SHORT startY )
{

  SHORT bubbleY = 0 ;
  SHORT bubbleX = 0 ;

  WORD attributes[] = { FOREGROUND_RED, FOREGROUND_GREEN, FOREGROUND_BLUE,
                        FOREGROUND_RED | FOREGROUND_INTENSITY, FOREGROUND_GREEN | FOREGROUND_INTENSITY, FOREGROUND_BLUE | FOREGROUND_INTENSITY, 
                        FOREGROUND_RED | FOREGROUND_GREEN, FOREGROUND_RED | FOREGROUND_BLUE, FOREGROUND_GREEN | FOREGROUND_BLUE,
                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
                        FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY } ;

  WORD bubbleAttribute = 0 ;

  CHAR logo[6][5][5]={ {{219, 219, 219, 219, 219},
                        {219,  0,  0,   0,   219},
                        {219,  0,  0,   0,   219},
                        {219,  0,  0,   0,   219},
                        {219,  0,  0,   0,   219} },

                       {{219, 219, 219, 219, 219},
                        {219, 0,   0,   0,   219},
                        {219, 0,   0,   0,   219},
                        {219, 0,   0,   0,   219},
                        {219, 219, 219, 219, 219} },
  
                       {{219, 219, 219, 219, 219},
                        {0,   0,   219, 0,   0  },
                        {0,   0,   219, 0,   0  },
                        {0,   0,   219, 0,   0  },
                        {0,   0,   219, 0,   0  } },

                       {{219, 219, 219, 219, 219},
                        {219, 0,   0,   0,   219},
                        {219, 0,   0,   219, 219},
                        {219, 0,   0,   219, 0  },
                        {219, 0,   0,   219, 219} },

                       {{219, 219, 219, 219, 219},
                        {0,   0,   219, 0,   0  },
                        {0,   0,   219, 0,   0  },
                        {0,   0,   219, 0,   0  },
                        {219, 219, 219, 219, 219} },

                       {{219, 219, 219, 219, 219},
                        {219, 0,   0,   0,   0  },
                        {219, 219, 219, 219, 219},
                        {0,   0,   0,   0,   219},
                        {219, 219, 219, 219, 219} }} ; 

  for( int i = 0; i < 6; i++ )
  {

    bubbleAttribute = attributes[random_number_in_range(0, 11)] ;      

    for( int y = startY; y < ( startY + 5 ); y++ )
    {
      for( int x = startX; x < ( startX + 5 ); x++ )
      {
        if( logo[i][bubbleY][bubbleX] )
        {
          buffer[y][x].Char.AsciiChar = logo[i][bubbleY][bubbleX] ;
          buffer[y][x].Attributes = bubbleAttribute ;
        }
        bubbleX++ ;
      }
      bubbleY++ ;
      bubbleX = 0 ;
    }
    startX += 6 ;
    bubbleY = 0 ;
  }
}

void notris_draw_menu( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisMenu* nmMenu)
{

  draw_rectangle( nmMenu->ciNotrisMainMenu, 219, 0x0004| 0x0002 |0x0001 | 0x0008, 1, 1, 40, 2 ) ;
  draw_rectangle( nmMenu->ciNotrisMainMenu, 219, 0x0004| 0x0002 |0x0001 | 0x0008, 1, 9, 40, 10 ) ;

  notris_draw_logo( csbiInfo, nmMenu->ciNotrisMainMenu, 3, 3 ) ;

  notris_draw_menu_options( csbiInfo, nmMenu ) ;

}

void notris_draw_menu_options( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisMenu* nmMenu )
{
  draw_rectangle(  nmMenu->ciNotrisMainMenu, 0, 0, 1, 11, 39, 39  ) ;

  draw_string( "PLAY", nmMenu->ciNotrisMainMenu, 18, 18, 0x0004| 0x0002 |0x0001 | 0x0008 ) ;
  draw_string( "SCORES", nmMenu->ciNotrisMainMenu, 18, 20, 0x0004| 0x0002 |0x0001 | 0x0008 ) ;
  draw_string( "EXIT", nmMenu->ciNotrisMainMenu, 18, 22, 0x0004| 0x0002 |0x0001 | 0x0008 ) ;

  nmMenu->ciNotrisMainMenu[nmMenu->cursorPosition.Y][nmMenu->cursorPosition.X].Char.AsciiChar = 26 ;
  nmMenu->ciNotrisMainMenu[nmMenu->cursorPosition.Y][nmMenu->cursorPosition.X].Attributes = 0x0004| 0x0002 |0x0001 | 0x0008 ;
}

void notris_draw_next( struct notrisInfo* niInfo )
{
  for( int y = niInfo->srNextPieceArea.Top + 1; y <= niInfo->srNextPieceArea.Bottom; y++ )
  {
    for( int x = niInfo->srNextPieceArea.Left; x <= niInfo->srNextPieceArea.Right; x++ )
    {
      niInfo->ciNotrisScreenBuffer[y][x].Char.AsciiChar = 0 ;
      niInfo->ciNotrisScreenBuffer[y][x].Attributes = 0 ;
    }
  }

  notrisPiece* next = notris_create_piece( niInfo->nextPiece, niInfo, niInfo->srNextPieceArea.Left + 2, niInfo->srNextPieceArea.Top + 2 ) ;

  notris_draw_piece( niInfo, next ) ;

  free( next ) ;
}

void notris_draw_piece( struct notrisInfo* niInfo, struct notrisPiece* piece )
{
  niInfo->ciNotrisScreenBuffer[piece->blockOne.Y][piece->blockOne.X].Char.AsciiChar = piece->pieceLook.Char.AsciiChar ;
  niInfo->ciNotrisScreenBuffer[piece->blockOne.Y][piece->blockOne.X].Attributes = piece->pieceLook.Attributes ;
  niInfo->boNotrisCollisionArray[piece->blockOne.Y][piece->blockOne.X] = 1 ;

  niInfo->ciNotrisScreenBuffer[piece->blockTwo.Y][piece->blockTwo.X].Char.AsciiChar = piece->pieceLook.Char.AsciiChar ;
  niInfo->ciNotrisScreenBuffer[piece->blockTwo.Y][piece->blockTwo.X].Attributes = piece->pieceLook.Attributes ;
  niInfo->boNotrisCollisionArray[piece->blockTwo.Y][piece->blockTwo.X] = 1 ;

  niInfo->ciNotrisScreenBuffer[piece->blockThree.Y][piece->blockThree.X].Char.AsciiChar = piece->pieceLook.Char.AsciiChar ;
  niInfo->ciNotrisScreenBuffer[piece->blockThree.Y][piece->blockThree.X].Attributes = piece->pieceLook.Attributes ;
  niInfo->boNotrisCollisionArray[piece->blockThree.Y][piece->blockThree.X] = 1 ;

  niInfo->ciNotrisScreenBuffer[piece->blockFour.Y][piece->blockFour.X].Char.AsciiChar = piece->pieceLook.Char.AsciiChar ;
  niInfo->ciNotrisScreenBuffer[piece->blockFour.Y][piece->blockFour.X].Attributes = piece->pieceLook.Attributes ;
  niInfo->boNotrisCollisionArray[piece->blockFour.Y][piece->blockFour.X] = 1 ;
}

void notris_draw_score( struct notrisInfo* niInfo )
{
  CHAR score[8] ;

  sprintf( score, "%i", niInfo->notrisScore ) ;

  draw_string( score, niInfo->ciNotrisScreenBuffer, niInfo->srScoreArea.Left, niInfo->srScoreArea.Top + 2, FOREGROUND_BLUE | FOREGROUND_INTENSITY ) ;
}

void notris_draw_UI( struct notrisInfo* niInfo )
{
  // Draw PlayFieldArea border
  for( int roof = niInfo->srPlayFieldArea.Left - 1; roof < niInfo->srPlayFieldArea.Right + 1 ; roof++ )
  {
    niInfo->ciNotrisScreenBuffer[niInfo->srPlayFieldArea.Top - 1][roof].Char.AsciiChar = 0 ;
    niInfo->ciNotrisScreenBuffer[niInfo->srPlayFieldArea.Top - 1][roof].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED ;

    niInfo->ciNotrisPauseMenu[niInfo->srPlayFieldArea.Top - 1][roof].Char.AsciiChar = 0 ;
    niInfo->ciNotrisPauseMenu[niInfo->srPlayFieldArea.Top - 1][roof].Attributes = BACKGROUND_BLUE | BACKGROUND_INTENSITY ;

    niInfo->boNotrisCollisionArray[niInfo->srPlayFieldArea.Top - 1][roof] = 1 ;                                                                                 
  }

  for( int floor = niInfo->srPlayFieldArea.Left - 1; floor < niInfo->srPlayFieldArea.Right + 1; floor++ )
  {
    niInfo->ciNotrisScreenBuffer[niInfo->srPlayFieldArea.Bottom][floor].Char.AsciiChar = 0 ;
    niInfo->ciNotrisScreenBuffer[niInfo->srPlayFieldArea.Bottom][floor].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED ;

    niInfo->ciNotrisPauseMenu[niInfo->srPlayFieldArea.Bottom][floor].Char.AsciiChar = 0 ;
    niInfo->ciNotrisPauseMenu[niInfo->srPlayFieldArea.Bottom][floor].Attributes = BACKGROUND_BLUE | BACKGROUND_INTENSITY ;

    niInfo->boNotrisCollisionArray[niInfo->srPlayFieldArea.Bottom][floor] = 1 ;                                                                                
  }

  for( int leftWall = niInfo->srPlayFieldArea.Top; leftWall < niInfo->srPlayFieldArea.Bottom; leftWall++ )
  {
    niInfo->ciNotrisScreenBuffer[leftWall][niInfo->srPlayFieldArea.Left - 1].Char.AsciiChar = 0 ;
    niInfo->ciNotrisScreenBuffer[leftWall][niInfo->srPlayFieldArea.Left - 1].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED ;

    niInfo->ciNotrisPauseMenu[leftWall][niInfo->srPlayFieldArea.Left - 1].Char.AsciiChar = 0 ;
    niInfo->ciNotrisPauseMenu[leftWall][niInfo->srPlayFieldArea.Left - 1].Attributes = BACKGROUND_BLUE | BACKGROUND_INTENSITY ;

    niInfo->boNotrisCollisionArray[leftWall][niInfo->srPlayFieldArea.Left - 1] = 1 ;                                                                                                                                                                          
  }

  for( int rightWall = niInfo->srPlayFieldArea.Top; rightWall < niInfo->srPlayFieldArea.Bottom; rightWall++ )
  {
    niInfo->ciNotrisScreenBuffer[rightWall][niInfo->srPlayFieldArea.Right].Char.AsciiChar = 0 ;
    niInfo->ciNotrisScreenBuffer[rightWall][niInfo->srPlayFieldArea.Right].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED ;

    niInfo->ciNotrisPauseMenu[rightWall][niInfo->srPlayFieldArea.Right].Char.AsciiChar = 0 ;
    niInfo->ciNotrisPauseMenu[rightWall][niInfo->srPlayFieldArea.Right].Attributes = BACKGROUND_BLUE | BACKGROUND_INTENSITY ;

    niInfo->boNotrisCollisionArray[rightWall][niInfo->srPlayFieldArea.Right] = 1 ;                                                                                      
  }

  draw_string( "SCORE", niInfo->ciNotrisScreenBuffer, niInfo->srScoreArea.Left, niInfo->srScoreArea.Top, FOREGROUND_RED | FOREGROUND_INTENSITY ) ;

  draw_string( "LEVEL", niInfo->ciNotrisScreenBuffer, niInfo->srLevelArea.Left, niInfo->srLevelArea.Top, FOREGROUND_RED | FOREGROUND_INTENSITY ) ;

  draw_string( "NEXT", niInfo->ciNotrisScreenBuffer, niInfo->srNextPieceArea.Left, niInfo->srNextPieceArea.Top, FOREGROUND_RED | FOREGROUND_INTENSITY ) ;

  draw_string( "PAUSED", niInfo->ciNotrisPauseMenu, niInfo->srPlayFieldArea.Left + 2, niInfo->srPlayFieldArea.Top + 3, FOREGROUND_BLUE | FOREGROUND_INTENSITY ) ;

  draw_string( "RESUME", niInfo->ciNotrisPauseMenu, niInfo->srPlayFieldArea.Left + 2, niInfo->srPlayFieldArea.Top + 7, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN ) ;

  draw_string( "EXIT", niInfo->ciNotrisPauseMenu, niInfo->srPlayFieldArea.Left + 2, niInfo->srPlayFieldArea.Top + 10, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN ) ;
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
 * Rows are counted from 0y increasing. Thus the row are stored in ascending order in toErase[4].
 * toErase is iterated over. If toErase[n] has value > 0, all row values from y == toErase[n] to 0y  are shifted down, i.e. 
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

  for( int y = ceiling; y <= floor; y++ )
  {
    for( int x = left; x < right; x++ )
    {
      if( niInfo->boNotrisCollisionArray[y][x] )
      {
        cellCounter++ ;
      }
    }
    if( cellCounter >= ( right - left ) )
    {
      toErase[rowCounter] = y ;
      rowCounter++ ;
    }
    cellCounter = 0 ;
  }

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

    switch( rowCounter )
    {
      case 1:
        niInfo->notrisScore += (  100 * niInfo->level ) ;
        break ;

      case 2:
        niInfo->notrisScore += ( 300 * niInfo->level );
        break ;
        
      case 3:
        niInfo->notrisScore += ( 500 * niInfo->level );
        break ;
        
      case 4:
        niInfo->notrisScore += ( 800 * niInfo->level ) ;
        break ;       
    }

    if( niInfo->level < 7 )
    {
      if( niInfo->notrisScore >= ( 1500 * niInfo->level ) )
      {
        niInfo->level++ ;
      }
    }
  }
}
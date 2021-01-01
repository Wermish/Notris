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
 * These functions don't draw to the screen directly. Instead they set values in the notrisScreenBuffer which is then drawn.
 */

void notris_clear_play_field( CHAR_INFO** buffer, struct notrisInfo* niInfo )
{
  draw_rectangle( buffer, 0, 0, 
                  niInfo->srPlayFieldArea.Left, niInfo->srPlayFieldArea.Top, niInfo->srPlayFieldArea.Right, niInfo->srPlayFieldArea.Bottom ) ;
}

void notris_draw_game_over( struct notrisInfo* niInfo )
{
  notris_clear_play_field( niInfo->cinotrisScreenBuffer, niInfo );
                    
  draw_string( "GAME", niInfo->cinotrisScreenBuffer, niInfo->srPlayFieldArea.Left + 2, niInfo->srPlayFieldArea.Top + 3, 0x0004 ) ;
  draw_string( "OVER", niInfo->cinotrisScreenBuffer, niInfo->srPlayFieldArea.Left + 3, niInfo->srPlayFieldArea.Top + 4, 0x0004 ) ;
  draw_string( "NAME:", niInfo->cinotrisScreenBuffer, niInfo->srPlayFieldArea.Left + 1, niInfo->srPlayFieldArea.Top + 7, 0x0004 ) ;
}

void notris_draw_top_scores( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisMenu* nmMenu, FILE** fTopScores )
{
  notrisScore nsScore ;

  CHAR playerTag[4] ;
  CHAR scoreRecord[10] ; 

  SHORT edgePadding = 2 ;
  SHORT recordPadding = 0 ;

  draw_rectangle( nmMenu->cinotrisTopScores, 219, 0x001 | 0x002 | 0x004 | 0x008, 
                  nmMenu->srScoreBox.Left, nmMenu->srScoreBox.Top, nmMenu->srScoreBox.Right, nmMenu->srScoreBox.Top + 1 ) ;
  draw_rectangle( nmMenu->cinotrisTopScores, 219, 0x001 | 0x002 | 0x004 | 0x008, 
                  nmMenu->srScoreBox.Left, nmMenu->srScoreBox.Bottom, nmMenu->srScoreBox.Right, nmMenu->srScoreBox.Bottom + 1 ) ;
  draw_rectangle( nmMenu->cinotrisTopScores, 219, 0x001 | 0x002 | 0x004 | 0x008, 
                  nmMenu->srScoreBox.Left, nmMenu->srScoreBox.Top, nmMenu->srScoreBox.Left + 1, nmMenu->srScoreBox.Bottom ) ;
  draw_rectangle( nmMenu->cinotrisTopScores, 219, 0x001 | 0x002 | 0x004 | 0x008, 
                  nmMenu->srScoreBox.Right - 1, nmMenu->srScoreBox.Top, nmMenu->srScoreBox.Right, nmMenu->srScoreBox.Bottom ) ;

  *fTopScores = fopen( "notris.scores", "rb" ) ;

  for( int i = 0; i < 10; i++ )
  {
    fread( &nsScore, sizeof( struct notrisScore ), 1, *fTopScores ) ;

    sprintf( playerTag, "%c%c%c", nsScore.chPlayerTag[0], nsScore.chPlayerTag[1], nsScore.chPlayerTag[2] ) ;

    sprintf( scoreRecord, "%i", nsScore.dwScore ) ;

    draw_string( playerTag, nmMenu->cinotrisTopScores,
                (nmMenu->srScoreBox.Left + edgePadding ), nmMenu->srScoreBox.Top + edgePadding + recordPadding,
                0x0001 | 0x0002 | 0x0004 | 0x0008  ) ;

    draw_string( scoreRecord, nmMenu->cinotrisTopScores, 
               ( ( nmMenu->srScoreBox.Right - count_digits( nsScore.dwScore ) ) - edgePadding ), nmMenu->srScoreBox.Top + edgePadding + recordPadding,
               0x0001 | 0x0002 | 0x0004 | 0x0008 ) ;

    recordPadding += 2 ;
  }

  fclose( *fTopScores ) ;
}

void notris_draw_level( CHAR_INFO** buffer, struct notrisInfo* niInfo, SHORT startX, SHORT startY )
{
  CHAR level[2] ;

  sprintf( level, "%i", niInfo->level ) ;

  draw_string( level, buffer, startX, startY, FOREGROUND_BLUE | FOREGROUND_INTENSITY ) ;
}

void notris_draw_level_options( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisInfo* niInfo, struct notrisMenu* nmMenu )
{
  draw_rectangle(  nmMenu->cinotrisMainMenu, 0, 0, nmMenu->srMenuBox.Left, nmMenu->srMenuBox.Top, nmMenu->srMenuBox.Right - 1, nmMenu->srMenuBox.Bottom  ) ;

  draw_string( "LEVEL:", nmMenu->cinotrisMainMenu, nmMenu->srMenuBox.Left + 1, nmMenu->srMenuBox.Top + 3, 0x0004 | 0x0002 | 0x0001 | 0x0008 ) ;

  notris_draw_level( nmMenu->cinotrisMainMenu, niInfo, nmMenu->srMenuBox.Left + 7, nmMenu->srMenuBox.Top + 3 ) ;
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
  notris_draw_logo( csbiInfo, nmMenu->cinotrisMainMenu, csbiInfo->srWindow.Left + 3, csbiInfo->srWindow.Top + 3 ) ;

  draw_rectangle( nmMenu->cinotrisMainMenu, 219, 0x0004| 0x0002 |0x0001 | 0x0008, csbiInfo->srWindow.Left + 1, csbiInfo->srWindow.Top + 1, 40, 2 ) ;
  draw_rectangle( nmMenu->cinotrisMainMenu, 219, 0x0004| 0x0002 |0x0001 | 0x0008, csbiInfo->srWindow.Left + 1, csbiInfo->srWindow.Top + 9, 40, 10 ) ;

  notris_draw_menu_options( csbiInfo, nmMenu ) ;
}

void notris_draw_menu_options( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisMenu* nmMenu )
{
  draw_rectangle( nmMenu->cinotrisMainMenu, 0, 0, nmMenu->srMenuBox.Left, nmMenu->srMenuBox.Top, nmMenu->srMenuBox.Right - 1, nmMenu->srMenuBox.Bottom  ) ;

  draw_rectangle( nmMenu->cinotrisMainMenu, 219, 0x0004| 0x0002 |0x0001 | 0x0008, 
                  nmMenu->srMenuBox.Left - 1, nmMenu->srMenuBox.Top - 1, nmMenu->srMenuBox.Right, nmMenu->srMenuBox.Top ) ;
  draw_rectangle( nmMenu->cinotrisMainMenu, 219, 0x0004| 0x0002 |0x0001 | 0x0008, 
                  nmMenu->srMenuBox.Left - 1, nmMenu->srMenuBox.Bottom, nmMenu->srMenuBox.Right, nmMenu->srMenuBox.Bottom + 1  ) ;
  draw_rectangle( nmMenu->cinotrisMainMenu, 219, 0x0004| 0x0002 |0x0001 | 0x0008, 
                  nmMenu->srMenuBox.Left - 1, nmMenu->srMenuBox.Top, nmMenu->srMenuBox.Left, nmMenu->srMenuBox.Bottom ) ;
  draw_rectangle( nmMenu->cinotrisMainMenu, 219, 0x0004| 0x0002 |0x0001 | 0x0008, 
                  nmMenu->srMenuBox.Right - 1, nmMenu->srMenuBox.Top, nmMenu->srMenuBox.Right, nmMenu->srMenuBox.Bottom ) ;

  draw_string( "PLAY", nmMenu->cinotrisMainMenu, nmMenu->srMenuBox.Left + 2, nmMenu->srMenuBox.Top + 1, 0x0004| 0x0002 |0x0001 | 0x0008 ) ;
  draw_string( "SCORES", nmMenu->cinotrisMainMenu, nmMenu->srMenuBox.Left + 2, nmMenu->srMenuBox.Top + 3, 0x0004| 0x0002 |0x0001 | 0x0008 ) ;
  draw_string( "EXIT", nmMenu->cinotrisMainMenu, nmMenu->srMenuBox.Left + 2, nmMenu->srMenuBox.Top + 5, 0x0004| 0x0002 |0x0001 | 0x0008 ) ;

  nmMenu->cinotrisMainMenu[nmMenu->cursorPosition.Y][nmMenu->cursorPosition.X].Char.AsciiChar = 254 ;
  nmMenu->cinotrisMainMenu[nmMenu->cursorPosition.Y][nmMenu->cursorPosition.X].Attributes = 0x0004| 0x0002 |0x0001 | 0x0008 ;
}

void notris_draw_next( struct notrisInfo* niInfo )
{
  for( int y = niInfo->srNextPieceArea.Top + 1; y <= niInfo->srNextPieceArea.Bottom; y++ )
  {
    for( int x = niInfo->srNextPieceArea.Left; x <= niInfo->srNextPieceArea.Right; x++ )
    {
      niInfo->cinotrisScreenBuffer[y][x].Char.AsciiChar = 0 ;
      niInfo->cinotrisScreenBuffer[y][x].Attributes = 0 ;
    }
  }

  notrisPiece* next = notris_create_piece( niInfo->nextPiece, niInfo, niInfo->srNextPieceArea.Left + 2, niInfo->srNextPieceArea.Top + 2 ) ;

  notris_draw_piece( niInfo, next ) ;

  free( next ) ;
}

void notris_draw_piece( struct notrisInfo* niInfo, struct notrisPiece* piece )
{
  niInfo->cinotrisScreenBuffer[piece->blockOne.Y][piece->blockOne.X].Char.AsciiChar = piece->pieceLook.Char.AsciiChar ;
  niInfo->cinotrisScreenBuffer[piece->blockOne.Y][piece->blockOne.X].Attributes = piece->pieceLook.Attributes ;
  niInfo->bonotrisCollisionArray[piece->blockOne.Y][piece->blockOne.X] = 1 ;

  niInfo->cinotrisScreenBuffer[piece->blockTwo.Y][piece->blockTwo.X].Char.AsciiChar = piece->pieceLook.Char.AsciiChar ;
  niInfo->cinotrisScreenBuffer[piece->blockTwo.Y][piece->blockTwo.X].Attributes = piece->pieceLook.Attributes ;
  niInfo->bonotrisCollisionArray[piece->blockTwo.Y][piece->blockTwo.X] = 1 ;

  niInfo->cinotrisScreenBuffer[piece->blockThree.Y][piece->blockThree.X].Char.AsciiChar = piece->pieceLook.Char.AsciiChar ;
  niInfo->cinotrisScreenBuffer[piece->blockThree.Y][piece->blockThree.X].Attributes = piece->pieceLook.Attributes ;
  niInfo->bonotrisCollisionArray[piece->blockThree.Y][piece->blockThree.X] = 1 ;

  niInfo->cinotrisScreenBuffer[piece->blockFour.Y][piece->blockFour.X].Char.AsciiChar = piece->pieceLook.Char.AsciiChar ;
  niInfo->cinotrisScreenBuffer[piece->blockFour.Y][piece->blockFour.X].Attributes = piece->pieceLook.Attributes ;
  niInfo->bonotrisCollisionArray[piece->blockFour.Y][piece->blockFour.X] = 1 ;
}

void notris_draw_player_tag( struct notrisInfo* niInfo, struct notrisScore* nsScore )
{
  niInfo->cinotrisScreenBuffer[niInfo->srNameEntryArea.Top][niInfo->srNameEntryArea.Left].Char.AsciiChar = nsScore->chPlayerTag[0] ;
  niInfo->cinotrisScreenBuffer[niInfo->srNameEntryArea.Top][niInfo->srNameEntryArea.Left].Attributes = 0x0004 | 0x0002 | 0x0001 | 0x0008 ;
  niInfo->cinotrisScreenBuffer[niInfo->srNameEntryArea.Top][niInfo->srNameEntryArea.Left + 1].Char.AsciiChar = nsScore->chPlayerTag[1] ;
  niInfo->cinotrisScreenBuffer[niInfo->srNameEntryArea.Top][niInfo->srNameEntryArea.Left + 1].Attributes = 0x0004 | 0x0002 | 0x0001 | 0x0008 ;
  niInfo->cinotrisScreenBuffer[niInfo->srNameEntryArea.Top][niInfo->srNameEntryArea.Left + 2].Char.AsciiChar = nsScore->chPlayerTag[2] ;
  niInfo->cinotrisScreenBuffer[niInfo->srNameEntryArea.Top][niInfo->srNameEntryArea.Left + 2].Attributes = 0x0004 | 0x0002 | 0x0001 | 0x0008 ;
}

void notris_draw_score( struct notrisInfo* niInfo )
{
  CHAR score[8] ;

  sprintf( score, "%i", niInfo->notrisScore ) ;

  draw_string( score, niInfo->cinotrisScreenBuffer, niInfo->srScoreArea.Left, niInfo->srScoreArea.Top + 2, FOREGROUND_BLUE | FOREGROUND_INTENSITY ) ;
}

void notris_draw_UI( struct notrisInfo* niInfo )
{
  // Draw PlayFieldArea border
  for( int roof = niInfo->srPlayFieldArea.Left - 1; roof < niInfo->srPlayFieldArea.Right + 1 ; roof++ )
  {
    niInfo->cinotrisScreenBuffer[niInfo->srPlayFieldArea.Top - 1][roof].Char.AsciiChar = 0 ;
    niInfo->cinotrisScreenBuffer[niInfo->srPlayFieldArea.Top - 1][roof].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED ;

    niInfo->cinotrisPauseMenu[niInfo->srPlayFieldArea.Top - 1][roof].Char.AsciiChar = 0 ;
    niInfo->cinotrisPauseMenu[niInfo->srPlayFieldArea.Top - 1][roof].Attributes = BACKGROUND_BLUE | BACKGROUND_INTENSITY ;

    niInfo->bonotrisCollisionArray[niInfo->srPlayFieldArea.Top - 1][roof] = 1 ;                                                                                 
  }

  for( int floor = niInfo->srPlayFieldArea.Left - 1; floor < niInfo->srPlayFieldArea.Right + 1; floor++ )
  {
    niInfo->cinotrisScreenBuffer[niInfo->srPlayFieldArea.Bottom][floor].Char.AsciiChar = 0 ;
    niInfo->cinotrisScreenBuffer[niInfo->srPlayFieldArea.Bottom][floor].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED ;

    niInfo->cinotrisPauseMenu[niInfo->srPlayFieldArea.Bottom][floor].Char.AsciiChar = 0 ;
    niInfo->cinotrisPauseMenu[niInfo->srPlayFieldArea.Bottom][floor].Attributes = BACKGROUND_BLUE | BACKGROUND_INTENSITY ;

    niInfo->bonotrisCollisionArray[niInfo->srPlayFieldArea.Bottom][floor] = 1 ;                                                                                
  }

  for( int leftWall = niInfo->srPlayFieldArea.Top; leftWall < niInfo->srPlayFieldArea.Bottom; leftWall++ )
  {
    niInfo->cinotrisScreenBuffer[leftWall][niInfo->srPlayFieldArea.Left - 1].Char.AsciiChar = 0 ;
    niInfo->cinotrisScreenBuffer[leftWall][niInfo->srPlayFieldArea.Left - 1].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED ;

    niInfo->cinotrisPauseMenu[leftWall][niInfo->srPlayFieldArea.Left - 1].Char.AsciiChar = 0 ;
    niInfo->cinotrisPauseMenu[leftWall][niInfo->srPlayFieldArea.Left - 1].Attributes = BACKGROUND_BLUE | BACKGROUND_INTENSITY ;

    niInfo->bonotrisCollisionArray[leftWall][niInfo->srPlayFieldArea.Left - 1] = 1 ;                                                                                                                                                                          
  }

  for( int rightWall = niInfo->srPlayFieldArea.Top; rightWall < niInfo->srPlayFieldArea.Bottom; rightWall++ )
  {
    niInfo->cinotrisScreenBuffer[rightWall][niInfo->srPlayFieldArea.Right].Char.AsciiChar = 0 ;
    niInfo->cinotrisScreenBuffer[rightWall][niInfo->srPlayFieldArea.Right].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED ;

    niInfo->cinotrisPauseMenu[rightWall][niInfo->srPlayFieldArea.Right].Char.AsciiChar = 0 ;
    niInfo->cinotrisPauseMenu[rightWall][niInfo->srPlayFieldArea.Right].Attributes = BACKGROUND_BLUE | BACKGROUND_INTENSITY ;

    niInfo->bonotrisCollisionArray[rightWall][niInfo->srPlayFieldArea.Right] = 1 ;                                                                                      
  }

  draw_string( "SCORE", niInfo->cinotrisScreenBuffer, niInfo->srScoreArea.Left, niInfo->srScoreArea.Top, FOREGROUND_RED | FOREGROUND_INTENSITY ) ;

  draw_string( "LEVEL", niInfo->cinotrisScreenBuffer, niInfo->srLevelArea.Left, niInfo->srLevelArea.Top, FOREGROUND_RED | FOREGROUND_INTENSITY ) ;

  draw_string( "NEXT", niInfo->cinotrisScreenBuffer, niInfo->srNextPieceArea.Left, niInfo->srNextPieceArea.Top, FOREGROUND_RED | FOREGROUND_INTENSITY ) ;

  draw_string( "PAUSED", niInfo->cinotrisPauseMenu, niInfo->srPlayFieldArea.Left + 2, niInfo->srPlayFieldArea.Top + 3, FOREGROUND_BLUE | FOREGROUND_INTENSITY ) ;

  draw_string( "RESUME", niInfo->cinotrisPauseMenu, niInfo->srPlayFieldArea.Left + 2, niInfo->srPlayFieldArea.Top + 7, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN ) ;

  draw_string( "EXIT", niInfo->cinotrisPauseMenu, niInfo->srPlayFieldArea.Left + 2, niInfo->srPlayFieldArea.Top + 10, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN ) ;
}  

void notris_erase_piece( struct notrisInfo* niInfo, struct notrisPiece* piece )
{
  niInfo->cinotrisScreenBuffer[piece->blockOne.Y][piece->blockOne.X].Char.AsciiChar = 0 ;
  niInfo->cinotrisScreenBuffer[piece->blockOne.Y][piece->blockOne.X].Attributes = 0 ;
  niInfo->bonotrisCollisionArray[piece->blockOne.Y][piece->blockOne.X] = 0 ;

  niInfo->cinotrisScreenBuffer[piece->blockTwo.Y][piece->blockTwo.X].Char.AsciiChar = 0 ;
  niInfo->cinotrisScreenBuffer[piece->blockTwo.Y][piece->blockTwo.X].Attributes = 0 ;
  niInfo->bonotrisCollisionArray[piece->blockTwo.Y][piece->blockTwo.X] = 0 ;

  niInfo->cinotrisScreenBuffer[piece->blockThree.Y][piece->blockThree.X].Char.AsciiChar = 0 ;
  niInfo->cinotrisScreenBuffer[piece->blockThree.Y][piece->blockThree.X].Attributes = 0 ;
  niInfo->bonotrisCollisionArray[piece->blockThree.Y][piece->blockThree.X] = 0 ;

  niInfo->cinotrisScreenBuffer[piece->blockFour.Y][piece->blockFour.X].Char.AsciiChar = 0 ;
  niInfo->cinotrisScreenBuffer[piece->blockFour.Y][piece->blockFour.X].Attributes = 0 ;
  niInfo->bonotrisCollisionArray[piece->blockFour.Y][piece->blockFour.X] = 0 ;
}

/*
 * Counts BOOLs in each row of notrisInfo.boCollisionArray with cellCounter. If all 1, increments rowCounter, thus marking row for deletion, and adds it to 
 * toErase array.
 * Rows are counted from 0y increasing. Thus the row are stored in ascending order in toErase[4].
 * toErase is iterated over. If toErase[n] has value > 0, all row values from y == toErase[n] to 0y  are shifted down, i.e. 
 * niInfo.cinotrisScreenBuffer[y][x] = niInfo.cinotrisScreenBuffer[y - 1][x].
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
      if( niInfo->bonotrisCollisionArray[y][x] )
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
              niInfo->cinotrisScreenBuffer[y][x].Char.AsciiChar = 0 ;
              niInfo->cinotrisScreenBuffer[y][x].Attributes = 0 ;
              niInfo->bonotrisCollisionArray[y][x] = 0 ;
            }
            else
            {
              niInfo->cinotrisScreenBuffer[y][x].Char.AsciiChar = niInfo->cinotrisScreenBuffer[y - 1][x].Char.AsciiChar ;
              niInfo->cinotrisScreenBuffer[y][x].Attributes = niInfo->cinotrisScreenBuffer[y - 1][x].Attributes ;
              niInfo->bonotrisCollisionArray[y][x] = niInfo->bonotrisCollisionArray[y - 1][x] ;
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
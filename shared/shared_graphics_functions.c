#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "console_functions.h"
#include "shared_graphics_functions.h"
#include "../notris/notris_structures.h"

void clear_buffer( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, CHAR_INFO** buffer )
{
  SHORT bufferWidth = csbiInfo->dwSize.X ;
  SHORT bufferHeight = csbiInfo->dwSize.Y ;

  for( int y = 0; y < bufferHeight; y++ )
    {
        for( int x = 0; x < bufferWidth; x++ )
        {
            buffer[y][x].Char.AsciiChar = 0 ;
            buffer[y][x].Attributes = 0 ;
        }
    }
}

void display_buffer( HANDLE *hScreen, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, CHAR_INFO** buffer )
{
    SHORT bufferWidth = csbiInfo->dwSize.X ;
    SHORT bufferHeight = csbiInfo->dwSize.Y ;

    COORD bufferSize = { bufferWidth, 1 } ;
    COORD startPoint = { 0, 0 } ;

    SMALL_RECT srWriteRegion = { .Left = csbiInfo->srWindow.Left, .Top = csbiInfo->srWindow.Top,
                                 .Right = csbiInfo->srWindow.Right, .Bottom = csbiInfo->srWindow.Top + 1 } ;

    CHAR_INFO* ciPointer ;

    SetConsoleActiveScreenBuffer( *hScreen ) ;
    SetConsoleCursorPosition( *hScreen, startPoint ) ;

    for( int j = 0; j < bufferHeight; j++ )
    {
        ciPointer = buffer[j] ;

        if( !WriteConsoleOutputA( *hScreen, ciPointer, bufferSize, startPoint, &srWriteRegion ) )
        {
            report_error( "WriteConsoleOutputA( hScreenBufferOne, buffer, bufferSize, startPoint, &csbiInfo.srWindow )" ) ;
        }

        srWriteRegion.Top++ ;
        srWriteRegion.Bottom++ ;
    }
}

void draw_bubble_writing(  CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, CHAR_INFO** buffer, CHAR* msg, SHORT startX, SHORT startY, WORD attributes )
{
  
}

void draw_integer( DWORD number, CHAR_INFO** buffer, SHORT startX, SHORT startY, WORD attributes )
{
  CHAR* chNumberString ;
  SHORT siDigitCounter = 0 ;

  while( number != 0 )
  {
    number /= 10 ;
    siDigitCounter++ ;
  }

  chNumberString = calloc( siDigitCounter, sizeof( CHAR ) ) ;

  sprintf( chNumberString, "%i", number ) ;

  draw_string( chNumberString, buffer, startX, startY, attributes ) ;

  free( chNumberString ) ;
}

void draw_rectangle( CHAR_INFO** buffer, CHAR asciiValue, WORD asciiAttributes, SHORT startX, SHORT startY, SHORT endX, SHORT endY )
{
    for( int y = startY; y < endY; y++ )
    {
      for( int x = startX; x < endX; x++ )
      {
        buffer[y][x].Char.AsciiChar = asciiValue ;
        buffer[y][x].Attributes = asciiAttributes ;
      }
    }
}

void draw_string( CHAR* str, CHAR_INFO** buffer, SHORT startX, SHORT startY, WORD attributes )
{
  for( int i = 0; i < strlen( str ); i++ )
  {
    buffer[startY][startX + i].Char.AsciiChar = str[i] ;
    buffer[startY][startX + i].Attributes = attributes ;
  }
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "console_functions.h"

void report_error( char *msg )
{
    fprintf( stderr, "Failed: %s\nError Code: %i\n", msg, GetLastError() ) ;
    exit( EXIT_FAILURE ) ;
}

// TODO: Experiment with setup functions which set console to max size or even full screen, then 'draw' game window within that.

int setup_console( HANDLE* phScreenBufferOne, HANDLE* phScreenBufferTwo, HANDLE* phInputBuffer,
                   CONSOLE_SCREEN_BUFFER_INFO* pcsbiInfo, CONSOLE_CURSOR_INFO* pcciInfo, CONSOLE_FONT_INFOEX* pcfiInfo,                                                                 
                   SHORT intended_width, SHORT intended_height ) 
{  
    // I have decided not to position the console window for the user as that would require linking a system library, user32 or gdi32.

    // Has to be equal to, or larger than, the Screen One's screen.
    COORD coIntendedBuffer = { intended_width, intended_height } ;

    // Coordinates used in resizing console window.
    COORD coTempBuff = { intended_width, intended_height } ;

    // Coordinates for top left and bottom right corners of the screen of the Screen One.
    SMALL_RECT srIntendedScreen = { 0, 0, intended_width - 1, intended_height - 1 } ;

    pcfiInfo->cbSize = sizeof( CONSOLE_FONT_INFOEX ) ;

     // Specify cursor as invisible.
    pcciInfo->dwSize = 1 ;
    pcciInfo->bVisible = FALSE ;

    *phInputBuffer = GetStdHandle( STD_INPUT_HANDLE ) ;
    
    // Initialise Screen One.
    *phScreenBufferOne = CreateConsoleScreenBuffer( GENERIC_WRITE | GENERIC_READ, 
                                                    FILE_SHARE_READ | FILE_SHARE_WRITE,
                                                    NULL, CONSOLE_TEXTMODE_BUFFER, NULL ) ;

    *phScreenBufferTwo = CreateConsoleScreenBuffer(  GENERIC_WRITE | GENERIC_READ, 
                                                    FILE_SHARE_READ | FILE_SHARE_WRITE,
                                                    NULL, CONSOLE_TEXTMODE_BUFFER, NULL ) ;

    if( !GetCurrentConsoleFontEx( *phScreenBufferOne, FALSE, pcfiInfo ) )
    {
        report_error( "GetCurrentConsoleFontEx( *phScreenBufferOne, FALSE, pcfiInfo )" ) ;
    }

    // Fill csbi struct.
    if( !GetConsoleScreenBufferInfo( *phScreenBufferOne, pcsbiInfo ) )
    {
        report_error( "GetConsoleScreenBufferInfo( *phScreenBufferOne, &pcsbiInfo )" ) ;
    }

    // Fill cfi struct. Could be used at some point to change font and character size to get more 'pixels'.
    if( !GetCurrentConsoleFontEx( *phScreenBufferOne, FALSE, pcfiInfo ) )
    {
        report_error( "GetCurrentConsoleFontEx( *phScreenBufferOne, FALSE, pcfiInfo )" );
    }

    // Sets coords for a temp buffer large enough to allow screen to be set to intended size. Only needed when run from cmd line.
    if( intended_width > pcsbiInfo->srWindow.Right )
    {
        if( intended_height < pcsbiInfo->srWindow.Bottom )
        {
            coTempBuff.Y = pcsbiInfo->srWindow.Bottom + 1 ;
        }
    }
    else 
    {
        coTempBuff.X = pcsbiInfo->srWindow.Right + 1 ;

        if( intended_height < pcsbiInfo->srWindow.Bottom )
        {
            coTempBuff.Y = pcsbiInfo->srWindow.Bottom + 1 ;
        }
    }

    // IBM Code Page 437. Required for the box drawing characters.
    if( !SetConsoleOutputCP( 437 ) )
    {
        report_error( "SetConsoleOutputCP( 437 )" ) ;
    }

    // First sets a temporary buffer size which is larger than or equal to intended screen/buffer and then shrinks to intended.

    // Setup ScreenBufferOne---------------------------------------------------------------------------------
    if( !SetConsoleScreenBufferSize( *phScreenBufferOne, coTempBuff ) )
    {
        report_error( "SetConsoleScreenBufferSize( *phScreenBufferOne, coTempBuff )" ) ;
    }

    if( !SetConsoleWindowInfo( *phScreenBufferOne, TRUE, &srIntendedScreen ) )
    {
        report_error("Failed: SetConsoleWindowInfo( *phScreenBufferOne, TRUE, &srIntendedScreen )" ) ;
    }

    if( !SetConsoleScreenBufferSize( *phScreenBufferOne, coIntendedBuffer ) )
    {
        report_error( "Failed: SetConsoleScreenBufferSize( *phScreenBufferOne, coIntendedBuffer )" ) ;
    }
    // ------------------------------------------------------------------------------------------------------

    // Setup ScreenBufferTwo---------------------------------------------------------------------------------
    if( !SetConsoleScreenBufferSize( *phScreenBufferTwo, coTempBuff ) )
    {
        report_error( "SetConsoleScreenBufferSize( *phScreenBufferTwo, coTempBuff )" ) ;
    }

    if( !SetConsoleWindowInfo( *phScreenBufferTwo, TRUE, &srIntendedScreen ) )
    {
        report_error("Failed: SetConsoleWindowInfo( *phScreenBufferTwo, TRUE, &srIntendedScreen )" ) ;
    }

    if( !SetConsoleScreenBufferSize( *phScreenBufferTwo, coIntendedBuffer ) )
    {
        report_error( "Failed: SetConsoleScreenBufferSize( *phScreenBufferTwo, coIntendedBuffer )" ) ;
    }
    // ------------------------------------------------------------------------------------------------------

    if( !SetConsoleCursorInfo( *phScreenBufferOne, pcciInfo ) )
    {
        report_error( "Failed: SetConsoleCursorInfo( *phScreenBufferOne, pcciInfo )" ) ;
    }
    
    if( !SetConsoleCursorInfo( *phScreenBufferTwo, pcciInfo ) )
    {
        report_error( "SetConsoleCursorInfo( *phScreenBufferTwo, pcciInfo )" ) ;
    }

    GetConsoleScreenBufferInfo( *phScreenBufferOne, pcsbiInfo ) ;


    return EXIT_SUCCESS ;
}


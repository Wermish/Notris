#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "console_functions.h"

// TODO: Experiment with setup functions which set console to max size or even full screen, then 'draw' game window within that.

int initial_setup( 
                   HANDLE* hMainBuffer, HANDLE* hBackBuffer, HANDLE* hStdInput,
                   CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, CONSOLE_CURSOR_INFO* cciInfo, CONSOLE_FONT_INFOEX* cfiInfo,                                                                 
                   SHORT intended_width, SHORT intended_height 
                 ) 
{  
    // I have decided not to position the console window for the user as that would require linking a system library, user32 or gdi32.

    // Has to be equal to, or larger than, the Main Buffer's screen.
    COORD coIntendedBuffer = { intended_width, intended_height } ;

    // Coordinates used in resizing console window.
    COORD coTempBuff = { intended_width, intended_height } ;

    // Coordinates for top left and bottom right corners of the screen of the Main Buffer.
    SMALL_RECT srIntendedScreen = { 0, 0, intended_width - 1, intended_height - 1 } ;

    cfiInfo->cbSize = sizeof( CONSOLE_FONT_INFOEX ) ;

     // Set cursor to invisible.
    cciInfo->dwSize = 1 ;
    cciInfo->bVisible = FALSE ;

    *hStdInput = GetStdHandle( STD_INPUT_HANDLE ) ;
    
    // Initialise the Main Buffer and the Back Buffer.
    *hMainBuffer = CreateConsoleScreenBuffer( 
                                            GENERIC_WRITE | GENERIC_READ, 
                                            FILE_SHARE_READ | FILE_SHARE_WRITE,
                                            NULL, CONSOLE_TEXTMODE_BUFFER, NULL 
                                            ) ;

    // Fill csbi struct.
    if( !GetConsoleScreenBufferInfo( *hMainBuffer, csbiInfo ) )
    {
        report_error( "GetConsoleScreenBufferInfo( *hMainBuffer, &csbiInfo )" ) ;
    }

    if( !GetCurrentConsoleFontEx( *hMainBuffer, FALSE, cfiInfo ) )
    {
        report_error( "GetCurrentConsoleFontEx( *hMainBuffer, FALSE, cfiInfo )" );
    }

    // Sets coords for a temp buffer large enough to allow screen to be set to intended size. Only needed when run from cmd line.
    if( intended_width > csbiInfo->srWindow.Right )
    {
        if( intended_height < csbiInfo->srWindow.Bottom )
        {
            coTempBuff.Y = csbiInfo->srWindow.Bottom + 1 ;
        }
    }
    else 
    {
        coTempBuff.X = csbiInfo->srWindow.Right + 1 ;

        if( intended_height < csbiInfo->srWindow.Bottom )
        {
            coTempBuff.Y = csbiInfo->srWindow.Bottom + 1 ;
        }
    }

    if( !SetConsoleActiveScreenBuffer( *hMainBuffer ) )
    {
        report_error( "SetConsoleActiveScreenBuffer( *hMainBuffer )" ) ;
    }
    // Set buffer so that intended screen size can be set, then set intended buffer size so no scroll bar shows.
    if( !SetConsoleScreenBufferSize( *hMainBuffer, coTempBuff ) )
    {
        report_error( "SetConsoleScreenBufferSize( *hMainBuffer, coTempBuff )" ) ;
    }

    if( !SetConsoleWindowInfo( *hMainBuffer, TRUE, &srIntendedScreen ) )
    {
        report_error("Failed: SetConsoleWindowInfo( *hMainBuffer, TRUE, &srIntendedScreen )" ) ;
    }

    if( !SetConsoleScreenBufferSize( *hMainBuffer, coIntendedBuffer ) )
    {
        report_error( "Failed: SetConsoleScreenBufferSize( *hMainBuffer, coIntendedBuffer )" ) ;
    }

    if( !SetConsoleWindowInfo( *hMainBuffer, TRUE, &srIntendedScreen ) )
    {
        report_error( "Failed: SetConsoleWindowInfo( *hMainBuffer, TRUE, &srIntendedScreen )" ) ;
    }

    if( !SetConsoleCursorInfo( *hMainBuffer, cciInfo ) )
    {
        report_error( "Failed: SetConsoleCursorInfo( *hMainBuffer, cciInfo )" ) ;
    }
    // Initialise Back Buffer now that Main Buffer and Console Window have been setup.
    *hBackBuffer = CreateConsoleScreenBuffer( 
                                            GENERIC_WRITE | GENERIC_READ, 
                                            FILE_SHARE_READ | FILE_SHARE_WRITE,
                                            NULL, CONSOLE_TEXTMODE_BUFFER, NULL 
                                            ) ;
    

    if( !SetConsoleCursorInfo( *hBackBuffer, cciInfo ) )
    {
        report_error( "SetConsoleCursorInfo( *hBackBuffer, cciInfo )" ) ;
    }
    
    // Required for the box drawing characters.
    if( !SetConsoleOutputCP( 437 ) )
    {
        report_error( "SetConsoleOutputCP( 437 )" ) ;
    }

    return EXIT_SUCCESS ;
}

void report_error( char *msg )
{
    fprintf( stderr, "Failed: %s\nError Code: %i\n", msg, GetLastError() ) ;
    exit( EXIT_FAILURE ) ;
}
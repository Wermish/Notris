#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "console_functions.h"

// TODO: Experiment with setup functions which set console to max size or even full screen, then 'draw' game window within that.

int initial_setup( HANDLE* hMainBuffer, HANDLE* hBackBuffer, SHORT intended_width, SHORT intended_height )
{  
    // I have decided not to position the console window for the user as that would require linking a system library, user32 or gdi32.

    // The initial console screen buffer settings, needed for correct resizing.
    CONSOLE_SCREEN_BUFFER_INFO csbiConsole ;

    // Cursor data, set to invisible.
    CONSOLE_CURSOR_INFO cciMainBuffer = { 1, FALSE } ;

    // Has to be equal to, or larger than, the Main Buffer's screen.
    COORD coIntendedBuffer = { intended_width, intended_height } ;

    // Coordinates used in resizing console window.
    COORD coTempBuff = { intended_width, intended_height } ;

    // Coordinates for top left and bottom right corners of the screen of the Main Buffer.
    SMALL_RECT srIntendedScreen = { 0, 0, intended_width - 1, intended_height - 1 } ;
    
    // Initialise the Main Buffer and the Back Buffer.
    *hMainBuffer = CreateConsoleScreenBuffer( 
                                            GENERIC_WRITE | GENERIC_READ, 
                                            FILE_SHARE_READ | FILE_SHARE_WRITE,
                                            NULL, CONSOLE_TEXTMODE_BUFFER, NULL 
                                            ) ;

    // Fill csbi struct.
    if( !GetConsoleScreenBufferInfo( *hMainBuffer, &csbiConsole ) )
    {
        fprintf( stderr, "Failed: GetConsoleScreenBufferInfo( *hMainBuffer, &csbiConsole )\n" ) ;
        return EXIT_FAILURE ;
    }

    // Sets coords for a temp buffer large enough to allow screen to be set to intended size. Only needed when run from cmd line.
    if( intended_width > csbiConsole.srWindow.Right )
    {
        if( intended_height < csbiConsole.srWindow.Bottom )
        {
            coTempBuff.Y = csbiConsole.srWindow.Bottom + 1 ;
        }
    }
    else 
    {
        coTempBuff.X = csbiConsole.srWindow.Right + 1 ;

        if( intended_height < csbiConsole.srWindow.Bottom )
        {
            coTempBuff.Y = csbiConsole.srWindow.Bottom + 1 ;
        }
    }

    if( !SetConsoleActiveScreenBuffer( *hMainBuffer ) )
    {
        fprintf( stderr, "Failed: SetConsoleActiveScreenBuffer( *hMainBuffer )\n" ) ;
        return EXIT_FAILURE ;
    }
    // Set buffer so that intended screen size can be set, then set intended buffer size so no scroll bar shows.
    if( !SetConsoleScreenBufferSize( *hMainBuffer, coTempBuff ) )
    {
        fprintf( stderr, "Failed: SetConsoleScreenBufferSize( *hMainBuffer, coTempBuff )\n" ) ;
        return EXIT_FAILURE ;
    }

    if( !SetConsoleWindowInfo( *hMainBuffer, TRUE, &srIntendedScreen ) )
    {
        fprintf( stderr, "Failed: SetConsoleWindowInfo( *hMainBuffer, TRUE, &srIntendedScreen )\n" ) ;
        return EXIT_FAILURE ;
    }

    if( !SetConsoleScreenBufferSize( *hMainBuffer, coIntendedBuffer ) )
    {
        fprintf( stderr,"Failed: SetConsoleScreenBufferSize( *hMainBuffer, coIntendedBuffer )\n" ) ;
        return EXIT_FAILURE ;
    }

    if( !SetConsoleWindowInfo( *hMainBuffer, TRUE, &srIntendedScreen ) )
    {
        fprintf( stderr, "Failed: SetConsoleWindowInfo( *hMainBuffer, TRUE, &srIntendedScreen )\n" ) ;
        return EXIT_FAILURE ;
    }

    if( !SetConsoleCursorInfo( *hMainBuffer, &cciMainBuffer ) )
    {
        fprintf( stderr, "Failed: SetConsoleCursorInfo( *hMainBuffer, &cciMainBuffer )\n" ) ;
        return EXIT_FAILURE ;
    }
    // Initialise Back Buffer now that Main Buffer and Console Window have been setup.
    *hBackBuffer = CreateConsoleScreenBuffer( 
                                            GENERIC_WRITE | GENERIC_READ, 
                                            FILE_SHARE_READ | FILE_SHARE_WRITE,
                                            NULL, CONSOLE_TEXTMODE_BUFFER, NULL 
                                            ) ;

    if( !SetConsoleCursorInfo( *hBackBuffer, &cciMainBuffer ) )
    {
        fprintf( stderr, "SetConsoleCursorInfo( *hBackBuffer, &cciMainBuffer )\n" ) ;
        return EXIT_FAILURE ;
    }

    return EXIT_SUCCESS ;
}
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "console_functions.h"

int initial_setup( HANDLE* hMainBuffer, HANDLE* hBackBuffer )
{  
    int intended_width = 100 ;
    int intended_height = 40 ;

    // The initial console screen buffer settings, needed for correct resizing.
    CONSOLE_SCREEN_BUFFER_INFO csbiConsole ;

    // Cursor data, set to invisible.
    CONSOLE_CURSOR_INFO cciMainBuffer = { 1, FALSE } ;

    // Has to be equal to, or larger than, the Main Buffer's screen.
    COORD coIntendedBuffer = { intended_width, intended_height } ;

    // Coordinates used in resizing console window.
    COORD coTempBuff = { coIntendedBuffer.X, coIntendedBuffer.Y } ;

    // Coordinates for top left and bottom right corners of the screen of the Main Buffer.
    SMALL_RECT srIntendedScreen = { 0, 0, coIntendedBuffer.X - 1, coIntendedBuffer.Y - 1 } ;

    // Initialise the Main Buffer and the Back Buffer.
    *hMainBuffer = CreateConsoleScreenBuffer( 
                                            GENERIC_WRITE | GENERIC_READ, 
                                            FILE_SHARE_READ | FILE_SHARE_WRITE,
                                            NULL, CONSOLE_TEXTMODE_BUFFER, NULL 
                                            ) ;

    *hBackBuffer = CreateConsoleScreenBuffer( 
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

    // Sets coords for a temp buffer, which needs to be of a size large enough for both current and intended screen size.
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

    if( !SetConsoleScreenBufferSize( *hMainBuffer, coTempBuff ) )
    {
        fprintf( stderr, "Failed: SetConsoleScreenBufferSize( *hMainBuffer, coTempBuff )\n" ) ;
        return EXIT_FAILURE ;
    }

    if( !SetConsoleScreenBufferSize( *hBackBuffer, coTempBuff ) )
    {
        fprintf( stderr, "Failed: SetConsoleScreenBufferSize( *hBackBuffer, coTempBuff )\n" ) ;
        return EXIT_FAILURE ;
    }

    if( !SetConsoleWindowInfo( *hMainBuffer, TRUE, &srIntendedScreen ) )
    {
        fprintf( stderr, "Failed: SetConsoleWindowInfo( *hMainBuffer, TRUE, &srIntendedScreen )\n" ) ;
        return EXIT_FAILURE ;
    }

    if( !SetConsoleWindowInfo( *hBackBuffer, TRUE, &srIntendedScreen ) )
    {
        fprintf( stderr, "Failed: SetConsoleWindowInfo( *hBackBuffer, TRUE, &srIntendedScreen )\n" ) ;
        return EXIT_FAILURE ;
    }

    if( !SetConsoleScreenBufferSize( *hMainBuffer, coIntendedBuffer ) )
    {
        fprintf( stderr,"Failed: SetConsoleScreenBufferSize( *hMainBuffer, coIntendedBuffer )\n" ) ;
        return EXIT_FAILURE ;
    }

    if( !SetConsoleScreenBufferSize( *hBackBuffer, coIntendedBuffer ) )
    {
        fprintf( stderr,"Failed: SetConsoleScreenBufferSize( *hBackBuffer, coIntendedBuffer )\n" ) ;
        return EXIT_FAILURE ;
    }

    if( !SetConsoleCursorInfo( *hMainBuffer, &cciMainBuffer ) )
    {
        fprintf( stderr, "Failed: SetConsoleCursorInfo( *hMainBuffer, &cciMainBuffer )\n" ) ;
        return EXIT_FAILURE ;
    }

    return EXIT_SUCCESS ;
}
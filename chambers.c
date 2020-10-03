#include <stdio.h>
#include <Windows.h>
//#include "auxillary.h"
//#pragma comment(lib, "user32")

/*
 * Win32 functions return 0 on failure; my functions return 0 on success, as is the NORM. /endOutrage
 */

#define INTENDED_HEIGHT 40 // Current default buffer is 9001 (over 9000!).
#define INTENDED_WIDTH 100  // Current default buffer is 120.

int main()
{   
    // The game screen as seen by the player.
    HANDLE hMainBuffer ;
    // The hidden screen used for double buffering.
    HANDLE hBackBuffer ;

    // The data for the Main Buffer, either the default when created or inherited from the invoking command line. Shared with Back Buffer.
    CONSOLE_SCREEN_BUFFER_INFO csbiMainBuffer ;

    // Cursor data for the Main Buffer. Set to invisible. Shared with Back Buffer
    CONSOLE_CURSOR_INFO cciMainBuffer = { 1, FALSE } ;

    // Has to be equal to, or larger than, the Main Buffer's screen.
    COORD coIntendedBuffer = { INTENDED_WIDTH, INTENDED_HEIGHT } ;

    // Coordinates for top left and bottom right corners of the screen of the Main Buffer.
    SMALL_RECT srIntendedScreen = { 0, 0, coIntendedBuffer.X - 1, coIntendedBuffer.Y - 1 } ;

    COORD coTempBuff = { coIntendedBuffer.X, coIntendedBuffer.Y } ;

    // Initialise the Main Buffer and the Back Buffer.
    hMainBuffer = CreateConsoleScreenBuffer( 
                                            GENERIC_WRITE | GENERIC_READ, 
                                            FILE_SHARE_READ | FILE_SHARE_WRITE,
                                            NULL, CONSOLE_TEXTMODE_BUFFER, NULL 
                                            ) ;

    hBackBuffer = CreateConsoleScreenBuffer( 
                                            GENERIC_WRITE | GENERIC_READ, 
                                            FILE_SHARE_READ | FILE_SHARE_WRITE,
                                            NULL, CONSOLE_TEXTMODE_BUFFER, NULL 
                                            ) ;

    // Fill csbi structs with default values.

    if( !GetConsoleScreenBufferInfo( hMainBuffer, &csbiMainBuffer ) )
    {
        fprintf( stderr, "Failed: GetConsoleScreenBufferInfo( hMainBuffer, &csbiMainBuffer )\n" ) ;
        return 1 ;
    }

    // Fill cci struct with default values.

    if( !GetConsoleCursorInfo( hMainBuffer, &cciMainBuffer ) )
    {
        fprintf( stderr, "Failed: GetConsoleCursorInfo( hMainBuffer, &cciMainBuffer )\n" ) ;
        return 1 ;
    }

    if( !SetConsoleActiveScreenBuffer( hMainBuffer ) )
    {
        fprintf( stderr, "Failed: SetConsoleActiveScreenBuffer( hMainBuffer )\n" ) ;
    }

    /*
     * Checks that buffer large enough to encompass both current and intended screens.
     * 
     */

    if( INTENDED_WIDTH > csbiMainBuffer.srWindow.Right )
    {
        if( INTENDED_HEIGHT < csbiMainBuffer.srWindow.Bottom )
        {
            coTempBuff.Y = csbiMainBuffer.srWindow.Bottom + 1 ;
        }
    }
    else
    {
        coTempBuff.X = csbiMainBuffer.srWindow.Right + 1 ;

        if( INTENDED_HEIGHT < csbiMainBuffer.srWindow.Bottom )
        {
            coTempBuff.Y = csbiMainBuffer.srWindow.Bottom + 1 ;
        }
    }

    SetConsoleScreenBufferSize( hMainBuffer, coTempBuff ) ;
    SetConsoleWindowInfo( hMainBuffer, TRUE, &srIntendedScreen ) ;
    SetConsoleScreenBufferSize( hMainBuffer, coIntendedBuffer ) ;

    getchar() ;

    return 0;
}
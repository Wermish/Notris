#include <stdio.h>
#include <Windows.h>

/*
 * Win32 functions return 0 on failure; my functions return 0 on success, as is the NORM. /endOutrage
 */

#define INTENDED_HEIGHT 40 // Current default buffer is 9001 (over 9000!).
#define INTENDED_WIDTH 100  // Current default buffer is 120.

int main()
{   
    // The game screen and the double buffer.
    HANDLE hMainBuffer, hBackBuffer ;

    // The initial console screen buffer settings, needed for correct resizing.
    CONSOLE_SCREEN_BUFFER_INFO csbiConsole ;

    // Cursor data for the Main Buffer. Set to invisible. Shared with Back Buffer
    CONSOLE_CURSOR_INFO cciMainBuffer = { 1, FALSE } ;

    // Has to be equal to, or larger than, the Main Buffer's screen.
    COORD coIntendedBuffer = { INTENDED_WIDTH, INTENDED_HEIGHT } ;

    // Coordinates used in resizing console window.
    COORD coTempBuff = { coIntendedBuffer.X, coIntendedBuffer.Y } ;

    // Coordinates for top left and bottom right corners of the screen of the Main Buffer.
    SMALL_RECT srIntendedScreen = { 0, 0, coIntendedBuffer.X - 1, coIntendedBuffer.Y - 1 } ;

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

    // Fill csbi structs.
    if( !GetConsoleScreenBufferInfo( hMainBuffer, &csbiConsole ) )
    {
        fprintf( stderr, "Failed: GetConsoleScreenBufferInfo( hMainBuffer, &csbiConsole )\n" ) ;
        return 1 ;
    }

    // Fill cci struct.
    if( !GetConsoleCursorInfo( hMainBuffer, &cciMainBuffer ) )
    {
        fprintf( stderr, "Failed: GetConsoleCursorInfo( hMainBuffer, &cciMainBuffer )\n" ) ;
        return 1 ;
    }

    // Set the Main Buffer as the game screen.
    if( !SetConsoleActiveScreenBuffer( hMainBuffer ) )
    {
        fprintf( stderr, "Failed: SetConsoleActiveScreenBuffer( hMainBuffer )\n" ) ;
        return 1 ;
    }

    /*
     * Checks that the buffer is large enough to encompass both current and intended console window.
     *  
     */

    if( INTENDED_WIDTH > csbiConsole.srWindow.Right )
    {
        if( INTENDED_HEIGHT < csbiConsole.srWindow.Bottom )
        {
            coTempBuff.Y = csbiConsole.srWindow.Bottom + 1 ;
        }
    }
    else
    {
        coTempBuff.X = csbiConsole.srWindow.Right + 1 ;

        if( INTENDED_HEIGHT < csbiConsole.srWindow.Bottom )
        {
            coTempBuff.Y = csbiConsole.srWindow.Bottom + 1 ;
        }
    }

    if( !SetConsoleScreenBufferSize( hMainBuffer, coTempBuff ) )
    {
        fprintf( stderr, "Failed: SetConsoleScreenBufferSize( hMainBuffer, coTempBuff )\n" ) ;
        return 1 ;
    }

    if( !SetConsoleWindowInfo( hMainBuffer, TRUE, &srIntendedScreen ) )
    {
        fprintf( stderr, "Failed: SetConsoleWindowInfo( hMainBuffer, TRUE, &srIntendedScreen )\n" ) ;
        return 1 ;
    }

    if( !SetConsoleScreenBufferSize( hMainBuffer, coIntendedBuffer ) )
    {
        fprintf( stderr,"Failed: SetConsoleScreenBufferSize( hMainBuffer, coIntendedBuffer )\n" ) ;
        return 1 ;
    }

    getchar() ;

    CloseHandle( hMainBuffer ) ;
    CloseHandle( hBackBuffer ) ;

    return 0;
}
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

int setup_console( HANDLE* hScreenBuffer, HANDLE* hInputBuffer,
                   CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, CONSOLE_CURSOR_INFO* cciInfo, CONSOLE_FONT_INFOEX* cfiInfo,                                                                 
                   SHORT intended_width, SHORT intended_height ) 
{  
    // Has to be equal to, or larger than, the Screen One's screen.
    COORD coIntendedBuffer = { intended_width, intended_height } ;

    // Coordinates used in resizing console window.
    COORD coTempBuff = { intended_width, intended_height } ;

    // Coordinates for top left and bottom right corners of the screen of the Screen One.
    SMALL_RECT srIntendedScreen = { 0, 0, intended_width - 1, intended_height - 1 } ;

    cfiInfo->cbSize = sizeof( CONSOLE_FONT_INFOEX ) ;

     // Specify cursor as invisible.
    cciInfo->dwSize = 1 ;
    cciInfo->bVisible = FALSE ;

    *hInputBuffer = GetStdHandle( STD_INPUT_HANDLE ) ;
    
    // Initialise Screen One.
    *hScreenBuffer = CreateConsoleScreenBuffer( GENERIC_WRITE | GENERIC_READ, 
                                                FILE_SHARE_READ | FILE_SHARE_WRITE,
                                                NULL, CONSOLE_TEXTMODE_BUFFER, NULL ) ;

    // Fill cfiex struct.
    if( !GetCurrentConsoleFontEx( *hScreenBuffer, TRUE, cfiInfo ) )
    {
        report_error( "GetCurrentConsoleFontEx( *hScreenBuffer, TRUE, cfiInfo )" ) ;
    }

    // Fill csbi struct.
    if( !GetConsoleScreenBufferInfo( *hScreenBuffer, csbiInfo ) )
    {
        report_error( "GetConsoleScreenBufferInfo( *hScreenBuffer, &csbiInfo )" ) ;
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
    
    // Terminal raster font is boxier and makes for better 'pixels' when using IBM 437 characters.
    wcscpy( cfiInfo->FaceName, L"Terminal" );
    cfiInfo->dwFontSize.X = 16 ;
    cfiInfo->dwFontSize.Y = 16 ;
    cfiInfo->FontFamily = 0x30 ; // Supposedly should be 0x30
    cfiInfo->FontWeight = 0 ;
    
    // First sets a temporary buffer size which is larger than or equal to intended screen/buffer and then shrinks to intended.

    // Setup ScreenBuffer------------------------------------------------------------------------------------
    if( !SetConsoleScreenBufferSize( *hScreenBuffer, coTempBuff ) )
    {
        report_error( "SetConsoleScreenBufferSize( *hScreenBuffer, coTempBuff )" ) ;
    }

    if( !SetConsoleWindowInfo( *hScreenBuffer, TRUE, &srIntendedScreen ) )
    {
        report_error("SetConsoleWindowInfo( *hScreenBuffer, TRUE, &srIntendedScreen )" ) ;
    }

    if( !SetConsoleScreenBufferSize( *hScreenBuffer, coIntendedBuffer ) )
    {
        report_error( "SetConsoleScreenBufferSize( *hScreenBuffer, coIntendedBuffer )" ) ;
    }

    if( !SetConsoleCursorInfo( *hScreenBuffer, cciInfo ) )
    {
        report_error( "SetConsoleCursorInfo( *hScreenBuffer, cciInfo )" ) ;
    }

    if( !SetCurrentConsoleFontEx( *hScreenBuffer, TRUE, cfiInfo ) )
    {
        report_error( "SetCurrentConsoleFontEx( *hScreenBuffer, TRUE, cfiInfo )" ) ;
    }
    // ------------------------------------------------------------------------------------------------------

    // IBM Code Page 437. Required for the box drawing characters.
    if( !SetConsoleOutputCP( 437 ) )
    {
        report_error( "SetConsoleOutputCP( 437 )" ) ;
    }

    if( !SetConsoleTitleA( "CHAMBERS" ) )
    {
        report_error( "SetConsoleTitle( \"CHAMBERS\" )" ) ;
    }

    // Update csfiInfo struct with new values.
    if( !GetCurrentConsoleFontEx( *hScreenBuffer, TRUE, cfiInfo ) )
    {
        report_error( "GetCurrentConsoleFontEx( *hScreenBuffer, TRUE, cfiInfo )" ) ;
    }

    // Update csbiInfo struct with new values.
    if( !GetConsoleScreenBufferInfo( *hScreenBuffer, csbiInfo ) )
    {
        report_error( "GetConsoleScreenBufferInfo( *hScreenBuffer, csbiInfo )" ) ;
    }

    if( !SetConsoleActiveScreenBuffer( *hScreenBuffer ) )
    {
        report_error( "SetConsoleActiveScreenBuffer( *hScreenBuffer )" ) ;
    }

    return EXIT_SUCCESS ;
}


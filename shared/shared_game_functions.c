#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "shared_game_functions.h"

BOOL act_on_input( HANDLE* hInputBuffer )
{
    DWORD numberOfEvents = 0 ;
    DWORD numberOfEventsRead = 0 ;

    GetNumberOfConsoleInputEvents( *hInputBuffer, &numberOfEvents ) ;

    if( numberOfEvents )
    {
        INPUT_RECORD* inputRecordArray = malloc( sizeof( INPUT_RECORD ) * numberOfEvents ) ;

        ReadConsoleInput( *hInputBuffer, inputRecordArray, numberOfEvents, &numberOfEventsRead ) ;

        for( int i = 0; i < numberOfEventsRead; i++ )
        {
            if( inputRecordArray[i].EventType == KEY_EVENT )
            {
                if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE )
                {
                    if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                    {
                        return 1 ;
                    }
                }
            }
        }
    }

    return 0 ;
}

/*
 * For use with qsort() to order array max to min.
 */

int comparator_descending( const void *a, const void *b )
{
    int c = ( *( int* )b - *( int* )a ) ;

    return c ;
}

/*
 * Use 'srand( time( 0 ) )' at start of main to seed.
 */

int random_number_in_range( int minimum, int maximum )
{
    int result = rand() % (( maximum + 1 ) - minimum) + minimum ;

    return result ;
}
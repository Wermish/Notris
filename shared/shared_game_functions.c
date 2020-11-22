#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "shared_game_functions.h"

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
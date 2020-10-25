#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "shared_game_functions.h"

/*
 * Use 'srand( time( 0 ) )' at start of main to seed.
 */

int generate_random_number( int minimum, int maximum )
{
    int result = rand() % (( maximum + 1 ) - minimum) + minimum ;

    return result ;
}
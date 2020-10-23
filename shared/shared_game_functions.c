#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "shared_game_functions.h"

int generate_random_number( int minimum, int maximum )
{
    srand( time( 0 ) ) ;
    
    int result = rand() % (( maximum + 1 ) - minimum) + minimum ;

    return result ;
}
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "console_functions.h"

HANDLE hMainBuffer ;
HANDLE hBackBuffer ;

int main( void )
{   
    initial_setup( &hMainBuffer, &hBackBuffer ) ;

    getchar() ;

    CloseHandle( hMainBuffer ) ;
    CloseHandle( hBackBuffer ) ;

    return EXIT_SUCCESS ;

}
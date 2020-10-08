#ifndef CONSOLE_FUNCTIONS_H
#define CONSOLE_FUNCTIONS_H

int initial_setup( HANDLE* hMainBuffer, HANDLE* hBackBuffer, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, SHORT intended_width, SHORT intended_height ) ;

void report_error( char *msg ) ;

#endif /* CONSOLE_FUNCTIONS_H */
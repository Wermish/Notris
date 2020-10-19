#ifndef CONSOLE_FUNCTIONS_H
#define CONSOLE_FUNCTIONS_H

int generate_random_number( int minimum, int maximum ) ;

void report_error( char *msg ) ;

int setup_console( HANDLE* phScreenBufferOne, HANDLE* phScreenBufferTwo, HANDLE* phInputBuffer,
                   CONSOLE_SCREEN_BUFFER_INFO* pcsbiInfo, CONSOLE_CURSOR_INFO* pcciInfo, CONSOLE_FONT_INFOEX* pcfiInfo,                                                                 
                   SHORT intended_width, SHORT intended_height ) ;
#endif /* CONSOLE_FUNCTIONS_H */
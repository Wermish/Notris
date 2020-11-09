#ifndef CONSOLE_FUNCTIONS_H
#define CONSOLE_FUNCTIONS_H

void report_error( char *msg ) ;

int setup_console( HANDLE* hScreenBuffer, HANDLE* hInputBuffer,
                   CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, CONSOLE_CURSOR_INFO* cciInfo, CONSOLE_FONT_INFOEX* cfiInfo,                                                                 
                   SHORT intended_width, SHORT intended_height ) ;
                   
#endif /* CONSOLE_FUNCTIONS_H */
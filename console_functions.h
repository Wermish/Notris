#ifndef CONSOLE_FUNCTIONS_H
#define CONSOLE_FUNCTIONS_H

int initial_setup( 
                   HANDLE* hMainBuffer, HANDLE* hBackBuffer, HANDLE* hStdInput,
                   CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, CONSOLE_CURSOR_INFO* cciInfo, CONSOLE_FONT_INFOEX* cfiInfo,                                                                 
                   SHORT intended_width, SHORT intended_height 
                 ) ;

void report_error( char *msg ) ;

#endif /* CONSOLE_FUNCTIONS_H */
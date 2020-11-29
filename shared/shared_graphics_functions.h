#ifndef SHARED_GRAPHICS_FUNCTIONS_H
#define SHARED_GRAPHICS_FUNCTIONS_H

void clear_buffer( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, CHAR_INFO** buffer ) ;

void display_buffer( HANDLE *hScreen, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, CHAR_INFO** buffer ) ;

void draw_rectangle( HANDLE* phScreenBuffer, 
                    CHAR asciiValue, WORD asciiAttributes, 
                    SHORT startX, SHORT startY, SHORT endX, SHORT endY ) ;

void draw_string( CHAR* str, CHAR_INFO** buffer, SHORT startX, SHORT startY, WORD attributes ) ;

#endif /* SHARED_GRAPHICS_FUNCTIONS_H */
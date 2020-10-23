#ifndef SHARED_GRAPHICS_FUNCTIONS_H
#define SHARED_GRAPHICS_FUNCTIONS_H

void clear_screen_buffer( HANDLE* phScreenBuffer, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo ) ;

void draw_rectangle( HANDLE* phScreenBuffer, 
                    CHAR asciiValue, WORD asciiAttributes, 
                    SHORT startX, SHORT startY, SHORT endX, SHORT endY ) ;

#endif /* SHARED_GRAPHICS_FUNCTIONS_H */
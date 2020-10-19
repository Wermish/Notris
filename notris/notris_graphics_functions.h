#ifndef NOTRIS_GRAPHICS_FUNCTIONS_H
#define NOTRIS_GRAPHICS_FUNCTIONS_H

void clear_screen_buffer( HANDLE* phScreenBuffer, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo ) ;

void draw_notris_piece( HANDLE* phScreenBuffer, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisPiece* piece ) ;

void draw_notris_play_field( HANDLE* phScreenBuffer, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisPlayFieldInfo* npfiInfo ) ;
 
void draw_rectangle( HANDLE* phScreenBuffer, 
                    CHAR asciiValue, WORD asciiAttributes, 
                    SHORT startX, SHORT startY, SHORT endX, SHORT endY ) ;

void erase_notris_piece( HANDLE* phScreenBuffer, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisPiece* piece ) ;

#endif /* NOTRIS_GRAPHICS_FUNCTIONS_H */
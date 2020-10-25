#ifndef NOTRIS_GRAPHICS_FUNCTIONS_H
#define NOTRIS_GRAPHICS_FUNCTIONS_H

void draw_notris_piece( HANDLE* phScreenBuffer, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisPiece* piece ) ;

void draw_notris_play_field( HANDLE* phScreenBuffer, struct notrisPlayFieldInfo* npfiInfo ) ;

void erase_notris_piece( HANDLE* phScreenBuffer, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisPiece* piece ) ;

#endif /* NOTRIS_GRAPHICS_FUNCTIONS_H */
#ifndef NOTRIS_GRAPHICS_FUNCTIONS_H
#define NOTRIS_GRAPHICS_FUNCTIONS_H

void notris_clear_play_field( HANDLE* hScreenBuffer, struct notrisPlayFieldInfo* npfiInfo ) ;

void notris_draw_piece( HANDLE* hScreenBuffer, struct notrisPiece* piece ) ;

void notris_draw_play_field( HANDLE* hScreenBuffer, struct notrisPlayFieldInfo* npfiInfo ) ;

void notris_draw_UI( HANDLE* hScreenBuffer, struct notrisPlayFieldInfo* npfiInfo ) ;

void notris_erase_piece( HANDLE* hScreenBuffer, struct notrisPiece* piece ) ;

#endif /* NOTRIS_GRAPHICS_FUNCTIONS_H */
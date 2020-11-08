#ifndef NOTRIS_GRAPHICS_FUNCTIONS_H
#define NOTRIS_GRAPHICS_FUNCTIONS_H

void notris_clear_play_field( HANDLE* hScreenBuffer, struct notrisInfo* npfiInfo ) ;

void notris_draw_piece( struct notrisInfo* niInfo, struct notrisPiece* piece ) ;

void notris_draw_UI( struct notrisInfo* npfiInfo ) ;

void notris_erase_piece( struct notrisInfo* niInfo, struct notrisPiece* piece ) ;

#endif /* NOTRIS_GRAPHICS_FUNCTIONS_H */
#ifndef NOTRIS_GRAPHICS_FUNCTIONS_H
#define NOTRIS_GRAPHICS_FUNCTIONS_H

void notris_clear_play_field( HANDLE* hScreenBuffer, struct notrisInfo* niInfo ) ;

void notris_draw_level( struct notrisInfo* niInfo ) ;

void notris_draw_piece( struct notrisInfo* niInfo, struct notrisPiece* piece ) ;

void notris_draw_next( struct notrisInfo* niInfo  ) ;

void notris_draw_score( struct notrisInfo* niInfo ) ;

void notris_draw_UI( struct notrisInfo* npfiInfo ) ;

void notris_erase_piece( struct notrisInfo* niInfo, struct notrisPiece* piece ) ;

void notris_erase_row( struct notrisInfo* niInfo ) ;

#endif /* NOTRIS_GRAPHICS_FUNCTIONS_H */
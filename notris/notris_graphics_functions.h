#ifndef notris_GRAPHICS_FUNCTIONS_H
#define notris_GRAPHICS_FUNCTIONS_H

void notris_clear_play_field( CHAR_INFO** buffer, struct notrisInfo* niInfo ) ;

void notris_draw_game_over( struct notrisInfo* niInfo ) ;

void notris_draw_top_scores( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisMenu* nmMenu, FILE** fTopScores ) ;

void notris_draw_level( CHAR_INFO** buffer, struct notrisInfo* niInfo, SHORT startX, SHORT startY ) ;

void notris_draw_level_options( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisInfo* niInfo, struct notrisMenu* nmMenu ) ;

void notris_draw_logo( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, CHAR_INFO** buffer, SHORT startX, SHORT startY ) ;

void notris_draw_menu( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisMenu* nmMenu ) ;

void notris_draw_menu_options( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisMenu* nmMenu ) ;

void notris_draw_next( struct notrisInfo* niInfo  ) ;

void notris_draw_piece( struct notrisInfo* niInfo, struct notrisPiece* piece ) ;

void notris_draw_player_tag( struct notrisInfo* niInfo, struct notrisScore* nsScore ) ;

void notris_draw_score( struct notrisInfo* niInfo ) ;

void notris_draw_UI( struct notrisInfo* npfiInfo ) ;

void notris_erase_piece( struct notrisInfo* niInfo, struct notrisPiece* piece ) ;

void notris_erase_row( struct notrisInfo* niInfo ) ;

#endif /* notris_GRAPHICS_FUNCTIONS_H */
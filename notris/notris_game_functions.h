#ifndef NOTRIS_GAME_FUNCTIONS_H
#define NOTRIS_GAME_FUNCTIONS_H

BOOL notris_check_x_plus_collision( struct notrisInfo* niInfo, struct notrisPiece* piece ) ;

BOOL notris_check_x_minus_collision( struct notrisInfo* niInfo, struct notrisPiece* piece ) ;

BOOL notris_check_y_collision( struct notrisInfo* niInfo, struct notrisPiece* piece ) ;

struct notrisPiece* notris_create_piece( enum notrisPieceShape pieceShape, struct notrisInfo* npfiInfo ) ;

BOOL notris_move_piece( HANDLE* phInputBuffer, struct notrisInfo* npfiInfo, struct notrisPiece* piece ) ;

BOOL notris_piece_falling( DWORD* counter, struct notrisInfo* niInfo, struct notrisPiece* piece ) ;

void notris_rotate_piece_anticlockwise( struct notrisPiece* piece ) ;

void notris_rotate_piece_clockwise( struct notrisPiece* piece ) ;

void notris_set_boundaries( struct notrisInfo* niInfo ) ;

void notris_setup( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisInfo* npfiInfo ) ;

void play_notris( HANDLE* hScreenBuffer, HANDLE* hInputBuffer, 
                  CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisInfo* npfiInfo ) ;

#endif /* NOTRIS_GAME_FUNCTIONS_H */
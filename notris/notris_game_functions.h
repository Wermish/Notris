#ifndef NOTRIS_GAME_FUNCTIONS_H
#define NOTRIS_GAME_FUNCTIONS_H

BOOL notris_check_axis_collision( struct notrisInfo* niInfo, struct notrisPiece* npPiece, SHORT offset, CHAR axis ) ;

BOOL notris_check_move_collision( struct notrisInfo* niInfo, struct notrisPiece* npPiece, WORD wVirtualKeyCode ) ;

void notris_create_bag( struct notrisInfo* niInfo ) ;

struct notrisPiece* notris_create_piece( enum notrisPieceShape npsPieceShape, struct notrisInfo* npfiInfo, SHORT sLeadBlockX, SHORT sLeadBlockY ) ;

BOOL notris_move_piece( HANDLE* hInputBuffer, struct notrisInfo* niInfo, struct notrisPiece* npPiece ) ;

BOOL notris_piece_falling( DWORD* dwCounter, struct notrisInfo* niInfo, struct notrisPiece* npPiece ) ;

void notris_rotate_piece_anticlockwise( struct notrisPiece* npPiece ) ;

void notris_rotate_piece_clockwise( struct notrisPiece* npPiece ) ;

void notris_score_and_level( struct notrisInfo* niInfo ) ;

void notris_set_boundaries( struct notrisInfo* niInfo ) ;

void notris_setup( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisInfo* npfiInfo ) ;

void play_notris( HANDLE* hScreenBuffer, HANDLE* hInputBuffer, 
                  CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisInfo* npfiInfo ) ;

#endif /* NOTRIS_GAME_FUNCTIONS_H */
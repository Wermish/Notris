#ifndef NOTRIS_GAME_FUNCTIONS_H
#define NOTRIS_GAME_FUNCTIONS_H

struct notrisPiece* generate_notris_piece( enum notrisPieceShape pieceShape, struct notrisPlayFieldInfo* npfiInfo ) ;

void move_notris_piece( HANDLE* hInputBuffer, struct notrisPiece* piece ) ;

void rotate_notris_piece( struct notrisPiece* piece ) ;

void setup_notris( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisPlayFieldInfo* npfiInfo ) ;

#endif /* NOTRIS_GAME_FUNCTIONS_H */
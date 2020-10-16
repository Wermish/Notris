#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

struct notrisPiece* generate_notris_piece( int notrisPieceShape, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo ) ;

void move_notris_piece( HANDLE* phInputBuffer, struct notrisPiece* piece ) ;

#endif /* GAME_FUNCTIONS_H */
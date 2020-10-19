#ifndef NOTRIS_GAME_FUNCTIONS_H
#define NOTRIS_GAME_FUNCTIONS_H

struct notrisPiece* generate_notris_piece( int notrisPieceShape, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo ) ;

void move_notris_piece( HANDLE* phInputBuffer, struct notrisPiece* piece ) ;

void rotate_notris_piece( struct notrisPiece* piece ) ;

void setup_notris( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo ) ;

#endif /* NOTRIS_GAME_FUNCTIONS_H */
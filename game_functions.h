#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

struct notrisPiece* generate_notris_piece( int pt ) ;

void move_player( HANDLE* phInputBuffer, COORD* playerLocation ) ;

void move_notris_piece( HANDLE* phInputBuffer, struct notrisPiece* piece ) ;

#endif /* GAME_FUNCTIONS_H */
#ifndef GAME_ENTITIES_H
#define GAME_ENTITIES_H

// Idea is to make the whole Notris play area a malloc'd array of CHAR_INFO and write characters to it each frame.
typedef struct notrisPlayFieldInfo
{
    CHAR_INFO* playFieldBuffer ;
    SMALL_RECT playFieldSize ;
} notrisPlayFieldInfo ;

typedef struct notrisPiece
{
    // Piece type 1 - 7. Each coord is one of the blocks which makes up a piece.
    CHAR pieceShape ;
    COORD blockOne ;
    COORD blockTwo ;
    COORD blockThree ;
    COORD blockFour ; 
    CHAR_INFO pieceLook ;
} notrisPiece ;

#endif /* GAME_ENTITIES_H */
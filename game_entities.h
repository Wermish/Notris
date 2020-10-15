#ifndef GAME_ENTITIES_H
#define GAME_ENTITIES_H

typedef struct
{
    SMALL_RECT playField ;
} gameDisplayInfo ;

typedef struct notrisPiece
{
    // Piece type 1 - 7. Each coord is one of the blocks which makes up a piece.
    CHAR pieceType ;
    COORD partOne ;
    COORD partTwo ;
    COORD partThree ;
    COORD partFour ; 
    CHAR_INFO pieceLook ;
} notrisPiece ;

typedef struct
{
    CHAR icon ;
    CHAR empty ;
    COORD location ;
} player ; 

#endif /* GAME_ENTITIES_H */
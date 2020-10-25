#ifndef NOTRIS_STRUCTURES_H
#define NOTRIS_STRUCTURES_H

typedef enum notrisPieceShape{
    square = 1,
    line = 2,
    lshape = 3,
    mirroredlshape = 4,
    zed = 5,
    mirroredzed = 6,
    hat = 7
} notrisPieceShape ;

typedef struct notrisPlayFieldInfo
{
    SMALL_RECT playFieldArea ;
    DWORD notrisScore ;
    enum notrisPieceShape nextPiece ;
} notrisPlayFieldInfo ;

typedef struct notrisPiece
{
    enum notrisPieceShape pieceShape ;
    // Current rotation. Different pieces have different number of rotations.
    CHAR piecePhase ;
    // Each coord is one of the blocks which makes up a piece.
    COORD blockOne ;
    COORD blockTwo ;
    COORD blockThree ;
    COORD blockFour ; 
    CHAR_INFO pieceLook ;
} notrisPiece ;

#endif /* NOTRIS_STRUCTURES_H */
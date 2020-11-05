#ifndef NOTRIS_STRUCTURES_H
#define NOTRIS_STRUCTURES_H

typedef enum notrisPiecePhase
{
    phasezero = 0,
    phaseone = 1,
    phasetwo = 2,
    phasethree = 3 
} 
notrisPiecePhase ;

typedef enum notrisPieceShape
{
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
    //struct notrisPiece** fallenPieces ; // Array of pointers to pieces which have fallen. Used for drawing stacked pieces.
    enum notrisPieceShape nextPiece ;
    // Dimensions of the area in which blocks fall.
    SMALL_RECT playFieldArea ;
    DWORD notrisScore ;

} notrisPlayFieldInfo ;

typedef struct notrisPiece
{
    enum notrisPieceShape pieceShape ;
    // Current rotation. Different pieces have different number of rotations.
    enum notrisPiecePhase piecePhase ;
    // Each coord is one of the blocks which makes up a piece.
    COORD blockOne ;
    COORD blockTwo ;
    COORD blockThree ;
    COORD blockFour ;
    // Colour and graphic.
    CHAR_INFO pieceLook ;

} notrisPiece ;

#endif /* NOTRIS_STRUCTURES_H */
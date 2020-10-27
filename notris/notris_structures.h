#ifndef NOTRIS_STRUCTURES_H
#define NOTRIS_STRUCTURES_H

typedef union notrisPieceBoundary
{   
    COORD blockBoundary ;
    SMALL_RECT segmentBoundary ;
} notrisPieceBoundary ;

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
    // Array of pointers to pieces which have fallen. Used for drawing stacked pieces.
    struct notrisPiece** fallenPieces ;
    enum notrisPieceShape nextPiece ;
    SMALL_RECT playFieldArea ;
    COORD* playAreaFloor ;
    DWORD notrisScore ;
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
    // Used for collision detection.
    union notrisPieceBoundary leftmost ;
    union notrisPieceBoundary rightmost ;
    union notrisPieceBoundary upmost ;
    union notrisPieceBoundary downmost ;
    // Colour and graphic.
    CHAR_INFO pieceLook ;
} notrisPiece ;

#endif /* NOTRIS_STRUCTURES_H */
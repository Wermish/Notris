#ifndef NOTRIS_STRUCTURES_H
#define NOTRIS_STRUCTURES_H

typedef union notrisPieceBoundary
{   
    COORD blockBoundary ;
    SMALL_RECT segmentBoundary ;
    
} notrisPieceBoundary ;

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

typedef struct playFieldAreaCell
{
    COORD cellCoord ;
    CHAR_INFO cellData ;
    BOOL deadOrAlive ;

} playFieldAreaCell ;

typedef struct notrisPlayFieldInfo
{   
    //struct notrisPiece** fallenPieces ; // Array of pointers to pieces which have fallen. Used for drawing stacked pieces.
    enum notrisPieceShape nextPiece ;
    // Dimensions of the area in which blocks fall.
    SMALL_RECT playFieldArea ;
    // Holds info for each cell in the play area, which is used by the screen buffer.
    struct playFieldAreaCell** playFieldBuffer ;
    // Used for collision detection.
    COORD* playFieldFloor ;
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
    // Used for collision detection.
    union notrisPieceBoundary leftmost ;
    union notrisPieceBoundary rightmost ;
    union notrisPieceBoundary upmost ;
    union notrisPieceBoundary downmost ;
    // Colour and graphic.
    CHAR_INFO pieceLook ;

} notrisPiece ;

#endif /* NOTRIS_STRUCTURES_H */
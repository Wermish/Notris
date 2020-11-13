#ifndef NOTRIS_STRUCTURES_H
#define NOTRIS_STRUCTURES_H

typedef enum notrisPiecePhase
{
    phasezero = 0,
    phaseone = 1,
    phasetwo = 2,
    phasethree = 3 
    
} notrisPiecePhase ;

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

/*
 * ciNotrisScreenBuffer: a matrix of CHAR_INFOs, each row being a horizontal segment of the screen. The screen updates by writing a row at a time.
 * boNotrisWriteArray: an array of BOOLs. Each item represents the state of a row of ciNotrisScreenBuffer. If 1, the row has been updated and needs to be drawn.
 * boNotrisCollisionArray: a matrix of BOOLs, each item representing the state of an item from ciNotrisScreenBuffer. 1 means the cell is occupied, or drawn.
 * srPlayFieldArea: a SMALL_RECT, the dimensions of the area into which the blocks fall and the action takes place.
 * dwNotrisScore: DWORD returned from play_notris() once the game is over.
 * npsNextPiece: an enum which determines the next piece to fall, displayed to the player ahead of time via the UI.
 */

typedef struct notrisInfo
{   
    CHAR_INFO** ciNotrisScreenBuffer ;
    BOOL* boNotrisWriteArray ;
    BOOL** boNotrisCollisionArray ;
    SMALL_RECT srPlayFieldArea ;
    DWORD notrisScore ;
    enum notrisPieceShape nextPiece ;
    
} notrisInfo ;

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
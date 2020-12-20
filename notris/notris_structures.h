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

typedef enum notrisLevel
{
    easiest = 1,
    easier = 2,
    easy = 3,
    normal = 4,
    hard = 5,
    harder = 6,
    hardest = 7

} notrisLevel ;

typedef enum menuOption
{

    play = 1,
    scores = 2,
    quit = 3

} menuOption ;

/*
 * ciNotrisScreenBuffer: a matrix of CHAR_INFOs, each row being a horizontal segment of the screen. The screen updates by writing a row at a time.
 * ciNotrisPauseMenu: as above but displays the pause menu during play when the pause key is pressed.
 * boNotrisWriteArray: an array of BOOLs. Each item represents the state of a row of ciNotrisScreenBuffer. If 1, the row has been updated and needs to be drawn.
 * boNotrisCollisionArray: a matrix of BOOLs, each item representing the state of an item from ciNotrisScreenBuffer. 1 means the cell is occupied, or drawn.
 * boPieceFalling: whether or not the piece has collided with floor.
 * srPlayFieldArea: a SMALL_RECT, the dimensions of the area into which the blocks fall and the action takes place.
 * srScoreArea: a SMALL_RECT, the dimensions of the area in which the score is displayed.
 * srLevelArea: a SMALL_RECT, the dimensions of the area in which the current level is displayed.
 * srNextPieceArea: a SMALL_RECT, the dimensions of the area in which the next piece to fall is displayed.
 * dwNotrisScore: DWORD storing points accrued through playing Notris.
 * nextPiece: an enum which determines the next piece to fall, displayed to the player ahead of time via the UI.
 * level: pace at which pieces fall. 1 - 7, with 7 the fastest. More points per row deletion at greater levels.
 */

typedef struct notrisInfo
{   
    CHAR_INFO** ciNotrisScreenBuffer ;
    CHAR_INFO** ciNotrisPauseMenu ;
    BOOL* boNotrisWriteArray ;
    BOOL** boNotrisCollisionArray ;
    BOOL boPieceFalling ;
    SMALL_RECT srPlayFieldArea ;
    SMALL_RECT srScoreArea ;
    SMALL_RECT srLevelArea ;
    SMALL_RECT srNextPieceArea ;
    DWORD notrisScore ;
    enum notrisLevel level ;
    enum notrisPieceShape pieceBag[7] ;
    enum notrisPieceShape nextPiece ;
    
} notrisInfo ;

typedef struct notrisMenu
{
    CHAR_INFO** ciNotrisMainMenu ;
    enum menuOption menuChoice ;
    COORD cursorPosition ;
}  notrisMenu ;

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
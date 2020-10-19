#ifndef NOTRIS_STRUCTURES_H
#define NOTRIS_STRUCTURES_H

// Idea is to make the whole Notris play area a malloc'd array of CHAR_INFO and write characters to it each frame. Hmmm...
typedef struct notrisPlayFieldInfo
{
    CHAR_INFO* playFieldBuffer ;
    COORD playFieldCoords ;
    SMALL_RECT playFieldArea ;
} notrisPlayFieldInfo ;

typedef struct notrisPiece
{
    // Piece type 1 - 7. Each coord is one of the blocks which makes up a piece.
    CHAR pieceShape ;
    // Current rotation. Different pieces have different number of rotations.
    CHAR piecePhase ;
    COORD blockOne ;
    COORD blockTwo ;
    COORD blockThree ;
    COORD blockFour ; 
    CHAR_INFO pieceLook ;
} notrisPiece ;

#endif /* NOTRIS_STRUCTURES_H */
#include <stdio.h>
#include <Windows.h>
#include "../shared/shared_game_functions.h"
#include "../shared/shared_graphics_functions.h"
#include "notris_game_functions.h"
#include "notris_graphics_functions.h"
#include "notris_structures.h"

/*
 * Uses the piece's COORDS as indices for a collision array, an array of BOOLS which signifies if cells are (un)occupied.
 */

BOOL notris_check_x_plus_collision( struct notrisInfo* niInfo, struct notrisPiece* piece )
{
    if(  ( niInfo->boNotrisCollisionArray[piece->blockOne.Y][piece->blockOne.X + 1] ) || 
         ( niInfo->boNotrisCollisionArray[piece->blockTwo.Y][piece->blockTwo.X + 1] ) ||
         ( niInfo->boNotrisCollisionArray[piece->blockThree.Y][piece->blockThree.X + 1] ) ||
         ( niInfo->boNotrisCollisionArray[piece->blockFour.Y][piece->blockFour.X + 1] ) )
    {
        return 1 ;
    }
    else
    {
        return 0 ;
    }
}

BOOL notris_check_x_minus_collision( struct notrisInfo* niInfo, struct notrisPiece* piece )
{
    if(  ( niInfo->boNotrisCollisionArray[piece->blockOne.Y][piece->blockOne.X - 1] ) || 
         ( niInfo->boNotrisCollisionArray[piece->blockTwo.Y][piece->blockTwo.X - 1] ) ||
         ( niInfo->boNotrisCollisionArray[piece->blockThree.Y][piece->blockThree.X - 1] ) ||
         ( niInfo->boNotrisCollisionArray[piece->blockFour.Y][piece->blockFour.X - 1] ) )
    {
        return 1 ;
    }
    else
    {
        return 0 ;
    }
}

/*
 * Separate function from above for simplicity of use with notris_move_piece().
 */

BOOL notris_check_y_collision( struct notrisInfo* niInfo, struct notrisPiece* piece )
{
    if(  ( niInfo->boNotrisCollisionArray[piece->blockOne.Y + 1][piece->blockOne.X] ) || 
         ( niInfo->boNotrisCollisionArray[piece->blockTwo.Y + 1][piece->blockTwo.X] ) ||
         ( niInfo->boNotrisCollisionArray[piece->blockThree.Y + 1][piece->blockThree.X] ) ||
         ( niInfo->boNotrisCollisionArray[piece->blockFour.Y + 1][piece->blockFour.X] ) )
    {
        return 1 ;
    }

    else
    {
        return 0 ;
    }
}

/*
 * Shape of piece is formed relative to coord of leading block, blockOne.
 */

struct notrisPiece* notris_create_piece( enum notrisPieceShape pieceShape, struct notrisInfo* niInfo ){

    notrisPiece *piece = malloc( sizeof( notrisPiece ) ) ;
    
    piece->pieceShape = pieceShape ;
    piece->piecePhase = 0 ;
    piece->pieceLook.Char.AsciiChar = 0 ;

    piece->blockOne.X = ( niInfo->srPlayFieldArea.Left + niInfo->srPlayFieldArea.Right ) / 2 ; // 24
    piece->blockOne.Y = niInfo->srPlayFieldArea.Top ; // 5

    switch( pieceShape )
    {   // Square
        case 1:
            piece->blockTwo.X = piece->blockOne.X + 1 ; 
            piece->blockTwo.Y = piece->blockOne.Y ;
            piece->blockThree.X = piece->blockOne.X ;
            piece->blockThree.Y = piece->blockOne.Y + 1 ;
            piece->blockFour.X = piece->blockOne.X + 1 ;
            piece->blockFour.Y = piece->blockOne.Y + 1 ;
            piece->pieceLook.Attributes = BACKGROUND_RED ;
            
            break ;
        // Line
        case 2:
            piece->blockTwo.X = piece->blockOne.X ;
            piece->blockTwo.Y = piece->blockOne.Y + 1 ;
            piece->blockThree.X = piece->blockOne.X ;
            piece->blockThree.Y = piece->blockOne.Y + 2 ;
            piece->blockFour.X = piece->blockOne.X ;
            piece->blockFour.Y = piece->blockOne.Y + 3 ;
            piece->pieceLook.Attributes = BACKGROUND_GREEN ;
            notris_rotate_piece_clockwise( piece ) ;

            break ;
        // 'L'
        case 3:
            piece->blockTwo.X = piece->blockOne.X ;
            piece->blockTwo.Y = piece->blockOne.Y + 1 ;
            piece->blockThree.X = piece->blockOne.X ;
            piece->blockThree.Y = piece->blockOne.Y + 2 ;
            piece->blockFour.X = piece->blockOne.X + 1 ;
            piece->blockFour.Y = piece->blockOne.Y + 2 ;
            piece->pieceLook.Attributes = BACKGROUND_GREEN | BACKGROUND_RED ;

            notris_rotate_piece_anticlockwise( piece ) ;

            break ;
        // Mirrored 'L'
        case 4:
            piece->blockTwo.X = piece->blockOne.X ;
            piece->blockTwo.Y = piece->blockOne.Y + 1 ;
            piece->blockThree.X = piece->blockOne.X ;
            piece->blockThree.Y = piece->blockOne.Y + 2 ;
            piece->blockFour.X = piece->blockOne.X - 1 ;
            piece->blockFour.Y = piece->blockOne.Y + 2 ;
            piece->pieceLook.Attributes = BACKGROUND_BLUE | BACKGROUND_RED ;

            notris_rotate_piece_clockwise( piece ) ;

            break ;
        // 'Z'
        case 5:
            piece->blockTwo.X = piece->blockOne.X + 1 ;
            piece->blockTwo.Y = piece->blockOne.Y ;
            piece->blockThree.X = piece->blockOne.X + 1 ;
            piece->blockThree.Y = piece->blockOne.Y + 1 ;
            piece->blockFour.X = piece->blockOne.X + 2 ;
            piece->blockFour.Y = piece->blockOne.Y + 1 ;
            piece->pieceLook.Attributes = BACKGROUND_GREEN | BACKGROUND_BLUE ;
            break ;
        // Mirrored 'Z'
        case 6:
            piece->blockTwo.X = piece->blockOne.X - 1 ;
            piece->blockTwo.Y = piece->blockOne.Y ;
            piece->blockThree.X = piece->blockOne.X - 1 ;
            piece->blockThree.Y = piece->blockOne.Y + 1 ;
            piece->blockFour.X = piece->blockOne.X - 2 ;
            piece->blockFour.Y = piece->blockOne.Y + 1 ;
            piece->pieceLook.Attributes =  BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY ;
            break ;
        // 'Hat'    
        case 7:
            piece->blockTwo.X = piece->blockOne.X ;
            piece->blockTwo.Y = piece->blockOne.Y + 1 ;
            piece->blockThree.X = piece->blockOne.X - 1 ;
            piece->blockThree.Y = piece->blockOne.Y + 1 ;
            piece->blockFour.X = piece->blockOne.X + 1 ;
            piece->blockFour.Y = piece->blockOne.Y + 1 ;
            piece->pieceLook.Attributes = BACKGROUND_BLUE ;
            break ;  
    }

    return piece ;
}

BOOL notris_move_piece( HANDLE* hInputBuffer, struct notrisInfo* niInfo, struct notrisPiece* piece )
{
    BOOL boPieceFallen = 0 ;

    DWORD numberOfEvents = 0 ;
    DWORD numberOfEventsRead = 0 ;

    GetNumberOfConsoleInputEvents( *hInputBuffer, &numberOfEvents ) ;

    if( numberOfEvents )
    {
        INPUT_RECORD* inputRecordArray = malloc( sizeof( INPUT_RECORD ) * numberOfEvents ) ;

        ReadConsoleInput( *hInputBuffer, inputRecordArray, numberOfEvents, &numberOfEventsRead ) ;

        for( int i = 0; i < numberOfEventsRead; i++ )
        {
            if( inputRecordArray[i].EventType == KEY_EVENT )
            {
                    
                if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE )
                {
                    if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                    {
                        exit( EXIT_SUCCESS ) ;
                    }
                }
                // Pauses the game.
                if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_TAB )
                {
                    BOOL loopBreak = 1 ;

                    if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                    {
                        while( loopBreak )
                        {   
                            DWORD numberOfEventsInner = 0 ;
                            DWORD numberOfEventsReadInner = 0 ;

                            GetNumberOfConsoleInputEvents( *hInputBuffer, &numberOfEventsInner ) ;

                            if( numberOfEventsInner )
                            {
                                INPUT_RECORD* inputRecordArrayInner = malloc( sizeof( INPUT_RECORD ) * numberOfEventsInner ) ;

                                ReadConsoleInput( *hInputBuffer, inputRecordArrayInner, numberOfEventsInner, &numberOfEventsReadInner ) ;

                                for( int i = 0; i < numberOfEventsReadInner; i++ )
                                {
                                    if( inputRecordArrayInner[i].EventType == KEY_EVENT )
                                    {
                                        if( inputRecordArrayInner[i].Event.KeyEvent.wVirtualKeyCode == VK_TAB )
                                        {
                                            if( inputRecordArrayInner[i].Event.KeyEvent.bKeyDown )
                                            {
                                                free( inputRecordArrayInner ) ;
                                                loopBreak = 0 ;
                                            }
                                        }
                                    }
                                }
                            }            
                        }
                    }
                }

                else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_CONTROL )
                {
                    if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                    {
                        if( piece->pieceShape != 1 ) // Square
                        {
                            if( notris_check_x_plus_collision( niInfo, piece ) && notris_check_x_minus_collision( niInfo, piece ) )
                            {
                                break ;
                            }
                            else if( notris_check_x_plus_collision( niInfo, piece ) )
                            {
                                switch( piece->pieceShape )
                                {
                                    case 2:
                                        if( piece->piecePhase == 0 )
                                        {
                                            piece->blockOne.X-- ;
                                            piece->blockTwo.X-- ;
                                            piece->blockThree.X-- ;
                                            piece->blockFour.X-- ;
                                        }
                                        else if( piece->piecePhase == 2 )
                                        {
                                            piece->blockOne.X-=2 ;
                                            piece->blockTwo.X-=2 ;
                                            piece->blockThree.X-=2 ;
                                            piece->blockFour.X-=2 ;
                                        }
                                        break ;

                                    case 3:
                                        if( piece->piecePhase == 2 )
                                        {
                                            piece->blockOne.X-- ;
                                            piece->blockTwo.X-- ;
                                            piece->blockThree.X-- ;
                                            piece->blockFour.X-- ;
                                        }
                                        break ;

                                    case 4:
                                        if( piece->piecePhase == 0 )
                                        {
                                            piece->blockOne.X-- ;
                                            piece->blockTwo.X-- ;
                                            piece->blockThree.X-- ;
                                            piece->blockFour.X-- ;
                                        }
                                        break ;

                                    case 5:
                                        if( piece->piecePhase == 1 )
                                        {
                                            piece->blockOne.X-- ;
                                            piece->blockTwo.X-- ;
                                            piece->blockThree.X-- ;
                                            piece->blockFour.X-- ;
                                        }
                                        break ;

                                    case 6 :
                                        if( piece->piecePhase == 1 )
                                        {
                                            piece->blockOne.X-- ;
                                            piece->blockTwo.X-- ;
                                            piece->blockThree.X-- ;
                                            piece->blockFour.X-- ;
                                        }
                                        break ;
                                    case 7:
                                        if( piece->piecePhase == 3 )
                                        {
                                            piece->blockOne.X-- ;
                                            piece->blockTwo.X-- ;
                                            piece->blockThree.X-- ;
                                            piece->blockFour.X-- ;
                                        }
                                        break ;
                                }   
                            }
                            else if( notris_check_x_minus_collision( niInfo, piece ) )
                            {
                                switch( piece->pieceShape )
                                {
                                    case 2:
                                        if( piece->piecePhase == 0 )
                                        {
                                            piece->blockOne.X += 2 ;
                                            piece->blockTwo.X += 2 ;
                                            piece->blockThree.X += 2 ;
                                            piece->blockFour.X += 2 ;
                                        }
                                        else if( piece->piecePhase == 2 )
                                        {
                                            piece->blockOne.X++ ;
                                            piece->blockTwo.X++ ;
                                            piece->blockThree.X++ ;
                                            piece->blockFour.X++ ;
                                        }
                                        break ;

                                    case 3:
                                        if( piece->piecePhase == 0 )
                                        {
                                            piece->blockOne.X++ ;
                                            piece->blockTwo.X++ ;
                                            piece->blockThree.X++ ;
                                            piece->blockFour.X++ ;
                                        }
                                        break ;

                                    case 4:
                                        if( piece->piecePhase == 2 )
                                        {
                                            piece->blockOne.X++ ;
                                            piece->blockTwo.X++ ;
                                            piece->blockThree.X++ ;
                                            piece->blockFour.X++ ;
                                        }
                                        break ;

                                    case 5:
                                        if( piece->piecePhase == 3 )
                                        {
                                            piece->blockOne.X++ ;
                                            piece->blockTwo.X++ ;
                                            piece->blockThree.X++ ;
                                            piece->blockFour.X++ ;
                                        }
                                        break ;

                                    case 6 :
                                        if( piece->piecePhase == 3 )
                                        {
                                            piece->blockOne.X++ ;
                                            piece->blockTwo.X++ ;
                                            piece->blockThree.X++ ;
                                            piece->blockFour.X++ ;
                                        }
                                        break ;

                                    case 7:
                                        if( piece->piecePhase == 1 )
                                        {
                                            piece->blockOne.X++ ;
                                            piece->blockTwo.X++ ;
                                            piece->blockThree.X++ ;
                                            piece->blockFour.X++ ;
                                        }
                                        break ;
                                }
                            }
                        }
                        notris_rotate_piece_clockwise( piece ) ;
                    }
                }

                else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_SHIFT )
                {
                    if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                    {
                        if( piece->pieceShape != 1 ) // Square
                        {
                            if( notris_check_x_plus_collision( niInfo, piece ) && notris_check_x_minus_collision( niInfo, piece ) )
                            {
                                break ;
                            }
                            else if( notris_check_x_plus_collision( niInfo, piece ) )
                            {
                                switch( piece->pieceShape )
                                {
                                    case 2:
                                        if( piece->piecePhase == 0 )
                                        {
                                            piece->blockOne.X -=2 ;
                                            piece->blockTwo.X -=2 ;
                                            piece->blockThree.X -= 2 ;
                                            piece->blockFour.X -= 2 ;
                                        }
                                        else if( piece->piecePhase == 2 )
                                        {
                                            piece->blockOne.X-- ;
                                            piece->blockTwo.X-- ;
                                            piece->blockThree.X-- ;
                                            piece->blockFour.X-- ;
                                        }
                                        break ;

                                    case 3:
                                        if( piece->piecePhase == 2 )
                                        {
                                            piece->blockOne.X-- ;
                                            piece->blockTwo.X-- ;
                                            piece->blockThree.X-- ;
                                            piece->blockFour.X-- ;
                                        }
                                        break ;

                                    case 4:
                                        if( piece->piecePhase == 0 )
                                        {
                                            piece->blockOne.X-- ;
                                            piece->blockTwo.X-- ;
                                            piece->blockThree.X-- ;
                                            piece->blockFour.X-- ;
                                        }
                                        break ;

                                    case 5:
                                        if( piece->piecePhase == 1 )
                                        {
                                            piece->blockOne.X-- ;
                                            piece->blockTwo.X-- ;
                                            piece->blockThree.X-- ;
                                            piece->blockFour.X-- ;
                                        }
                                        break ;

                                    case 6 :
                                        if( piece->piecePhase == 1 )
                                        {
                                            piece->blockOne.X-- ;
                                            piece->blockTwo.X-- ;
                                            piece->blockThree.X-- ;
                                            piece->blockFour.X-- ;
                                        }
                                        break ;
                                    case 7:
                                        if( piece->piecePhase == 3 )
                                        {
                                            piece->blockOne.X-- ;
                                            piece->blockTwo.X-- ;
                                            piece->blockThree.X-- ;
                                            piece->blockFour.X-- ;
                                        }
                                        break ;
                                }   
                            }
                            else if( notris_check_x_minus_collision( niInfo, piece ) )
                            {
                                switch( piece->pieceShape )
                                {
                                    case 2:
                                        if( piece->piecePhase == 0 )
                                        {
                                            piece->blockOne.X ++ ;
                                            piece->blockTwo.X ++ ;
                                            piece->blockThree.X ++ ;
                                            piece->blockFour.X ++ ;
                                        }
                                        else if( piece->piecePhase == 2 )
                                        {
                                            piece->blockOne.X += 2 ;
                                            piece->blockTwo.X += 2 ;
                                            piece->blockThree.X += 2 ;
                                            piece->blockFour.X += 2 ;
                                        }
                                        break ;

                                    case 3:
                                        if( piece->piecePhase == 0 )
                                        {
                                            piece->blockOne.X++ ;
                                            piece->blockTwo.X++ ;
                                            piece->blockThree.X++ ;
                                            piece->blockFour.X++ ;
                                        }
                                        break ;

                                    case 4:
                                        if( piece->piecePhase == 2 )
                                        {
                                            piece->blockOne.X++ ;
                                            piece->blockTwo.X++ ;
                                            piece->blockThree.X++ ;
                                            piece->blockFour.X++ ;
                                        }
                                        break ;

                                    case 5:
                                        if( piece->piecePhase == 3 )
                                        {
                                            piece->blockOne.X++ ;
                                            piece->blockTwo.X++ ;
                                            piece->blockThree.X++ ;
                                            piece->blockFour.X++ ;
                                        }
                                        break ;

                                    case 6 :
                                        if( piece->piecePhase == 3 )
                                        {
                                            piece->blockOne.X++ ;
                                            piece->blockTwo.X++ ;
                                            piece->blockThree.X++ ;
                                            piece->blockFour.X++ ;
                                        }
                                        break ;

                                    case 7:
                                        if( piece->piecePhase == 1 )
                                        {
                                            piece->blockOne.X++ ;
                                            piece->blockTwo.X++ ;
                                            piece->blockThree.X++ ;
                                            piece->blockFour.X++ ;
                                        }
                                        break ;
                                }
                            }
                        }
                        notris_rotate_piece_anticlockwise( piece ) ;
                    }
                }

                else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_DOWN )
                {
                    if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                    {
                        if( notris_check_y_collision( niInfo, piece ) )
                        {
                            return 1 ;
                        }
                        else
                        {
                            piece->blockOne.Y++ ;
                            piece->blockTwo.Y++ ;
                            piece->blockThree.Y++ ;
                            piece->blockFour.Y++ ;
                        }
                    }
                }
                else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_LEFT )
                {
                    if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                    {
                        if( notris_check_x_minus_collision( niInfo, piece ) )
                        {
                            break ;
                        }
                        else
                        {
                            piece->blockOne.X-- ;
                            piece->blockTwo.X-- ;
                            piece->blockThree.X-- ;
                            piece->blockFour.X-- ;
                        }
                    }
                }
                else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_RIGHT )
                {
                    if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                    {
                        if( notris_check_x_plus_collision( niInfo, piece ) )
                        {
                            break ;
                        }
                        else
                        {
                            piece->blockOne.X++ ;
                            piece->blockTwo.X++ ;
                            piece->blockThree.X++ ;
                            piece->blockFour.X++ ;
                        }
                    }
                }
            }
        }
        free( inputRecordArray ) ;
    }
    return 0 ;
}

BOOL notris_piece_falling( DWORD* dwCounter, struct notrisInfo* niInfo, struct notrisPiece* piece )
{
    if( !notris_check_y_collision( niInfo, piece ) )
    {
        if( *dwCounter == 10 )
        {
            *dwCounter = 0 ;

            piece->blockOne.Y++ ;
            piece->blockTwo.Y++ ;
            piece->blockThree.Y++ ;
            piece->blockFour.Y++ ;
        }
        return 0 ;
    }
    else
    {
        return 1 ;
    }
}

/*
 * Rotates piece based on current 'phase', or the degree of rotation from starting position.
 */

void notris_rotate_piece_anticlockwise( struct notrisPiece* piece )
{
    switch( piece->pieceShape ){
        // Square
        case 1:
            break ;
        // Line
        case 2:
             switch( piece->piecePhase )
            {
                case 0:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.X += 2 ;
                    piece->blockFour.Y -= 2 ;
                    piece->piecePhase = 3 ;
                break ;

                case 1:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.X += 2 ;
                    piece->blockFour.Y += 2 ;
                    piece->piecePhase = 0 ;
                break ;

                case 2:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.X -= 2 ;
                    piece->blockFour.Y += 2 ;
                    piece->piecePhase = 1 ;
                break ;

                case 3 :
                    piece->blockOne.X++ ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.X -= 2 ;
                    piece->blockFour.Y -= 2 ;
                    piece->piecePhase = 2 ;
                break ;
            }
        break ;
        // 'L'
        case 3:
             switch( piece->piecePhase )
            {
                case 0:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.Y -= 2 ;
                    piece->piecePhase = 3 ;
                break ;

                case 1:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.X += 2 ;
                    piece->piecePhase = 0 ;
                break ;

                case 2:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.Y += 2 ;
                    piece->piecePhase = 1 ;
                break ;

                case 3:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.X -= 2 ;
                    piece->piecePhase = 2 ;
                break ;
            }
            break ;
        // Mirrored 'L'
        case 4:
            switch( piece->piecePhase )
            {
                case 0:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.X += 2 ;
                    piece->piecePhase = 3 ;
                break ;

                case 1:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.Y += 2 ;
                    piece->piecePhase = 0 ;
                break ;

                case 2:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.X -= 2 ;
                    piece->piecePhase = 1 ;
                break ;

                case 3:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.Y -= 2 ;
                    piece->piecePhase = 2 ;
                break ;
            }
            break ;
        // 'Z'
        case 5:
            switch( piece->piecePhase )
            {
                case 0:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.Y -= 2 ;
                    piece->piecePhase = 3 ;
                break ;

                case 1:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.X += 2 ;
                    piece->piecePhase = 0 ;
                break ;

                case 2:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.Y += 2 ;
                    piece->piecePhase = 1 ;
                break ;

                case 3:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.X -= 2 ;
                    piece->piecePhase = 2 ;
                break ;
            }
            break ;
        // Mirrored 'Z'
        case 6:
            switch( piece->piecePhase )
            {
                case 0:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.X += 2 ;
                    piece->piecePhase = 3 ;
                break ;

                case 1:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.Y += 2 ;
                    piece->piecePhase = 0 ;
                break ;

                case 2:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.X -= 2 ;
                    piece->piecePhase = 1 ;
                break ;

                case 3:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.Y -= 2 ;
                    piece->piecePhase = 2 ;
                break ;
            }
            break ;
        // 'Hat'
        case 7:
            switch( piece->piecePhase )
            {
                case 0:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.X-- ;
                    piece->blockFour.Y-- ;
                    piece->piecePhase = 3 ;
                break ;

                case 1:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.X++ ;
                    piece->blockFour.Y-- ;
                    piece->piecePhase = 0 ;
                break ;

                case 2:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.X++ ;
                    piece->blockFour.Y++ ;
                    piece->piecePhase = 1 ;
                break ;

                case 3:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.X-- ;
                    piece->blockFour.Y++ ;
                    piece->piecePhase = 2 ;
                break ;
            }
        break ;
    }
}

void notris_rotate_piece_clockwise( struct notrisPiece* piece )
{
    switch( piece->pieceShape ){
        // Square
        case 1:
            break ;
        // Line
        case 2:
             switch( piece->piecePhase )
            {
                case 0:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.X -= 2 ;
                    piece->blockFour.Y -= 2 ;
                    piece->piecePhase = 1 ;
                break ;

                case 1:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.X += 2 ;
                    piece->blockFour.Y -= 2 ;
                    piece->piecePhase = 2 ;
                break ;

                case 2:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.X += 2 ;
                    piece->blockFour.Y += 2 ;
                    piece->piecePhase = 3 ;
                    break ;

                case 3:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.X -= 2 ;
                    piece->blockFour.Y += 2 ;
                    piece->piecePhase = 0 ;
                    break ;
            }
        break ;
        // 'L'
        case 3:
             switch( piece->piecePhase )
            {
                case 0:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.X -= 2 ;
                    piece->piecePhase = 1 ;
                break ;

                case 1:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.Y -= 2 ;
                    piece->piecePhase = 2 ;
                break ;

                case 2:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.X += 2 ;
                    piece->piecePhase = 3 ;
                break ;

                case 3:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.Y += 2 ;
                    piece->piecePhase = 0 ;
                break ;
            }
            break ;
        // Mirrored 'L'
        case 4:
            switch( piece->piecePhase )
            {
                case 0:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.Y -= 2 ;
                    piece->piecePhase = 1 ;
                break ;

                case 1:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.X += 2 ;
                    piece->piecePhase = 2 ;
                break ;

                case 2:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.Y += 2 ;
                    piece->piecePhase = 3 ;
                break ;

                case 3:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.X -= 2 ;
                    piece->piecePhase = 0 ;
                break ;
            }
            break ;
        // 'Z'
        case 5:
            switch( piece->piecePhase )
            {
                case 0:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.X -= 2 ;
                    piece->piecePhase = 1 ;
                break ;

                case 1:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.Y -= 2 ;
                    piece->piecePhase = 2 ;
                break ;

                case 2:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.X += 2 ;
                    piece->piecePhase = 3 ;
                break ;

                case 3:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.Y += 2 ;
                    piece->piecePhase = 0 ;
                break ;
            }
            break ;
        // Mirrored 'Z'
        case 6:
            switch( piece->piecePhase )
            {
                case 0:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.Y -= 2 ;
                    piece->piecePhase = 1 ;
                break ;

                case 1:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.X += 2 ;
                    piece->piecePhase = 2 ;
                break ;

                case 2:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.Y += 2 ;
                    piece->piecePhase = 3 ;
                break ;

                case 3:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.X -= 2 ;
                    piece->piecePhase = 0 ;
                break ;
            }
            break ;
        // 'Hat'
        case 7:
            switch( piece->piecePhase )
            {
                case 0:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.X-- ;
                    piece->blockFour.Y++ ;
                    piece->piecePhase = 1 ;
                break ;

                case 1:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y++ ;
                    piece->blockThree.X++ ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.X-- ;
                    piece->blockFour.Y-- ;
                    piece->piecePhase = 2 ;
                break ;

                case 2:
                    piece->blockOne.X-- ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y++ ;
                    piece->blockFour.X++ ;
                    piece->blockFour.Y-- ;
                    piece->piecePhase = 3 ;
                break ;

                case 3:
                    piece->blockOne.X++ ;
                    piece->blockOne.Y-- ;
                    piece->blockThree.X-- ;
                    piece->blockThree.Y-- ;
                    piece->blockFour.X++ ;
                    piece->blockFour.Y++ ;
                    piece->piecePhase = 0 ;
                break ;
            }
        break ;
    }
}

void notris_set_boundaries( struct notrisInfo* niInfo )
{
  for( int roof = niInfo->srPlayFieldArea.Left - 1; roof < niInfo->srPlayFieldArea.Right + 1 ; roof++ )
  {
    niInfo->boNotrisCollisionArray[niInfo->srPlayFieldArea.Top - 1][roof] = 1 ;
  }

  for( int floor = niInfo->srPlayFieldArea.Left - 1; floor < niInfo->srPlayFieldArea.Right + 1; floor++ )
  {
    niInfo->boNotrisCollisionArray[niInfo->srPlayFieldArea.Bottom][floor] = 1 ;
  }

  for( int leftWall = niInfo->srPlayFieldArea.Top; leftWall < niInfo->srPlayFieldArea.Bottom; leftWall++ )
  {
    niInfo->boNotrisCollisionArray[leftWall][niInfo->srPlayFieldArea.Left - 1] = 1 ;
  }

  for( int rightWall = niInfo->srPlayFieldArea.Top; rightWall < niInfo->srPlayFieldArea.Bottom; rightWall++ )
  {
    niInfo->boNotrisCollisionArray[rightWall][niInfo->srPlayFieldArea.Right] = 1 ;
  }
}

void notris_setup( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisInfo* niInfo )
{
    niInfo->srPlayFieldArea.Left = ( csbiInfo->srWindow.Right / 2 ) - 6 ;
    niInfo->srPlayFieldArea.Top =  (csbiInfo->srWindow.Bottom / 2) - 10 ;
    niInfo->srPlayFieldArea.Right = ( csbiInfo->srWindow.Right / 2 ) + 6 ;
    niInfo->srPlayFieldArea.Bottom =  (csbiInfo->srWindow.Bottom / 2) + 10 ;

    niInfo->notrisScore = 0 ;

    niInfo->nextPiece = random_number_in_range( 1, 7 ) ; 

    SHORT bufferWidth = csbiInfo->dwSize.X ;
    SHORT bufferHeight = csbiInfo->dwSize.Y ;

    niInfo->ciNotrisScreenBuffer = ( CHAR_INFO** ) malloc( bufferHeight  * sizeof( CHAR_INFO* ) ) ;
    niInfo->boNotrisCollisionArray = ( BOOL** ) malloc( bufferHeight  * sizeof( BOOL* ) ) ;
    niInfo->boNotrisWriteArray = ( BOOL* ) malloc( bufferHeight * sizeof( BOOL ) ) ;

    for( int i = 0; i < bufferHeight; i++ )
    {
        niInfo->ciNotrisScreenBuffer[i] = ( CHAR_INFO* ) malloc( bufferWidth * sizeof( CHAR_INFO ) ) ;
        niInfo->boNotrisCollisionArray[i] = ( BOOL* ) malloc( bufferWidth * sizeof( BOOL ) ) ;
        niInfo->boNotrisWriteArray[i] = 0 ;
    }

    for( int y = 0; y < bufferHeight; y++ )
    {
        for( int x = 0; x < bufferWidth; x++ )
        {
            niInfo->ciNotrisScreenBuffer[y][x].Char.AsciiChar = 0 ;
            niInfo->ciNotrisScreenBuffer[y][x].Attributes = 0 ;
            niInfo->boNotrisCollisionArray[y][x] = 0 ;
        }
    }
}

void play_notris( HANDLE* hScreenBuffer, HANDLE* hInputBuffer, 
                  CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisInfo* niInfo )
{ 
    DWORD dwDropCounter ;
    BOOL pieceFalling ;

    notris_setup( csbiInfo, niInfo ) ;

    notris_set_boundaries( niInfo ) ;

    notris_draw_UI( niInfo ) ;

    srand( time( 0 ) ) ;

    while(1)
    {
        notrisPiece *p = notris_create_piece( random_number_in_range( 1, 7 ), niInfo ) ;

        pieceFalling = 1 ;

        dwDropCounter = 0 ;
       
        while( pieceFalling )
        {   
            // TODO: Compare old vs new collision array to see if needs to be drawn.
            
            notris_erase_piece( niInfo, p ) ;

            if ( notris_piece_falling( &dwDropCounter, niInfo, p ) )
            {
                pieceFalling = 0 ;
            }

            if( notris_move_piece( hInputBuffer, niInfo, p ) )
            {
                pieceFalling = 0 ;
            }
            
            notris_draw_piece( niInfo, p ) ;

            draw_buffer( hScreenBuffer, csbiInfo, niInfo->ciNotrisScreenBuffer ) ;

            dwDropCounter++ ;

            Sleep( 50 ) ;
        }

        notris_draw_piece( niInfo, p ) ;

        notris_erase_row( niInfo ) ;

        free( p ) ;
    }
}
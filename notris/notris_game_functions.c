#include <stdio.h>
#include <Windows.h>
#include "../shared/console_functions.h"
#include "../shared/shared_game_functions.h"
#include "../shared/shared_graphics_functions.h"
#include "notris_game_functions.h"
#include "notris_graphics_functions.h"
#include "notris_structures.h"

/*
 * Uses the piece's COORDS as indices for niNotrisInfo.boNotrisCollisionArray.
 * TODO: redo checking functions, switching on INPUT_RECORD.Event.KeyEvent.wVirtualKey.
 */

BOOL notris_check_axis_collision( struct notrisInfo* niInfo, struct notrisPiece* piece, SHORT offset, CHAR axis )
{
    if( axis == 'x' )
    {
        if( ( niInfo->boNotrisCollisionArray[piece->blockOne.Y][piece->blockOne.X + offset] ) || 
            ( niInfo->boNotrisCollisionArray[piece->blockTwo.Y][piece->blockTwo.X + offset] ) ||
            ( niInfo->boNotrisCollisionArray[piece->blockThree.Y][piece->blockThree.X + offset] ) ||
            ( niInfo->boNotrisCollisionArray[piece->blockFour.Y][piece->blockFour.X + offset] ) )
        {
            return 1 ;
        }
    }
    else if( axis == 'y' )
    {
        if( ( niInfo->boNotrisCollisionArray[piece->blockOne.Y + offset][piece->blockOne.X] ) || 
            ( niInfo->boNotrisCollisionArray[piece->blockTwo.Y + offset][piece->blockTwo.X] ) ||
            ( niInfo->boNotrisCollisionArray[piece->blockThree.Y + offset][piece->blockThree.X] ) ||
            ( niInfo->boNotrisCollisionArray[piece->blockFour.Y + offset][piece->blockFour.X] ) )
        {
            return 1 ;
        }
    }
    else
    {
        report_error( "Incorrect axis parameter." ) ;
    }
    
    return 0 ;
}

BOOL notris_check_move_collision( struct notrisInfo* niInfo, struct notrisPiece* piece, WORD wVirtualKeyCode )
{   
    switch( wVirtualKeyCode )
    {
        case VK_LEFT:
            if( notris_check_axis_collision( niInfo, piece, -1, 'x' ) )
            {
                return 1 ;
            }

            break ;

        case VK_RIGHT:
            if( notris_check_axis_collision( niInfo, piece, 1, 'x' ) )
            {
                return 1 ;
            }
            
            break ;

        case VK_DOWN:
            if( notris_check_axis_collision( niInfo, piece, 1, 'y' ) )
            {
                return 1 ;
            }

            break ;
        // Anticlockwise rotation.
        case VK_CONTROL:
            // 1 == square, which doesn't need to rotate.
            if( piece->pieceShape != 1 )
            {
                // Specific to pieceShape 2 as it has longer 'reach' in certain situations when rotating.
                if( notris_check_axis_collision( niInfo, piece, -2, 'x' )   && piece->pieceShape == 2 )
                {
                    if( piece->piecePhase == 2 )
                    {
                        if( notris_check_axis_collision( niInfo, piece, 1, 'x' ) )
                        {
                            return 1 ;
                        }

                        piece->blockOne.X++ ;
                        piece->blockTwo.X++ ;
                        piece->blockThree.X++ ;
                        piece->blockFour.X++ ;
                    }
                }
                // Specific to pieceShape 2.
                else if( notris_check_axis_collision( niInfo, piece, 2, 'x' ) && piece->pieceShape == 2 )
                {                        
                    if( piece->piecePhase == 0 )
                    {
                        if( notris_check_axis_collision( niInfo, piece, -1, 'x' ) )
                        {
                            return 1 ;
                        }

                        piece->blockOne.X-- ;
                        piece->blockTwo.X-- ;
                        piece->blockThree.X-- ;
                        piece->blockFour.X-- ;
                    }                        
                }
                // Specific to piece 2
                else if( notris_check_axis_collision( niInfo, piece, 2, 'y' ) && piece->pieceShape == 2 )
                {
                    if( piece->piecePhase == 1 )
                    {
                        if( notris_check_axis_collision( niInfo, piece, -1, 'y' ) )
                        {
                            return 1 ;
                        }

                        piece->blockOne.Y -- ;
                        piece->blockTwo.Y -- ;
                        piece->blockThree.Y -- ;
                        piece->blockFour.Y -- ;
                    }                       
                }                   
                // If cell to the left, or -x, is occupied.
                else if( notris_check_axis_collision( niInfo, piece, -1, 'x' ) )
                {
                    if( notris_check_axis_collision( niInfo, piece, 1, 'x' ) )
                    {
                        return 1 ;
                    }

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
                // If cell to the right, or +x, is occupied.
                else if( notris_check_axis_collision( niInfo, piece, 1, 'x' ) )
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
                // If cell above, or -y, is occupied.
                else if( notris_check_axis_collision( niInfo, piece, -1, 'y' ) )
                {
                    return 1 ;
                }
                // If cell below, or +y, is occupied.
                else if( notris_check_axis_collision( niInfo, piece, 1, 'y' ) )
                {
                    switch( piece->pieceShape )
                    {
                        case 2:
                            if( piece->piecePhase == 1 )
                            {
                                piece->blockOne.Y -= 2 ;
                                piece->blockTwo.Y -= 2 ;
                                piece->blockThree.Y -= 2 ;
                                piece->blockFour.Y -= 2 ;
                            }
                            else if( piece->piecePhase == 3 )
                            {
                                piece->blockOne.Y-- ;
                                piece->blockTwo.Y-- ;
                                piece->blockThree.Y-- ;
                                piece->blockFour.Y-- ;
                            }
                            break ;
                        
                        case 3:
                            if( piece->piecePhase == 3 )
                            {
                                piece->blockOne.Y-- ;
                                piece->blockTwo.Y-- ;
                                piece->blockThree.Y-- ;
                                piece->blockFour.Y-- ;
                            }
                            break ;
                        
                        case 4:
                            if( piece->piecePhase == 1 )
                            {
                                piece->blockOne.Y-- ;
                                piece->blockTwo.Y-- ;
                                piece->blockThree.Y-- ;
                                piece->blockFour.Y-- ;
                            }
                            break ;
                        
                        case 5:
                            if( piece->piecePhase == 2 )
                            {
                                piece->blockOne.Y-- ;
                                piece->blockTwo.Y-- ;
                                piece->blockThree.Y-- ;
                                piece->blockFour.Y-- ;
                            }
                            break ;
                        
                        case 6:
                            if( piece->piecePhase == 2 )
                            {
                                piece->blockOne.Y-- ;
                                piece->blockTwo.Y-- ;
                                piece->blockThree.Y-- ;
                                piece->blockFour.Y-- ;
                            }
                            break ;
                        
                        case 7:
                            if( piece->piecePhase == 0 )
                            {
                                piece->blockOne.Y-- ;
                                piece->blockTwo.Y-- ;
                                piece->blockThree.Y-- ;
                                piece->blockFour.Y-- ;
                            }
                            break ;
                    }
                }                  
            }
            break ;

        case VK_MENU:
            if( piece->pieceShape != 1 )
            {
                if( notris_check_axis_collision( niInfo, piece, -2, 'x' ) && piece->pieceShape == 2)
                {
                    if( piece->piecePhase == 0 )
                    {
                        if( notris_check_axis_collision( niInfo, piece, 1, 'x' ) )
                        {
                            return 1 ;
                        }

                        piece->blockOne.X++ ;
                        piece->blockTwo.X++ ;
                        piece->blockThree.X++ ;
                        piece->blockFour.X++ ;
                    }
                }
                else if( notris_check_axis_collision( niInfo, piece, 2, 'x' ) && piece->pieceShape == 2)
                {
                    if( piece->piecePhase == 2 )
                    {
                        if( notris_check_axis_collision( niInfo, piece, -1, 'x' ) )
                        {
                            return 1 ;
                        }

                        piece->blockOne.X-- ;
                        piece->blockTwo.X-- ;
                        piece->blockThree.X-- ;
                        piece->blockFour.X-- ;
                    }                     
                }
                else if( notris_check_axis_collision( niInfo, piece, 2, 'y' ) && piece->pieceShape == 2)
                {
                    if( piece->piecePhase == 3 )
                    {
                        if( notris_check_axis_collision( niInfo, piece, -1, 'y' ) )
                        {
                            return 1 ;
                        }

                        piece->blockOne.Y -- ;
                        piece->blockTwo.Y -- ;
                        piece->blockThree.Y -- ;
                        piece->blockFour.Y -- ;
                    }                       
                }
                else if( notris_check_axis_collision( niInfo, piece, -1, 'x' ) )
                {
                    if( notris_check_axis_collision( niInfo, piece, 1, 'x' ) )
                        {
                            return 1 ;
                        }

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
                else if( notris_check_axis_collision( niInfo, piece, 1, 'x' ) )
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
                else if( notris_check_axis_collision( niInfo, piece, -1, 'y' ) )
                {
                    return 1 ;
                }
                else if( notris_check_axis_collision( niInfo, piece, 1, 'y' ) )
                {
                    switch( piece->pieceShape )
                    {
                        case 2:
                            if( piece->piecePhase == 1 )
                            {
                                piece->blockOne.Y-- ;
                                piece->blockTwo.Y-- ;
                                piece->blockThree.Y-- ;
                                piece->blockFour.Y-- ;
                            }
                            else if( piece->piecePhase == 3 )
                            {
                                piece->blockOne.Y -= 2 ;
                                piece->blockTwo.Y -= 2 ;
                                piece->blockThree.Y -= 2 ;
                                piece->blockFour.Y -= 2 ;
                            }
                            break ;
                        
                        case 3:
                            if( piece->piecePhase == 3 )
                            {
                                piece->blockOne.Y-- ;
                                piece->blockTwo.Y-- ;
                                piece->blockThree.Y-- ;
                                piece->blockFour.Y-- ;
                            }
                            break ;
                        
                        case 4:
                            if( piece->piecePhase == 1 )
                            {
                                piece->blockOne.Y-- ;
                                piece->blockTwo.Y-- ;
                                piece->blockThree.Y-- ;
                                piece->blockFour.Y-- ;
                            }
                            break ;
                        
                        case 5:
                            if( piece->piecePhase == 2 )
                            {
                                piece->blockOne.Y-- ;
                                piece->blockTwo.Y-- ;
                                piece->blockThree.Y-- ;
                                piece->blockFour.Y-- ;
                            }
                            break ;
                        
                        case 6:
                            if( piece->piecePhase == 2 )
                            {
                                piece->blockOne.Y-- ;
                                piece->blockTwo.Y-- ;
                                piece->blockThree.Y-- ;
                                piece->blockFour.Y-- ;
                            }
                            break ;
                        
                        case 7:
                            if( piece->piecePhase == 0 )
                            {
                                piece->blockOne.Y-- ;
                                piece->blockTwo.Y-- ;
                                piece->blockThree.Y-- ;
                                piece->blockFour.Y-- ;
                            }
                            break ;
                    }
                }

            }
            break ;

        default:
            report_error( "Incorrect virtual key code parameter." ) ;
    }

    return 0 ;
}

void notris_cleanup( CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisInfo* niInfo )
{
    SHORT bufferHeight = csbiInfo->dwSize.Y ;

    for( int y = 0; y < bufferHeight; y++ )
    {
        free( niInfo->ciNotrisScreenBuffer[y] ) ;
        free( niInfo->ciNotrisMainMenu[y] ) ;
        free( niInfo->ciNotrisPauseMenu[y] ) ;
        free( niInfo->boNotrisCollisionArray[y] ) ;
    }

    free( niInfo->ciNotrisScreenBuffer ) ;
    free( niInfo->ciNotrisMainMenu ) ;
    free( niInfo->ciNotrisPauseMenu ) ;
    free( niInfo->boNotrisCollisionArray ) ;
    free( niInfo->boNotrisWriteArray ) ;
}

void notris_create_bag( struct notrisInfo* niInfo )
{
    CHAR cSAndZCounter = 0 ;

    notrisPieceShape piece ;

    for( int i = 0; i < 7; i++ )
    {
        piece = random_number_in_range( 1, 7 ) ;

        if( cSAndZCounter == 4 && (  piece == 5 || piece == 6  ) )
        {
            while( piece != 5 && piece != 4 )
            {
                piece = random_number_in_range( 1, 7 ) ;
            }
        }   
        else if( piece == 5 || piece == 6 )
        {
            cSAndZCounter++ ;
        }

        niInfo->pieceBag[i] = piece ;
    }
}

/*
 * Shape of piece is formed relative to coord of leading block, blockOne.
 */

struct notrisPiece* notris_create_piece( enum notrisPieceShape pieceShape, struct notrisInfo* niInfo, SHORT leadBlockX, SHORT leadBlockY )
{
    notrisPiece *piece = malloc( sizeof( notrisPiece ) ) ;
    
    piece->pieceShape = pieceShape ;
    piece->piecePhase = 0 ;
    piece->pieceLook.Char.AsciiChar = 0 ;

    piece->blockOne.X =  leadBlockX ;
    piece->blockOne.Y = leadBlockY ;

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

            //notris_rotate_piece_clockwise( piece ) ;

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

            //notris_rotate_piece_anticlockwise( piece ) ;

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

            //notris_rotate_piece_clockwise( piece ) ;

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

BOOL notris_menu_selection( HANDLE* hInputBuffer, struct notrisInfo* niInfo )
{
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
                if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_UP )
                {
                    if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                    {
                        
                    }
                }
                else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_DOWN )
                {
                    if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                    {
                        
                    }
                }
                else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_SPACE )
                {
                    if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                    {
                        return 1 ;
                    }
                }
                else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE )
                {
                    if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                    {
                        exit( EXIT_SUCCESS ) ;
                    }
                }
            }
        }
        free( inputRecordArray ) ;
    }
    return 0 ;
}

BOOL notris_move_piece( HANDLE* hScreenBuffer, HANDLE* hInputBuffer, 
                        CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisInfo* niInfo, struct notrisPiece* piece )
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
                else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_TAB )
                {
                    BOOL loopBreak = 1 ;

                    if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                    {
                        CHAR cursor = 26 ;

                        SHORT cursorX = niInfo->srPlayFieldArea.Left + 1 ;
                        SHORT cursorY = niInfo->srPlayFieldArea.Top + 7 ;

                        BOOL cursorSelection = 1 ;

                        niInfo->ciNotrisPauseMenu[cursorY][cursorX].Char.AsciiChar = 26 ;
                        niInfo->ciNotrisPauseMenu[cursorY][cursorX].Attributes = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN ;

                        niInfo->ciNotrisPauseMenu[cursorY + 3][cursorX].Char.AsciiChar = 0 ;
                        niInfo->ciNotrisPauseMenu[cursorY + 3][cursorX].Attributes = 0 ;

                        while( loopBreak )
                        {   
                            display_buffer( hScreenBuffer, csbiInfo, niInfo->ciNotrisPauseMenu ) ;

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

                                                display_buffer( hScreenBuffer, csbiInfo, niInfo->ciNotrisScreenBuffer ) ;
                                            }
                                        }
                                        else if( inputRecordArrayInner[i].Event.KeyEvent.wVirtualKeyCode == VK_UP )
                                        {
                                            if( inputRecordArrayInner[i].Event.KeyEvent.bKeyDown )
                                            {
                                                if( !cursorSelection )
                                                {                                           
                                                    niInfo->ciNotrisPauseMenu[cursorY][cursorX].Char.AsciiChar = 26 ;
                                                    niInfo->ciNotrisPauseMenu[cursorY][cursorX].Attributes = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN ;

                                                    niInfo->ciNotrisPauseMenu[cursorY + 3][cursorX].Char.AsciiChar = 0 ;
                                                    niInfo->ciNotrisPauseMenu[cursorY + 3][cursorX].Attributes = 0 ;

                                                    cursorSelection = 1 ;
                                                }
                                            }
                                        }
                                        else if( inputRecordArrayInner[i].Event.KeyEvent.wVirtualKeyCode == VK_DOWN )
                                        {
                                            if( inputRecordArrayInner[i].Event.KeyEvent.bKeyDown )
                                            {
                                                if( cursorSelection )
                                                {
                                                    niInfo->ciNotrisPauseMenu[cursorY][cursorX].Char.AsciiChar = 0 ;
                                                    niInfo->ciNotrisPauseMenu[cursorY][cursorX].Attributes = 0 ;

                                                    niInfo->ciNotrisPauseMenu[cursorY + 3][cursorX].Char.AsciiChar = 26 ;
                                                    niInfo->ciNotrisPauseMenu[cursorY + 3][cursorX].Attributes = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN ; ;

                                                    cursorSelection = 0 ;
                                                }
                                            }
                                        }
                                        else if( inputRecordArrayInner[i].Event.KeyEvent.wVirtualKeyCode == VK_SPACE )
                                        {
                                            if( inputRecordArrayInner[i].Event.KeyEvent.bKeyDown )
                                            {
                                                if( cursorSelection )
                                                {
                                                    loopBreak = 0 ;
                                                }
                                                // Exits play_notris() and returns to main menu.
                                                else
                                                {
                                                    return 1 ;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            Sleep(50) ;            
                        }
                    }
                }

                else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_MENU )
                {
                    if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                    {
                        if( !notris_check_move_collision( niInfo, piece, VK_MENU) )
                        {
                            notris_rotate_piece_clockwise( piece ) ;
                        }
                    }
                }

                else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_CONTROL )
                {
                    if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                    {
                        if( !notris_check_move_collision( niInfo, piece, VK_CONTROL ) )
                        {
                            notris_rotate_piece_anticlockwise( piece ) ;
                        }
                    }
                }

                else if( inputRecordArray[i].Event.KeyEvent.wVirtualKeyCode == VK_DOWN )
                {
                    if( inputRecordArray[i].Event.KeyEvent.bKeyDown )
                    {
                        if( !notris_check_move_collision( niInfo, piece, VK_DOWN ) )
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
                        if( !notris_check_move_collision( niInfo, piece, VK_LEFT ) )
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
                        if( !notris_check_move_collision( niInfo, piece, VK_RIGHT ) )
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
    DWORD limit ;

    switch( niInfo->level )
    {
        case 1:
            limit = 10 ;
            break ;
        case 2:
            limit = 9 ;
            break ;
        case 3:
            limit = 8 ;
            break ;
        case 4:
            limit = 7 ;
            break ;
        case 5:
            limit = 6 ;
            break ;
        case 6:
            limit = 5 ;
            break ;
        case 7:
            limit = 4 ;
            break ;
    }

    if( !notris_check_axis_collision( niInfo, piece, 1, 'y' ) )
    {
        if( *dwCounter == limit )
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
    niInfo->srPlayFieldArea.Left = ( csbiInfo->srWindow.Right / 2 ) - 5 ;
    niInfo->srPlayFieldArea.Top =  (csbiInfo->srWindow.Bottom / 2) - 10 ;
    niInfo->srPlayFieldArea.Right = ( csbiInfo->srWindow.Right / 2 ) + 5 ;
    niInfo->srPlayFieldArea.Bottom =  (csbiInfo->srWindow.Bottom / 2) + 10 ;

    niInfo->srScoreArea.Left = niInfo->srPlayFieldArea.Right + 2 ;
    niInfo->srScoreArea.Right = niInfo->srScoreArea.Left + 9 ;
    niInfo->srScoreArea.Top = niInfo->srPlayFieldArea.Top ;
    niInfo->srScoreArea.Bottom = niInfo->srScoreArea.Top + 2 ;

    niInfo->srLevelArea.Left = niInfo->srPlayFieldArea.Right + 2 ;
    niInfo->srLevelArea.Right = niInfo->srLevelArea.Left + 4 ;
    niInfo->srLevelArea.Top = niInfo->srScoreArea.Bottom + 2 ;
    niInfo->srLevelArea.Bottom = niInfo->srLevelArea.Top + 2 ;

    niInfo->srNextPieceArea.Left = niInfo->srPlayFieldArea.Right + 2 ;
    niInfo->srNextPieceArea.Right = niInfo->srNextPieceArea.Left + 7 ;
    niInfo->srNextPieceArea.Top = niInfo->srLevelArea.Bottom + 2 ;
    niInfo->srNextPieceArea.Bottom = niInfo->srNextPieceArea.Top + 7 ;

    niInfo->notrisScore = 0 ;

    niInfo->level = 1 ;

    notris_create_bag( niInfo ) ;

    niInfo->nextPiece = niInfo->pieceBag[0] ;

    SHORT bufferWidth = csbiInfo->dwSize.X ;
    SHORT bufferHeight = csbiInfo->dwSize.Y ;

    niInfo->ciNotrisScreenBuffer = ( CHAR_INFO** ) malloc( bufferHeight  * sizeof( CHAR_INFO* ) ) ;
    niInfo->ciNotrisMainMenu = ( CHAR_INFO** ) malloc( bufferHeight  * sizeof( CHAR_INFO* ) ) ;
    niInfo->ciNotrisPauseMenu = ( CHAR_INFO** ) malloc( bufferHeight  * sizeof( CHAR_INFO* ) ) ;
    niInfo->boNotrisCollisionArray = ( BOOL** ) malloc( bufferHeight  * sizeof( BOOL* ) ) ;
    niInfo->boNotrisWriteArray = ( BOOL* ) malloc( bufferHeight * sizeof( BOOL ) ) ;

    for( int i = 0; i < bufferHeight; i++ )
    {
        niInfo->ciNotrisScreenBuffer[i] = ( CHAR_INFO* ) malloc( bufferWidth * sizeof( CHAR_INFO ) ) ;
        niInfo->ciNotrisMainMenu[i] = ( CHAR_INFO* ) malloc( bufferWidth * sizeof( CHAR_INFO ) ) ;
        niInfo->ciNotrisPauseMenu[i] = ( CHAR_INFO* ) malloc( bufferWidth * sizeof( CHAR_INFO ) ) ;
        niInfo->boNotrisCollisionArray[i] = ( BOOL* ) malloc( bufferWidth * sizeof( BOOL ) ) ;
        niInfo->boNotrisWriteArray[i] = 0 ;
    }

    for( int y = 0; y < bufferHeight; y++ )
    {
        for( int x = 0; x < bufferWidth; x++ )
        {
            niInfo->ciNotrisScreenBuffer[y][x].Char.AsciiChar = 0 ;
            niInfo->ciNotrisScreenBuffer[y][x].Attributes = 0 ;
            niInfo->ciNotrisMainMenu[y][x].Char.AsciiChar = 0 ;
            niInfo->ciNotrisMainMenu[y][x].Attributes = 0 ;
            niInfo->ciNotrisPauseMenu[y][x].Char.AsciiChar = 0 ;
            niInfo->ciNotrisPauseMenu[y][x].Attributes = 0 ;
            niInfo->boNotrisCollisionArray[y][x] = 0 ;
        }
    }
}

BOOL play_notris( HANDLE* hScreenBuffer, HANDLE* hInputBuffer, CONSOLE_SCREEN_BUFFER_INFO* csbiInfo, struct notrisInfo* niInfo )
{ 
    DWORD dwDropCounter ;

    CHAR pieceLockDownCounter ;
    CHAR pieceBagPointer = 0 ;

    notris_draw_UI( niInfo ) ;

    while( 1 )
    {
        if( pieceBagPointer == 6 )
        {
            pieceBagPointer = 0 ;
            notris_create_bag( niInfo ) ;
        }

        notrisPiece *p = notris_create_piece( niInfo->nextPiece, niInfo, 
                                           (( niInfo->srPlayFieldArea.Left + niInfo->srPlayFieldArea.Right ) / 2), niInfo->srPlayFieldArea.Top ) ;

        pieceBagPointer++ ;

        niInfo->nextPiece = niInfo->pieceBag[pieceBagPointer] ;

        notris_draw_level( niInfo ) ;

        notris_draw_score( niInfo ) ;

        notris_draw_next( niInfo ) ;

        niInfo->boPieceFalling = 1 ;

        dwDropCounter = 0 ;

        pieceLockDownCounter = 0 ;
       
        while( niInfo->boPieceFalling )
        {   
            // TODO: Compare old vs new collision array to see if needs to be drawn.
            
            notris_erase_piece( niInfo, p ) ;

            if ( notris_piece_falling( &dwDropCounter, niInfo, p ) )
            {
                niInfo->boPieceFalling = 0 ;
            }
            // Exits back to main menu if 1.
            if( notris_move_piece( hScreenBuffer, hInputBuffer, csbiInfo, niInfo, p ) )
            {
                free( p ) ;
                return 1 ;
            }

            // 250ms grace period after piece has collided with floor, allowing for movement and rotation. 
            if( !niInfo->boPieceFalling )
            {
                while( pieceLockDownCounter < 10 )
                {
                    notris_erase_piece( niInfo, p ) ;

                    notris_move_piece(  hScreenBuffer, hInputBuffer, csbiInfo, niInfo, p ) ;

                    notris_draw_piece( niInfo, p ) ;

                    display_buffer( hScreenBuffer, csbiInfo, niInfo->ciNotrisScreenBuffer ) ;

                    if( !notris_check_axis_collision( niInfo, p, 1, 'y' ) )
                    {
                        niInfo->boPieceFalling = 1 ;

                        pieceLockDownCounter = 0 ;

                        break ;
                    }
                    
                    pieceLockDownCounter++ ;

                    Sleep( 25 ) ;
                }
            }
    
            notris_draw_piece( niInfo, p ) ;

            display_buffer( hScreenBuffer, csbiInfo, niInfo->ciNotrisScreenBuffer ) ;

            dwDropCounter++ ;

            Sleep( 50 ) ;
        }

        notris_draw_piece( niInfo, p ) ;

        notris_erase_row( niInfo ) ;

        free( p ) ;
    }
    return 0 ;
}
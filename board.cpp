#include "board.h"

Board::Board(Blocks* pBlock, int pScreenHeight) {
    mBlock = pBlock;
    mScreenHeight = pScreenHeight;
    InitBoard();
}
// Init the board cells with free positions
void Board::InitBoard() {
    for (int i = 0; i < BOARD_WIDTH; i++)
        for (int j = 0; j < BOARD_HEIGHT; j++)
            mBoard[i][j] = POS_FREE;
}

/*
Store a piece in the board by filling the blocks
 
Parameters:
>> cX:        Horizontal position in cells
>> cY:        Vertical position in cells
>> block:     block to draw
>> bRotation: 1 of the 4 possible rotations
*/
void Board::StorePiece (int cX, int cY, int block, int bRotation)
{
    // Store each cell of the block into the board
    for (int i1 = cX, i2 = 0; i1 < cX + CELL_BLOCKS; i1++, i2++) {
        for (int j1 = cY, j2 = 0; j1 < cY + CELL_BLOCKS; j1++, j2++) {   
            // Store only the cells of the block that are not empty
            if (mBlock->GetCellType(block, bRotation, j2, i2) != 0)      
                mBoard[i1][j1] = POS_FILLED;    
        }
    }
}


// Check if the game is over because a block reached the upper bound
bool Board::IsGameOver() {
    // If the first line has anything, then game over
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (mBoard[i][0] == POS_FILLED) return true;
    }
    return false;
}

/* 
Delete a line of the board by moving all above lines down
 
Parameters: 
>> cY:        Vertical position in cells of the line to delete
*/
void Board::DeleteLine (int cY)
{
    // Moves all the upper lines one row down
    for (int j = cY; j > 0; j--) {
        for (int i = 0; i < BOARD_WIDTH; i++) {
            mBoard[i][j] = mBoard[i][j-1];
        }
    }   
}

// Delete all the lines that should be removed
int Board::DeletePossibleLines () {
    int lines{ 0 };
    for (int j = 0; j < BOARD_HEIGHT; j++) {
        int i = 0;
        while (i < BOARD_WIDTH) {
            if (mBoard[i][j] != POS_FILLED) 
                break;
            i++;
        } 
        if (i == BOARD_WIDTH) {
            DeleteLine(j);
            lines++;
        }
    }
    return lines;
}

/*                                
Returns true if the this cell of the board is empty, false if it is filled
 
Parameters:
>> cX:        Horizontal position in cells
>> cY:        Vertical position in cells
*/
bool Board::IsFreeCell (int cX, int cY) {
    if (mBoard [cX][cY] == POS_FREE) 
        return true; 
    else return false;
}

/*                                 
Returns the horizontal position (in pixels) of the cell given like parameter
 
Parameters:
 
>> pPos:  Horizontal position of the cell in the board
*/
int Board::GetXPosInPixels (int pPos) {
    return  ((BOARD_POSITION - (CELL_SIZE * (BOARD_WIDTH / 2))) + (pPos * CELL_SIZE));
}
 
/*                                
Returns the vertical position (in pixels) of the block given like parameter
 
Parameters: 
>> pPos:  Vertical position of the block in the board
*/
int Board::GetYPosInPixels (int pPos) {
    return ((mScreenHeight - (CELL_SIZE * BOARD_HEIGHT)) + (pPos * CELL_SIZE));
}

/* 
Check if the piece can be stored at this position without any collision

Parameters:
>> cX:        Horizontal position in cells
>> cY:        Vertical position in cells
>> block:    Piece to draw
>> bRotation: 1 of the 4 possible rotations
*/

bool Board::IsPossibleMove (int cX, int cY, int block, int bRotation) {
    // Checks collision
    // This is just to check the 5x5 map of the blocks with the current area in the board
    for (int i1 = cX, i2 = 0; i1 < cX + CELL_BLOCKS; i1++, i2++) {
        for (int j1 = cY, j2 = 0; j1 < cY + CELL_BLOCKS; j1++, j2++) {   
            // Check if the block is outside of the board
            if (i1 < 0 || i1 > BOARD_WIDTH  - 1 || j1 > BOARD_HEIGHT - 1) {
                if (mBlock->GetCellType (block, bRotation, j2, i2) != 0)
                    return false;       
            }
            // Check if the block touches anything already on the board
            if (j1 >= 0) {
                if ((mBlock->GetCellType (block, bRotation, j2, i2) != 0) &&
                    (!IsFreeCell (i1, j1)) )
                    return false;
            }
        }
    }
    // No collision
    return true;
}
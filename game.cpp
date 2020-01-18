#include "game.h"
#include <cstdlib>
#include <math.h>
/*
Get a random int between to integers
Parameters:
>> a: First number
>> b: Second number
*/
int Game::GetRand(int a, int b) {
	return rand() % (b - a + 1) + a;
}

// Initial parameters of the game
void Game::InitGame() {
	// Init random numbers
	srand((unsigned int)time(NULL));
	// First block
	block = GetRand(0, 6);
	bRotation = GetRand(0, 3);
	posX = (BOARD_WIDTH / 2) + mBlock->GetXInitialPosition(block, bRotation);
	posY = mBlock->GetYInitialPosition(block, bRotation);

	//  Next block
	nextBlock = GetRand(0, 6);
	nextRotation = GetRand(0, 3);
	nextPosX = BOARD_WIDTH + 5;
	nextPosY = 5;
}

// Create a random block
bool Game::CreateNewBlock() {
	// The new block
	block = nextBlock;
	bRotation = nextRotation;
	posX = (BOARD_WIDTH / 2) + mBlock->GetXInitialPosition(block, bRotation);
	posY = mBlock->GetYInitialPosition(block, bRotation);

	// Random next block
	nextBlock = GetRand(0, 6);
	nextRotation = GetRand(0, 3);
	return true;
}

/*
Draw block

Parameters:
>> cX:        Horizontal position in cells
>> cY:        Vertical position in cells
>> block:     block to draw
>> bRotation: 1 of the 4 possible rotations
*/
void Game::DrawBlock(int cX, int cY, int block, int bRotation) {
	MyColor mColor = MyColor::BLACK;               // Color of the block 

	// Obtain the position in pixel in the screen of the block we want to draw
	int pixelsX = mBoard->GetXPosInPixels(cX);
	int pixelsY = mBoard->GetYPosInPixels(cY);

	// Travel the matrix of blocks of the piece and draw the blocks that are filled
	for (int i = 0; i < CELL_BLOCKS; i++) {
		for (int j = 0; j < CELL_BLOCKS; j++) {
			// Get the type of the block and draw it with the correct color
			switch (mBlock->GetCellType(block, bRotation, j, i)) {
			case 1:
				mColor = MyColor::GREEN;
				break;  // For every cells of the block except the pivot
			case 2:
				mColor = MyColor::BLUE;
				break;   // For the pivot
			}
			if (mBlock->GetCellType(block, bRotation, j, i) != 0)
				mIO->DrawRectangle(pixelsX + i * CELL_SIZE,
					pixelsY + j * CELL_SIZE,
					(pixelsX + i * CELL_SIZE) + CELL_SIZE - 1,
					(pixelsY + j * CELL_SIZE) + CELL_SIZE - 1,
					mColor);
		}
	}
}

// Draw Board
void Game::DrawBoard() {

	// Calculate the limits of the board in pixels  
	int x1 = BOARD_POSITION - (CELL_SIZE * (BOARD_WIDTH / 2)) - 1;
	int x2 = BOARD_POSITION + (CELL_SIZE * (BOARD_WIDTH / 2));
	int y = mScreenHeight - (CELL_SIZE * BOARD_HEIGHT);
	mIO->DrawScore(GetScore(), x1 + (x2 - x1)/2 - 50, y - 5*CELL_SIZE);
	// Check that the vertical margin is not to small
	//assert (y > MIN_VERTICAL_MARGIN);

	// Rectangles that is borders of the board
	mIO->DrawRectangle(x1 - BOARD_LINE_WIDTH, y, x1, mScreenHeight - 1, MyColor::BLUE);

	mIO->DrawRectangle(x2, y, x2 + BOARD_LINE_WIDTH, mScreenHeight - 1, MyColor::BLUE);
	// Check that the horizontal margin is not to small
	// assert (x1 > MIN_HORIZONTAL_MARGIN);

	// Drawing the blocks that are already stored in the board
	x1 += 1;
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			// Check if the block is filled, if so, draw it
			if (!mBoard->IsFreeCell(i, j))
				mIO->DrawRectangle(x1 + i * CELL_SIZE,
					y + j * CELL_SIZE,
					(x1 + i * CELL_SIZE) + CELL_SIZE - 1,
					(y + j * CELL_SIZE) + CELL_SIZE - 1,
					MyColor::RED);
		}
	}
}

Game::Game(Board* pBoard, Blocks* pBlocks, IO* pIO, int pScreenHeight) {
	mBoard = pBoard;
	mBlock = pBlocks;
	mIO = pIO;
	mScreenHeight = pScreenHeight;
	InitGame();
}

// Draw all the objects of the scene
void Game::DrawScene() {
	DrawBoard();                                                   // Draw the borders and blocks stored in the board
	DrawBlock(posX, posY, block, bRotation);                       // Draw the playing block
	DrawBlock(nextPosX, nextPosY, nextBlock, nextRotation);        // Draw the next block
}

int Game::GetScore() {
	return score;
}

void Game::SetScore(int lines) {
	if (lines > 0)
		score += int(pow(2, float(lines) - 1)*BASIC_SCORE);
}


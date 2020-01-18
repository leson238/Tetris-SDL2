#include "Game.h"
#ifndef LINUX
#include <windows.h>
#include <iostream>
#endif

// Main 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	IO pIO;
	int mScreenHeight = pIO.GetScreenHeight();

	// Blocks
	Blocks block;

	// Board
	Board mBoard(&block, mScreenHeight);

	// Game
	Game mGame(&mBoard, &block, &pIO, mScreenHeight);

	unsigned long mTime1 = SDL_GetTicks();

	// Game Loop
	while (!pIO.IsKeyDown(SDLK_ESCAPE)) {
		int lines{ 0 };
		pIO.ClearScreen();
		mGame.DrawScene();
		pIO.UpdateScreen();
		std::cout << mGame.GetScore() << std::endl;
		int mKey = pIO.PollKey();
		switch (mKey) {
		case SDLK_RIGHT:
		case SDLK_d:
		{
			if (mBoard.IsPossibleMove(mGame.posX + 1, mGame.posY, mGame.block, mGame.bRotation))
				mGame.posX++;
			break;
		}

		case SDLK_LEFT:
		case SDLK_a:
		{
			if (mBoard.IsPossibleMove(mGame.posX - 1, mGame.posY, mGame.block, mGame.bRotation))
				mGame.posX--;
			break;
		}

		case SDLK_DOWN:
		case SDLK_s:
		{
			if (mBoard.IsPossibleMove(mGame.posX, mGame.posY + 1, mGame.block, mGame.bRotation))
				mGame.posY++;
			break;
		}

		case SDLK_SPACE:
		{
			// Check collision from up to down
			while (mBoard.IsPossibleMove(mGame.posX, mGame.posY, mGame.block, mGame.bRotation)) { mGame.posY++; }

			mBoard.StorePiece(mGame.posX, mGame.posY - 1, mGame.block, mGame.bRotation);

			lines = mBoard.DeletePossibleLines();
			mGame.SetScore(lines);
			if (mBoard.IsGameOver()) {
				pIO.GetKey();
				exit(0);
			}
			mGame.CreateNewBlock();

			break;
		}
		case SDLK_UP:
		case SDLK_z:
		{
			if (mBoard.IsPossibleMove(mGame.posX, mGame.posY, mGame.block, (mGame.bRotation + 1) % 4))
				mGame.bRotation = (mGame.bRotation + 1) % 4;

			break;
		}
		}
		// ----- Vertical movement -----


		unsigned long mTime3 = SDL_GetTicks();
		if ((mTime3 - mTime1) > WAIT_TIME) {
			if (mBoard.IsPossibleMove(mGame.posX, mGame.posY + 1, mGame.block, mGame.bRotation)) {
				mGame.posY++;
			}
			else {
				mBoard.StorePiece(mGame.posX, mGame.posY, mGame.block, mGame.bRotation);

				lines = mBoard.DeletePossibleLines();
				mGame.SetScore(lines);
				if (mBoard.IsGameOver()) {
					pIO.GetKey();
					exit(0);
				}

				mGame.CreateNewBlock();
			}

			mTime1 = SDL_GetTicks();
		}
	}

	return 0;
}

// ------ Includes -----

#include "IO.h"
#include <cstdlib>
static Uint32 pixels[480 * 640];

static Uint32 mColors[8] = { 0x000000ff,					// Colors
							   0xff0000ff, 0x00ff00ff, 0x0000ffff,
							   0x00ffffff, 0xff00ffff, 0xffff00ff,
							   0xffffffff };

/*
======================================
Init
======================================
*/
IO::IO() {
	InitGraph();
}


/*
Clear the screen to black
*/
void IO::ClearScreen() {
	SDL_Rect r1;
	r1.x = 0;
	r1.y = 0;
	r1.w = 480;
	r1.h = 640;
	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
	SDL_RenderFillRect(sdlRenderer, &r1);
}


/*
Draw a rectangle of a given color

Parameters:
>> pX1, pY1: 		Upper left corner of the rectangle
>> pX2, pY2: 		Lower right corner of the rectangle
>> pC				Rectangle color
*/
void IO::DrawRectangle(int pX1, int pY1, int pX2, int pY2, MyColor pC) {
	SDL_Rect r;
	r.x = pX1;
	r.y = pY1;
	r.w = pX2 - pX1;
	r.h = pY2 - pY1;
	for (int i = 0; i < 480 * 640; i++)
		pixels[i] = mColors[int(pC)];
	SDL_UpdateTexture(sdlTexture, NULL, pixels, 480);
	SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &r);
}


// Return screen height
int IO::GetScreenHeight() {
	int h;
	SDL_GetWindowSize(sdlWindow, NULL, &h);
	return h;
}


// Update screen
void IO::UpdateScreen() {
	SDL_RenderPresent(sdlRenderer);
	SDL_RenderClear(sdlRenderer);
}


// Keyboard input
int IO::PollKey() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			return event.key.keysym.sym;
		case SDL_QUIT:
			exit(3);
		}
	}
	return -1;
}

// Keyboard input
int IO::GetKey() {
	SDL_Event event;
	while (true) {
		SDL_WaitEvent(&event);
		if (event.type == SDL_KEYDOWN)
			break;
		if (event.type == SDL_QUIT)
			exit(3);
	};
	return event.key.keysym.sym;
}

// Keyboard input
int IO::IsKeyDown(int pKey) {
	const Uint8* mKeytable;
	int mNumkeys;
	SDL_PumpEvents();
	mKeytable = SDL_GetKeyboardState(&mNumkeys);
	return mKeytable[pKey];
}

// Graphic initialization
int IO::InitGraph() {
	sdlWindow = SDL_CreateWindow("Game",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		480, 640,
		SDL_WINDOW_RESIZABLE);
	sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	sdlTexture = SDL_CreateTexture(sdlRenderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STATIC,
		480, 640);

	return 0;
}

IO::~IO() {
	SDL_DestroyRenderer(sdlRenderer);
	SDL_DestroyWindow(sdlWindow);
}

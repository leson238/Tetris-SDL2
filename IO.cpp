// ------ Includes -----

#include "IO.h"
#include <cstdlib>
#include <string>

static Uint32 pixels[480 * 640];

static short mColors[8][4] = { {0,0,0,255},{255,0,0,255}, {0,255,0,255}, {0,0,255,255}, {255,255,0,255}, {0,255,255,255}, {255,0,255,255}, {255,255,255,255} };

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
	/*
	
	*/
	SDL_Rect r;
	r.x = pX1;
	r.y = pY1;
	r.w = pX2 - pX1;
	r.h = pY2 - pY1;
	SDL_SetRenderDrawColor(sdlRenderer, mColors[int(pC)][0], mColors[int(pC)][1], mColors[int(pC)][2], mColors[int(pC)][3]);
	SDL_RenderFillRect(sdlRenderer, &r);
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
	sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
	SDL_RenderClear(sdlRenderer);
	return 0;
}

void IO::DrawInformation(std::string description, int information, int cX, int cY) {
	if (TTF_Init() == -1) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"Not init",
			TTF_GetError(),
			NULL);
	}
	TTF_Font* Calibri = TTF_OpenFont("C:\\Windows\\Fonts\\Calibri.ttf", 24);
	if (!Calibri) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"Missing file",
			"Font is missing. Please reinstall the program.",
			NULL);
	}
	SDL_Color ORANGE = { 255,0,255 };
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Calibri, (description + std::to_string(information)).c_str(), ORANGE);
	sdlTexture = NULL;
	sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer, surfaceMessage);

	SDL_Rect Message_rect;
	Message_rect.x = cX;
	Message_rect.y = cY;
	Message_rect.w = 100;
	Message_rect.h = 20;

	SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &Message_rect); 
	SDL_FreeSurface(surfaceMessage);
}

IO::~IO() {
	SDL_DestroyRenderer(sdlRenderer);
	SDL_DestroyTexture(sdlTexture);
	SDL_DestroyWindow(sdlWindow);
}

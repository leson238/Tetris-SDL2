#ifndef _IO_
#define _IO_

// ------ Includes -----

#include "SDL.h"	
#include "SDL_ttf.h"
#include <string>


enum class MyColor : unsigned char { BLACK = 8, RED = 7, GREEN = 6, BLUE = 5, CYAN = 4, MAGENTA = 3, YELLOW = 2, WHITE = 1 }; // Colors


// --------------------------------------------------------------------------------
//									 IO
// --------------------------------------------------------------------------------

class IO {
public:
	SDL_Window* sdlWindow;
	SDL_Renderer* sdlRenderer;
	SDL_Texture* sdlTexture;


	IO();
	~IO();

	void DrawRectangle			(int pX1, int pY1, int pX2, int pY2, MyColor pC);
	void DrawInformation		(std::string description, int information, int cX, int cY);
	void ClearScreen			();
	int GetScreenHeight			();
	int InitGraph				();
	int PollKey					();
	int GetKey					();
	int IsKeyDown				(int pKey);
	void UpdateScreen			();
};

#endif // _IO_

#ifndef _GAME
#define _GAME
 
// ------ Includes -----
 
#include "board.h"
#include "blocks.h"
#include "IO.h"
#include <time.h>
 
// ------ Defines -----
 
#define WAIT_TIME 700          // Number of milliseconds that the block remains before going 1 cell down */ 
 
 
// --------------------------------------------------------------------------------
//                                   Game
// --------------------------------------------------------------------------------
 
class Game {
public:
    Game                (Board *pBoard, Blocks *pBlocks, IO *pIO, int pScreenHeight);
 
    void DrawScene      ();
    bool CreateNewBlock ();
    
    int posX, posY;               // Position of the block that is falling down
    int block, bRotation;         // Type and rotation the block that is falling down
 
private:
 
    int mScreenHeight;             // Screen height in pixels
    int nextPosX, nextPosY;        // Position of the next piece
    int nextBlock, nextRotation;   // Type and rotation of the next piece


    Board *mBoard;
    Blocks *mBlock;
    IO *mIO;

    int  GetRand    (int pA, int pB);
    void InitGame   ();
    void DrawBlock  (int pX, int pY, int block, int bRotation);
    void DrawBoard  ();
};
 
#endif // _GAME
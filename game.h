#ifndef _GAME
#define _GAME
 
// ------ Includes -----
 
#include "board.h"
#include "blocks.h"
#include "IO.h"
#include <time.h>
#include <string>
 
// ------ Defines -----
 
#define BASIC_SCORE 10 
 
// --------------------------------------------------------------------------------
//                                   Game
// --------------------------------------------------------------------------------
 
class Game {
public:
    Game                (Board *pBoard, Blocks *pBlocks, IO *pIO, int pScreenHeight);
 
    void DrawScene      ();
    bool CreateNewBlock ();
    int GetScore        ();
    void SetScore       (int lines);
    int GetLevel        ();
    void SetLevel       (int total_lines);
    int GetWaitTime     ();
    void SetWaitTime    ();


    int posX, posY;               // Position of the block that is falling down
    int block, bRotation;         // Type and rotation the block that is falling down
 
private:
    int level{ 1 };                //Level 
    int waitTime{ 700 };           //The wait time before the block going down 1 cell
    int score{ 0 };                // Score
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
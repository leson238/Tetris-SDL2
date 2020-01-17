#ifndef _BLOCKS
#define _BLOCKS
 
 
// Blocks
 
class Blocks {
public:
    int GetCellType         (int block, int bRotation, int bX, int bY);
    int GetXInitialPosition (int block, int bRotation);
    int GetYInitialPosition (int block, int bRotation);
};
 
#endif // _Blocks
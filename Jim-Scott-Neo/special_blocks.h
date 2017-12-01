#ifndef SPECIAL_BLOCKS_H
#define SPECIAL_BLOCKS_H
#include "block.h"

class IBlock :public Block
{
private:
    void iRotate();
public:
    IBlock(int, Cell*);

    void rRotate() override;
    void lRotate() override;

};

class OBlock :public Block
{
public:
    OBlock(int, Cell*);

    void rRotate() override;
    void lRotate() override;
};
#endif


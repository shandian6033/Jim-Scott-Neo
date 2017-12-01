
#ifndef NORMAL_BLOCKS_H
#define NORMAL_BLOCKS_H
#include "block.h"

class SBlock : public Block
{
public:
    SBlock(int, Cell*);
};

class ZBlock : public Block
{
public:
    ZBlock(int, Cell*);
};

class LBlock : public Block
{
public:
    LBlock(int, Cell*);
};

class JBlock : public Block
{
public:
    JBlock(int, Cell*);
};

class TBlock : public Block
{
public:
    TBlock(int, Cell*);
};

#endif // !NORMAL_BLOCKS_H


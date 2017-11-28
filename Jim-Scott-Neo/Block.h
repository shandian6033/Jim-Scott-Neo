#ifndef BLOCK_H
#define BLOCK_H

#include<vector>
#include"subject.h"
using namespace std;

class Cell;

/* 
example:
  0 1 2 3 4 5
a - L - - - - 
b - L - - - -
c - L L - - -
d - - - - - -
e - - - - - -

Cell* anchor points at a1
Range of the LBlock spans form a1 to c3

cellAt(anchor,1,2) = cell* b3
cellAt(anchor,0,-1) = cell* a0
cellAt(anchor,-1,3) = nullptr,(a-1)4

*/


class Block: public Subject
{
private:
    
protected:
    Cell *anchor;
    Cell* cellAt(Cell* ,int, int); 
public:
    virtual void left() = 0;
    virtual void right() = 0;
    virtual void down() = 0;
    virtual void drop() = 0;
        
    virtual void rRotate() = 0;
    virtual void lRotate() = 0;
};


class LBlock: public Block
{
private:
    vector<vector<WhoIam>> small_grid;
public:
    void left()override;
    void right() override;
    void down() override;
    void drop() override;

    void rRotate() override;
    void lRotate() override;


};

#endif

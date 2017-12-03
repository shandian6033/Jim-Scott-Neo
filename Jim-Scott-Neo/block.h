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


class Block
{
private:
    //danger! hard coded for 3*3 blocks, I block and O block need their own fns
    // intergrad both right and left rotate
	const int level;
    vector<vector<WhoIam>> ifRotated(bool);
    void eraseCheck(int& score, int& count);
protected:
    Cell* anchor;
    WhoIam my_type;
    vector<vector<WhoIam>> small_grid;
    bool is_successful; //the block is successfully generated or not, usd to check gameover

     //can erase the original type or set new type;
public:

	Block(int, Cell*, WhoIam); ;

    virtual void left();
    virtual void right();
    virtual void down();
    virtual int drop(); //return total score earns
        
    virtual void rRotate();
    virtual void lRotate();

	vector<vector<WhoIam>> getGrid()const;
	void setGrid(vector<vector<WhoIam>>);
	Cell* getAnchor()const;
	void setAnchor(Cell*);
	void setH();
	WhoIam getid()const;
    void modifyCellsUnderGrid(bool is_erase) const;
    bool isSuccessful();
};

Cell* cellAt(Cell*, int, int);
bool canFit(Cell* anchor,const vector<vector<WhoIam>>& compare_with);


#endif

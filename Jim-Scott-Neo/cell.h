#ifndef CELL_H
#define CELL_H
#include "subject.h"

class Cell:public Subject{
	const int r, c;
	int living_time, worth;
	WhoIam id;

	Cell* left;
	Cell* right;
	Cell* up;
	Cell* down;

	bool isRightClear()const;
	bool isLeftClear() const;
	bool isRowClear() const { return this->isRightClear() && this->isLeftClear() && this->id != WhoIam::Null; }
    //only WhoIam::I,O,J,Z,S,T,L,Null  will call this.
    //this fn will recursively call upper cell.upCopy()
    int upCopy();//return score earned by eliminating block
public:
    Cell(int, int);

	void setLeft(Cell &);
	void setRight(Cell &);
	void setUp(Cell &);
	void setDown(Cell &);
	void setPiece(WhoIam new_id, int level); //will only Block and Cell call this function

    Cell* getLeft()const;
    Cell* getRight()const;
    Cell* getUp()const;
    Cell* getDown()const;

	int age()const;
	void grow();
    int eraseRow(); //erase the entire row if possible and return score earned by eliminate block
	Info getInfo() const override;
};


#endif

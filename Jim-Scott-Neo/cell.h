#ifndef CELL_H
#define CELL_H
#include "subject.h"

class Cell:public Subject{
	const int r, c;
	int living_time;
	WhoIam id;

	Cell* left;
	Cell* right;
	Cell* up;
	Cell* down;

	bool isRightClear()const;
	bool isLeftClear() const;
    bool isRowClear() const { return this->isRightClear() && this->isLeftClear(); }
    //only WhoIam::I,O,J,Z,S,T,L,Null  will call this.
    //this fn will recursively call upper cell.upCopy()
    void upCopy();
public:
    Cell(int, int);

	void setLeft(Cell &);
	void setRight(Cell &);
	void setUp(Cell &);
	void setDown(Cell &);
	void setPiece(WhoIam); //will only Block and Cell call this function

    Cell* getLeft()const;
    Cell* getRight()const;
    Cell* getUp()const;
    Cell* getDown()const;

    void eraseRow(); //erase the entire row if possible
	Info getInfo() const override;
};


#endif

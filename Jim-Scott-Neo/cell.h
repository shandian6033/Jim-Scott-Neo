#ifndef  CELL_H
#define CELL_H
#include "subject.h"

class Cell:public Subject{
	int r, c, living_time;
	WhoIam id;

	Cell* left;
	Cell* right;
	Cell* up;
	Cell* down;

public:
    Cell(int, int);

    void setPiece(WhoIam);
    void upCopy();
	bool isRightClear();
	bool isLeftClear();
	bool isRowClear() { return this->isRightClear() && this->isLeftClear(); }

	Info getInfo() const override;

};


#endif

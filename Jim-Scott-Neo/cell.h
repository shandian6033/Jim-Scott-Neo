#ifndef  CELL_H
#define CELL_H
#include "observer.h"
#include "subject.h"

class cell:public Subject{
	int r, c, living_time;
	WhoIam id;

	cell* left;
	cell* right;
	cell* up;
	cell* down;

public:
    cell(int, int);

    void setPiece(WhoIam);
    void upCopy();
	bool isRightClear();
	bool isLeftClear();
	bool isRowClear() { return this->isRightClear() && this->isLeftClear(); }

	Info getInfo() const override;

};
#endif



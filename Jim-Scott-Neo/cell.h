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
	void isRowClear();

	Info getInfo() const override;

};
#endif



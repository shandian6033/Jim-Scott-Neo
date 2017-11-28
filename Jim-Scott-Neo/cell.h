#ifndef  CELL_H
#define CELL_H
#include "observer.h"
#include "subject.h"
class cell
{
	int r, c, living_time;
	WhoIam id;

	cell* left;
	cell* right;
	cell* up;
	cell* down;

public:
    cell(int, int);

    void SetPiece(char);
    void UpCopy();

    

};
#endif



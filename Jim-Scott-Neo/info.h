#ifndef INFO_H
#define INFO_H

//Info contains all information of a cell, including position, shape, living_time...
enum class WhoIam { O, J, L, S, Z, I, T, Null, Block };

struct Info {
	int row, col, living_time;
	WhoIam id;
};

#endif // !INFO_H


#ifndef INFO_H
#define INFO_H

//Info contains all information of a cell, including position, shape, living_time...
enum class Shape { O, J, L, S, Z, I, T, Null };

struct Info {
	int row, col, living_time;
	Shape shape;
};

#endif // !INFO_H


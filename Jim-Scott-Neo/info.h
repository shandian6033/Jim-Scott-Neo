#ifndef INFO_H
#define INFO_H

//Info contains all information of a cell, including position, shape, living_time...
enum class WhoIam { O, J, L, S, Z, I, T, Null, Block };

struct CmdList {
	string left = "left";
	string right = "right";
	string down = "down";
	string drop = "drop";

	string rRotate = "clockwise";
	string lRotate = "counterclockwise";

	string levelup = "levelup";
	string leveldown = "leveldown";
	string norandom = "norandom";
	string random = "random";
	string restart = "restart";
	string hint = "hint";
	string sequence = "sequence";

	string quit = "quit";
};

struct Info {
	int row, col, living_time;
	WhoIam id;
};

#endif // !INFO_H


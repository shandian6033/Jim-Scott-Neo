#ifndef INFO_H
#define INFO_H
#include <string>
enum class WhoIam { O, J, L, S, Z, I, T, X, Null, Placeholder};

struct CmdList {
	std::string left = "left";
	std::string right = "right";
	std::string down = "down";
	std::string drop = "drop";

	std::string rRotate = "clockwise";
	std::string lRotate = "counterclockwise";

	std::string levelup = "levelup";
	std::string leveldown = "leveldown";
	std::string norandom = "norandom";
	std::string random = "random";
	std::string restart = "restart";
	std::string hint = "hint";
	std::string sequence = "sequence";

	std::string quit = "quit";
};

struct Info {
	int row, col, living_time;
	WhoIam id;
};

#endif // !INFO_H


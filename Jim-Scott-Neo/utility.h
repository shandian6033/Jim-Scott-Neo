#ifndef UTILITY_H
#define UTILITY_H
#include <string>
#include <string.h>
#include "info.h"
void readCmd(std::string original_cmd, std::string string_cmd,std::string &valid_cmd, CmdList &changable_cmd) {
	
	//string_cmd may need be modified
	if (original_cmd == "I" || original_cmd == "J" || original_cmd == "L") {
		valid_cmd = original_cmd;
	}
	else if (strncmp(changable_cmd.left.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//left
		valid_cmd = changable_cmd.left;
	}
	else if (strncmp(changable_cmd.right.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//right
		valid_cmd = changable_cmd.right;
	}
	else if (strncmp(changable_cmd.down.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//down
		valid_cmd = changable_cmd.down;
	}
	else if (strncmp(changable_cmd.drop.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//drop
		valid_cmd = changable_cmd.drop;
	}
	else if (strncmp(changable_cmd.lRotate.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//lRotate
		valid_cmd = changable_cmd.lRotate;
	}
	else if (strncmp(changable_cmd.rRotate.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//rRotate
		valid_cmd = changable_cmd.rRotate;
	}
	else if (strncmp(changable_cmd.levelup.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//levelup
		valid_cmd = changable_cmd.levelup;
	}
	else if (strncmp(changable_cmd.leveldown.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//leveldown
		valid_cmd = changable_cmd.leveldown;
	}
	else if (strncmp(changable_cmd.norandom.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//norandom
		valid_cmd = changable_cmd.norandom;
	}
	else if (strncmp(changable_cmd.random.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//random
		valid_cmd = changable_cmd.random;
	}
	else if (strncmp(changable_cmd.restart.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//restart
		valid_cmd = changable_cmd.restart;
	}
	else if (strncmp(changable_cmd.hint.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//hint
		valid_cmd = changable_cmd.hint;
	}
	else if (strncmp(changable_cmd.sequence.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//sequence
		valid_cmd = changable_cmd.sequence;
	}
	else if (strncmp(changable_cmd.quit.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//quit
		valid_cmd = changable_cmd.quit;
	}
	else {
		valid_cmd = string_cmd;
	}
}

void setName(std::string old, std::string new_name, CmdList &myCmd) {
	if (old == myCmd.down)myCmd.down = new_name;
	else if (old == myCmd.drop)myCmd.drop = new_name;
	else if (old == myCmd.left)myCmd.left = new_name;
	else if (old == myCmd.right)myCmd.right = new_name;
	else if (old == myCmd.rRotate)myCmd.rRotate = new_name;
	else if (old == myCmd.lRotate)myCmd.lRotate = new_name;
	else if (old == myCmd.levelup)myCmd.levelup = new_name;
	else if (old == myCmd.leveldown)myCmd.leveldown = new_name;
	else if (old == myCmd.norandom)myCmd.norandom = new_name;
	else if (old == myCmd.random)myCmd.random = new_name;
	else if (old == myCmd.restart)myCmd.restart = new_name;
	else if (old == myCmd.hint)myCmd.hint = new_name;
	else if (old == myCmd.sequence)myCmd.sequence = new_name;
	else if (old == myCmd.rename)myCmd.rename = new_name;
	else if (old == myCmd.quit)myCmd.quit = new_name;
}
#endif // !UTILITY_H


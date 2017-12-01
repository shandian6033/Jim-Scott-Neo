#include"board.h"
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
using namespace std;


int main(int argc, char* argv[])
{
    //reading flags commands
	Board b;
	int row = 15;
	int col = 11;
	b.init(row, col);
	b.setLevel(1);

    for (int i = 1; i < argc; i++) {
        string flag = argv[i];
        //cout << flag << endl;
        if (flag == "-text") {
            // impliment for only text display (no graphic display)
        }
        else if (flag == "-seed") {
            string temp = argv[i+1];
            stringstream iss { temp };
            int seed;
            if (iss >> seed) {
                //set seed
                i++;
            }
            else cerr << "please enter valid seed" << endl;
        }
        else if (flag == "-scriptfile"){
            string file_name = argv[i + 1];
            //set order of generated block using file_name
            i++;
        }
        else if (flag == "-statlevel") {
            string temp = argv[i + 1];
            stringstream iss{ temp };
            int level;
            if (iss >> level) {
                //set the seed using ""
                i++;
            }
            else cerr << "please enter valid level" <<endl;
        }
    }
    // runtime commands
    string original_cmd;
	string string_cmd;
	string valid_cmd;
	int n;
    while (!cin.eof()) {

		//seperate command time and command
		cin >> original_cmd;
		stringstream(original_cmd) >> n;
		std::string s = std::to_string(n);
		int digit = s.length();
		if (n != 0)stringstream(original_cmd).ignore(digit) >> string_cmd;
		else { 
			if (original_cmd.at(0) == '0')continue; //should start reading new cmd
			else {
				stringstream(original_cmd) >> string_cmd;
				n = 1;
			}
		}
		//seperated
		//string_cmd may need be modified
		if (original_cmd == "I" || original_cmd == "J" || original_cmd == "L") {
			valid_cmd = original_cmd;
		}
		else if (strncmp(b.changable_cmd.left.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//left
			valid_cmd = b.changable_cmd.left;
		}
		else if (strncmp(b.changable_cmd.right.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//right
			valid_cmd = b.changable_cmd.right;
		}
		else if (strncmp(b.changable_cmd.down.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//down
			valid_cmd = b.changable_cmd.down;
		}
		else if (strncmp(b.changable_cmd.drop.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//drop
			valid_cmd = b.changable_cmd.drop;
		}
		else if (strncmp(b.changable_cmd.lRotate.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//lRotate
			valid_cmd = b.changable_cmd.lRotate;
		}
		else if (strncmp(b.changable_cmd.rRotate.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//rRotate
			valid_cmd = b.changable_cmd.rRotate;
		}
		else if (strncmp(b.changable_cmd.levelup.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//levelup
			valid_cmd = b.changable_cmd.levelup;
		}
		else if (strncmp(b.changable_cmd.leveldown.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//leveldown
			valid_cmd = b.changable_cmd.leveldown;
		}
		else if (strncmp(b.changable_cmd.norandom.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//norandom
			valid_cmd = b.changable_cmd.norandom;
		}
		else if (strncmp(b.changable_cmd.random.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//random
			valid_cmd = b.changable_cmd.random;
		}
		else if (strncmp(b.changable_cmd.restart.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//restart
			valid_cmd = b.changable_cmd.restart;
		}
		else if (strncmp(b.changable_cmd.hint.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//hint
			valid_cmd = b.changable_cmd.hint;
		}
		else if (strncmp(b.changable_cmd.sequence.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//sequence
			valid_cmd = b.changable_cmd.sequence;
		}
		else if (strncmp(b.changable_cmd.quit.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//quit
			valid_cmd = b.changable_cmd.quit;
		}
		//modified

		if (valid_cmd == b.changable_cmd.norandom) {} //impliment when we have level 3,4 //norandom
		else if (valid_cmd == b.changable_cmd.random) {}//random

		else if (valid_cmd == "I" || valid_cmd == "J" || valid_cmd == "L") {}

		else if (valid_cmd == b.changable_cmd.restart) {//restart
			b.init(row, col);
		} // impliment first

		else if (valid_cmd == b.changable_cmd.hint) {} //impliment last

		else if (string_cmd == "quit") break;
		else {
			for (int i = 0; i < n; i++) {
				if (valid_cmd == b.changable_cmd.left || valid_cmd == b.changable_cmd.right || valid_cmd == b.changable_cmd.down  ||
					valid_cmd == b.changable_cmd.rRotate || valid_cmd == b.changable_cmd.lRotate) { // impliment first
					b.movement(valid_cmd);
				}
				else if (valid_cmd == b.changable_cmd.drop) {
					b.movement(valid_cmd);
					b.nextBlock(b.getLevel());
					if (!b.setCur())break;//game over here. You lose.
				}
				else if (valid_cmd == "levelup") {}
				else if (valid_cmd == "leveldown") {}

				else if (string_cmd == "sequence") {} //impliment for testing purpose

				else {}; //error message here
			}
		}
		cout << b;
    }

}
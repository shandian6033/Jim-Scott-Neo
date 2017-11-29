#include"board.h"
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
using namespace std;


int main(int argc, char* argv[])
{
    //reading flags commands
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
	Board b;
    while (!cin.eof()) {

		//seperate command time and command
		cin >> original_cmd;
		stringstream(original_cmd) >> n;
		std::string s = std::to_string(n);
		int digit = s.length();
		if (n != 0)stringstream(original_cmd).ignore(digit) >> string_cmd;
		else { 
			stringstream(original_cmd) >> string_cmd;
			n = 1;
		}
		//seperated
		//string_cmd may need be modified
		if (strncmp(b.changable_cmd.left.c_str(), string_cmd.c_str(), strlen(string_cmd.c_str())) == 0) {//left
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
		//modified
		for (int i = 0; i < n; i++) {
			if (valid_cmd == b.changable_cmd.left || valid_cmd == b.changable_cmd.right || valid_cmd == b.changable_cmd.down ||
				valid_cmd == b.changable_cmd.drop || valid_cmd == b.changable_cmd.rRotate || valid_cmd == b.changable_cmd.lRotate) { // impliment first
				//Board.Movement(cmd);
			}
			else if (valid_cmd == "levelup") {}
			else if (valid_cmd == "leveldown") {}

			else if (string_cmd == "norandom") {} //impliment when we have level 3,4
			else if (string_cmd == "random") {}

			else if (string_cmd == "sequence file") {} //impliment for testing purpose
			else if (string_cmd == "I" || string_cmd == "J" || string_cmd == "L") {}

			else if (string_cmd == "restart") {} // impliment first

			else if (string_cmd == "hint") {} //impliment last

			else if (string_cmd == "quit") break;
			else {}; //error message here
		}

    }

}
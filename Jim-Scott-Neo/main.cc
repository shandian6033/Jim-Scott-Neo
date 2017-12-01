#include"board.h"
#include "utility.h"
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
	b.computeNextBlock();
	b.setCur();
	//b.computeNextBlock();

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

	cout << b;
    while (!cin.eof()) {
		int n = 0;
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
		readCmd(original_cmd, string_cmd, valid_cmd, b.changable_cmd);


		bool isOver = false;
		if (valid_cmd == b.changable_cmd.norandom) {//norandom
			string file;
			cin >> file;
			if (!b.setSeq(file)) {
				cout << "invalid file" << endl;
				continue;
			}
		} //impliment when we have level 3,4 
		else if (valid_cmd == b.changable_cmd.random) {}//random

		else if (valid_cmd == "I" || valid_cmd == "J" || valid_cmd == "L") {}

		else if (valid_cmd == b.changable_cmd.restart) {//restart
			b.init(row, col);
		} // impliment first

		else if (valid_cmd == b.changable_cmd.hint) {} //impliment last

		else if (valid_cmd == b.changable_cmd.sequence) { //sequence
			string file;
			cin >> file;
			if (!b.setSeq(file)) {
				cout << "invalid file" << endl;
				continue;
			}
		} //impliment for testing purpose

		else if (string_cmd == "quit") break;
		else {
			bool notvalid = false;
			for (int i = 0; i < n; i++) {
				if (valid_cmd == b.changable_cmd.left || valid_cmd == b.changable_cmd.right || valid_cmd == b.changable_cmd.down  ||
					valid_cmd == b.changable_cmd.rRotate || valid_cmd == b.changable_cmd.lRotate) { // impliment first
					b.movement(valid_cmd);
				}
				else if (valid_cmd == b.changable_cmd.drop) {
					b.movement(valid_cmd);
					if (!b.setCur()) {
						isOver = true;
						break;
					}//game over here. You lose.
				}
				else if (valid_cmd == "levelup") {}
				else if (valid_cmd == "leveldown") {}

				else {//invalid cmd
					notvalid = true;
					break;
				}; 
			}

			if (notvalid) {//invalid msg here
				continue;
			}
		}
		if (isOver) {
			cout << "game over" << endl;
		}
		else { cout << b; }
    }

}
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
	string file_name;
	Board b;
	int row = 15;
	int col = 11;
	b.setLevel(0);
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
				srand(seed);
                i++;
            }
            else cerr << "please enter valid seed" << endl;
        }
        else if (flag == "-scriptfile"){
            file_name = argv[i + 1];
			b.setSeq(file_name);
            i++;
        }
        else if (flag == "-statlevel") {
            string temp = argv[i + 1];
            stringstream iss{ temp };
            int level;
            if (iss >> level) {
				b.setLevel(level);
                i++;
            }
            else cerr << "please enter valid level" <<endl;
        }
    }
    // runtime commands
    string original_cmd;
	string string_cmd;
	string valid_cmd;

	//game start here
	b.init(row, col);
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
		if (valid_cmd == b.changable_cmd.norandom) { //impliment when we have level 3,4 //nonrandom
			/*string file;
			cin >> file;*/
			if (!b.setSeq(file_name)) {
				cout << "invalid file" << endl;
				continue;
			}
		}  
		else if (valid_cmd == b.changable_cmd.random) {}//random

		else if (valid_cmd == "I" || valid_cmd == "J" || valid_cmd == "L") {}

		else if (valid_cmd == b.changable_cmd.restart) {//restart
			b.init(row, col);
		} // impliment first

		else if (valid_cmd == b.changable_cmd.hint) {} //impliment last

		else if (valid_cmd == b.changable_cmd.sequence) { //sequence
			cin >> file_name;
			if (!b.setSeq(file_name)) {
				cout << "invalid file" << endl;
				continue;
			}
		} //impliment for testing purpose

		else if (string_cmd == b.changable_cmd.quit) break;
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
				else if (valid_cmd == b.changable_cmd.levelup) { b.setLevel(b.getLevel() + 1); } //level up
				else if (valid_cmd == b.changable_cmd.leveldown) { b.setLevel(b.getLevel() - 1); } //level down

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
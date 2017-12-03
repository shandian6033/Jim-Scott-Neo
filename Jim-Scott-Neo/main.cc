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
	string file_name = "seqeunce.txt";
	Board b;
	int row = 15;
	int col = 11;
	
    for (int i = 1; i < argc; i++) {
        string flag = argv[i];
        //cout << flag << endl;
        if (flag == "-text") {
            b.has_graphic = false;
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
			if (b.getLevel() != 0)b.setSeq(file_name);
            i++;
        }
        else if (flag == "-startlevel") {
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
    b.init(row, col);

    // runtime commands
    string original_cmd;
	string string_cmd;
	string valid_cmd;

	ifstream in;
	//game start here
	if (b.getLevel() == 0) {
		if (!b.setSeq(file_name))cout << "cannot find sequence.txt" << endl;
	}
	b.restart();
	cout << b;
    while (true) {
		int n = 0;
		//read command
		if (in >> original_cmd) {}
		else {
			cin >> original_cmd;
			if (cin.eof())break;
		}
		//seperate command time and command
		stringstream(original_cmd) >> n;
		std::string s = std::to_string(n);
		int digit = static_cast<int>(s.length());
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


		if (string_cmd == "I") {
			b.changeBlock(WhoIam::I);
		}
		else if (string_cmd == "L") {
			b.changeBlock(WhoIam::L);
		}
		else if (string_cmd == "J") {
			b.changeBlock(WhoIam::J);
		}
		else if (string_cmd == "Z") {
			b.changeBlock(WhoIam::Z);
		}
		else if (string_cmd == "S") {
			b.changeBlock(WhoIam::S);
		}
		else if (string_cmd == "O") {
			b.changeBlock(WhoIam::O);
		}
		else if (string_cmd == "T") {
			b.changeBlock(WhoIam::T);
		}
		else if (valid_cmd == b.changable_cmd.norandom) { //impliment when we have level 3,4 //nonrandom
			if (!(in >> file_name))cin >> file_name;
			if (!b.setSeq(file_name)) {
				cerr << "invalid file" << endl;
				continue;
			}
		}  
		else if (valid_cmd == b.changable_cmd.random) {
			b.clearSeq();
		}//random
		else if (valid_cmd == b.changable_cmd.restart) {//restart
			if (b.getLevel() == 0) {
				if (!b.setSeq(file_name))cout << "cannot find sequence.txt" << endl;
			}
			b.restart();
		} // impliment first
		else if (valid_cmd == b.changable_cmd.hint) {
			b.hint();
			continue;
		} //impliment last
		else if (valid_cmd == b.changable_cmd.sequence) { //sequence
			cin >> file_name;
			in.close();
			in.open(file_name);
			if (!in.is_open()) {
				cerr << "invalid file" << endl;
			}
			continue;
		} //impliment for testing purpose
		else if(valid_cmd == b.changable_cmd.rename){
			string old, new_name;
			if (in >> old) {
				in >> new_name;
			}
			else {
				cin >> old;
				cin >> new_name;
			}
			setName(old, new_name, b.changable_cmd);
		}
		else if (valid_cmd == b.changable_cmd.life){
			int lifetime;
			if (in >> lifetime) {}
			else { cin >> lifetime; }
			b.setLife(lifetime);
		}
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
					b.setCur(b.getNext());
					if (!b.not_over) break;//game over here. You lose.
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
		if (!b.not_over) {
			cout << "game over" << endl;
		}
		else { cout << b; }
    }

}
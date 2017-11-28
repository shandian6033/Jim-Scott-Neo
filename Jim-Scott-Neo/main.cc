#include <iostream>
#include <sstream>
#include <string>
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
    string cmd;
    while (true) {

        cin >> cmd;

        if (cmd == "left" || cmd == "right" || cmd == "down" || cmd == "drop" || cmd == "clockwise" || cmd == "counterclockwise") { // impliment first
            //Board.Movement(cmd);
        }
        else if (cmd == "levelup") {}
        else if (cmd == "leveldown") {}

        else if (cmd == "norandom") {} //impliment when we have level 3,4
        else if (cmd == "random") {}

        else if (cmd == "sequence file") {} //impliment for testing purpose
        else if (cmd == "I" || cmd == "J" || cmd == "L") {}

        else if (cmd == "restart") {} // impliment first

        else if (cmd == "hint") {} //impliment last

        else if (cmd == "quit") break;
		else {}; //error message here


    }

}
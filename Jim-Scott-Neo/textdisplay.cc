#include "textdisplay.h"
#include "board.h"

//class TextDisplay: public Observer {
//    std::vector<std::vector<char>> theDisplay;
//    const int length, width;
//public:
//TextDisplay(int width, int length);
    
// void notify(Subject &whoFrom) override;
    
// friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
//};


//#endif // !TEXTDISPLAY_H


TextDisplay::TextDisplay(int width, int length, const Board& my_board) :theDisplay{}, length{ length }, width{ width }, my_board{ &my_board } {
    for (int r=0; r<length; r++) {
		std::vector<char> new_row;
        for (int c=0; c<width; ++c) {
            new_row.emplace_back(' ');
        }
		theDisplay.emplace_back(new_row);
    }
}

void TextDisplay:: notify(Subject &whoFrom) {
    Info info_I_got = whoFrom.getInfo();
    if (info_I_got.id == WhoIam::O) {
        this->theDisplay.at(info_I_got.row).at(info_I_got.col) = 'O';
    }
    else if (info_I_got.id == WhoIam::J) {
		this->theDisplay.at(info_I_got.row).at(info_I_got.col) = 'J';
    }
    else if (info_I_got.id == WhoIam::L) {
		this->theDisplay.at(info_I_got.row).at(info_I_got.col) = 'L';
    }
    else if (info_I_got.id == WhoIam::S) {
		this->theDisplay.at(info_I_got.row).at(info_I_got.col) = 'S';
    }
    else if (info_I_got.id == WhoIam::Z) {
		this->theDisplay.at(info_I_got.row).at(info_I_got.col) = 'Z';
    }
    else if (info_I_got.id == WhoIam::I) {
		this->theDisplay.at(info_I_got.row).at(info_I_got.col) = 'I';
    }
    else if (info_I_got.id == WhoIam::T) {
		this->theDisplay.at(info_I_got.row).at(info_I_got.col) = 'T';
    }
    else if (info_I_got.id == WhoIam::Null) {
		this->theDisplay.at(info_I_got.row).at(info_I_got.col) = '-';
    }
	else {
		this->theDisplay.at(info_I_got.row).at(info_I_got.col) = '*';
	}
}

void TextDisplay::clear() {
	for (int r = 0; r < length; r++) {
		for (int c = 0; c < width; ++c) {
			theDisplay.at(r).at(c) = '-';
		}
	}
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
	out << "Level: " << td.my_board->getLevel() << endl;
	out << "Score: " << td.my_board->getScore() << endl;
	out << "Hi Score: " << td.my_board->getHi() << endl;
	
	for (int i = 0; i < td.width; i++) {
		out << '-';
	}
	out << endl;
	
	for (int r = 0; r<td.length; ++r) {
        for (int c = 0; c<td.width; ++c) {
            out << td.theDisplay.at(r).at(c);
        }
        out << endl;
    }

	for (int i = 0; i < td.width; i++) {
		out << '-';
	}
	out << endl;

	out << "Next:" << endl;
	if (td.my_board->getNext() == WhoIam::S) {
		out << " SS" << endl << "SS" << endl;
	}
	else if (td.my_board->getNext() == WhoIam::Z) {
        out << "ZZ" << endl << " ZZ" << endl;
	}
	else if (td.my_board->getNext() == WhoIam::L) {
		out << "LLL" << endl << "L" << endl;
	}
    else if (td.my_board->getNext() == WhoIam::J) {
        out << "JJJ" << endl << "  J" << endl;
    }
    else if (td.my_board->getNext() == WhoIam::T) {
        out << "TTT" << endl << " T" << endl;
    }
	else if (td.my_board->getNext() == WhoIam::I) {
		out << "IIII" << endl;
	}
	else if (td.my_board->getNext() == WhoIam::O) {
		out << "OO" << endl << "OO" << endl;
	}

    return out;
}

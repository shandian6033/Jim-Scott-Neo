#include "textdisplay.h"


//class TextDisplay: public Observer {
//    std::vector<std::vector<char>> theDisplay;
//    const int length, width;
//public:
//TextDisplay(int width, int length);
    
// void notify(Subject &whoFrom) override;
    
// friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
//};


#endif // !TEXTDISPLAY_H


TextDisplay:: TextDisplay(int width, int length) {
    int col;
    int row;
    for (col=0; col<length; col++) {
        for (row=0; row<width; ++row) {
            theDisplay[col].emplace_back('_');
        }
    }
}

void TextDisplay:: notify(Subject &whoFrom) {
    Info info_I_got = whoFrom.getInfo();
    if (info_I_got.id == O) {
        this->theDisplay[info_I_got.col][info_I_got.row] = 'O';
    }
    else if (info_I_got.id == J) {
        this->theDisplay[info_I_got.col][info_I_got.row] = 'J';
    }
    else if (info_I_got.id == L) {
        this->theDisplay[info_I_got.col][info_I_got.row] = 'L';
    }
    else if (info_I_got.id == S) {
        this->theDisplay[info_I_got.col][info_I_got.row] = 'S';
    }
    else if (info_I_got.id == Z) {
        this->theDisplay[info_I_got.col][info_I_got.row] = 'Z';
    }
    else if (info_I_got.id == I) {
        this->theDisplay[info_I_got.col][info_I_got.row] = 'I';
    }
    else if (info_I_got.id == T) {
        this->theDisplay[info_I_got.col][info_I_got.row] = 'T';
    }
    else if (info_I_got.id == NULL) {
        this->theDisplay[info_I_got.col][info_I_got.row] = '_';
    }
    else if (info_I_got.id == Block) {
        //edit here for notify from Block;
    }
}

std::ostream & TextDisplay:: operator<<(std::ostream &out, const TextDisplay &td) {
    for (int row = 0; row<td.length; ++row) {
        for (int col = 0; col<td.width; ++col) {
            out << td.theDisplay[row][col];
        }
        out << endl;
    }
    return out;
}

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
    std:: vector<std:: vector<char>> blanks;
    int col;
    int row;
    for (col=0; col<length; col++) {
        for (row=0; row<width; ++row) {
            blanks[col].emplace_back('_');
        }
    }
}

void TextDisplay:: notify(Subject &whoFrom) {
    Info Info_I_got = whoFrom.getInfo();
    this->blanks[Info_I_got.col][Info_I_got.row] = Info_I_got.id;
}


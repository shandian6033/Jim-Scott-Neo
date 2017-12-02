#include <iostream>
#include "graphicsdisplay.h"
#include "subject.h"
#include "board.h"
#include "info.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int width, int length, const Board& my_board)
    :width{ width }, height{length},win_width {width*cell_size}, win_height{ (length + 1)*cell_size }, my_board{ &my_board }, xw{ win_width, win_height } {
    
    for (int r = 0; r<length; r++) {
        std::vector<WhoIam> new_row;
        for (int c = 0; c<width; ++c) {
            new_row.emplace_back(WhoIam::Null);
        }
        the_display.emplace_back(new_row);
    }
}

void GraphicsDisplay::clear() {
    
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; ++c) {
            the_display.at(r).at(c) = WhoIam::Null;
        }
    }
    
    xw.fillRectangle(0, 0, win_width, win_height, Xwindow::Background);
    xw.fillRectangle(0, 40, win_width, 5,Xwindow::Black);
}

void GraphicsDisplay::notify(Subject &whoFrom) {
    Info info_I_got = whoFrom.getInfo();
    the_display.at(info_I_got.row).at(info_I_got.col) = info_I_got.id;
}

void GraphicsDisplay::updateText(){

    WhoIam next = my_board->getNext();
    string next_block_str;

    switch (next)
    {
    case WhoIam::O:
        next_block_str = "O";
        break;
    case WhoIam::J:
        next_block_str = "J";
        break;
    case WhoIam::L:
        next_block_str = "L";
        break;
    case WhoIam::S:
        next_block_str = "S";
        break;
    case WhoIam::Z:
        next_block_str = "Z";
        break;
    case WhoIam::I:
        next_block_str = "I";
        break;
    case WhoIam::T:
        next_block_str = "T";
        break;
    default: break;
    }
    
    string lev_str = "Level: " + to_string(my_board->getLevel());
    string score_str = "Score: " + to_string(my_board->getScore());
    string hi_score_str = "Hi Score: " + to_string(my_board->getHi());
    next_block_str = "Next: " + next_block_str + "Block";

    xw.fillRectangle(0, 0, win_width, 39,Xwindow::Background);
    int offset = 5;
    int space = 90;
    xw.drawString(offset + 0 * space, 23, lev_str);
    xw.drawString(offset + 1 * space, 23, score_str);
    xw.drawString(offset + 2 * space, 23, hi_score_str);
    xw.drawString(offset + 20 + 3 * space, 23, next_block_str);

}

void GraphicsDisplay::updateGraphic(){
    /*
     xxxx
    y
    y
    y
    
    
    */
    
    updateText();

    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; ++c) {
            WhoIam info = the_display.at(r).at(c);

            int x = c;
            int y = r+1;
            
            switch (info) {
            case WhoIam::L:
                xw.fillRectangle(x * cell_size, y * cell_size, cell_size, cell_size, Xwindow::Red);
                break;
            case WhoIam::T:
                xw.fillRectangle(x * cell_size, y * cell_size, cell_size, cell_size, Xwindow::Orange);
                break;
            case WhoIam::J:
                xw.fillRectangle(x * cell_size, y * cell_size, cell_size, cell_size, Xwindow::Yellow);
                break;
            case WhoIam::Z:
                xw.fillRectangle(x * cell_size, y * cell_size, cell_size, cell_size, Xwindow::Green);
                break;
            case WhoIam::O:
                xw.fillRectangle(x * cell_size, y * cell_size, cell_size, cell_size, Xwindow::Cyan);
                break;
            case WhoIam::S:
                xw.fillRectangle(x * cell_size, y * cell_size, cell_size, cell_size, Xwindow::Blue);
                break;
            case WhoIam::I:
                xw.fillRectangle(x * cell_size, y * cell_size, cell_size, cell_size, Xwindow::Purple);
                break;
            case WhoIam::X:
                xw.fillRectangle(x * cell_size, y * cell_size, cell_size, cell_size, Xwindow::Black);
                break;
            default:
                xw.fillRectangle(x * cell_size, y * cell_size, cell_size, cell_size, Xwindow::Background);
            }
        }
    }
}

void GraphicsDisplay::test() {

    int h = win_width / 9;
    for (int i = 0;i < 9;i++) {
        xw.fillRectangle(0, i*h, win_width, h, i);
        xw.drawString(20, i*h + h / 2, "0123456789");
    }

}
#include <iostream>
#include "graphicsdisplay.h"
#include "subject.h"
#include "board.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int width, int length, const Board& my_board)
    :width{ width }, height{length},win_width {width*cell_size}, win_height{ (length + global_offset)*cell_size }, my_board{ &my_board }, xw{ win_width, win_height } {
    
}

void GraphicsDisplay::clear() {
    
    xw.fillRectangle(0, 0, win_width, win_height, Xwindow::Background);
    xw.fillRectangle(0, global_offset*cell_size - 5, win_width, 5,Xwindow::Black);
}

void GraphicsDisplay::notify(Subject &whoFrom) {
    Info info_I_got = whoFrom.getInfo();
    
    int x = info_I_got.col;
    int y = info_I_got.row + global_offset;

    switch (info_I_got.id) {
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
        xw.fillRectangle(x * cell_size, y * cell_size, cell_size, cell_size, Xwindow::DarkRed);
        break;
    case WhoIam::H:
        xw.fillRectangle(x * cell_size, y * cell_size, cell_size, 3, Xwindow::Black);
        xw.fillRectangle(x * cell_size, y * cell_size, 3, cell_size, Xwindow::Black);
        xw.fillRectangle((x+1) * cell_size - 3, y* cell_size, 3, cell_size, Xwindow::Black);
        xw.fillRectangle(x * cell_size, (y+1) * cell_size - 3,cell_size, 3, Xwindow::Black);
        break;
    default:
        xw.fillRectangle(x * cell_size, y * cell_size, cell_size, cell_size, Xwindow::Background);
    }
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
    next_block_str = "Next:";

    xw.fillRectangle(0, 0, win_width, global_offset*cell_size-5,Xwindow::Background); //rewrite window

    int offset = 5;
    int v_space = 30;
    xw.drawString(offset, v_space, lev_str);
    xw.drawString(offset, 2*v_space, score_str);
    xw.drawString(offset, 3*v_space, hi_score_str);
    xw.drawString(win_width/2 - 20, 2*v_space, next_block_str);

    displayNextBlock(next);
}

void GraphicsDisplay::displayNextBlock(WhoIam next) {

    const int start_x = win_width / 2 + cell_size;
    const int start_y = (global_offset - 2)*cell_size*0.5;
    switch (next)
    {
    case WhoIam::L:
        xw.fillRectangle(start_x, start_y, 3*cell_size, cell_size, Xwindow::Red);
        xw.fillRectangle(start_x, start_y+cell_size, cell_size, cell_size, Xwindow::Red);
        break;
    case WhoIam::T:
        xw.fillRectangle(start_x, start_y, 3*cell_size, cell_size, Xwindow::Orange);
        xw.fillRectangle(start_x + cell_size, start_y+cell_size, cell_size, cell_size, Xwindow::Orange);
        break;
    case WhoIam::J:
        xw.fillRectangle(start_x, start_y, 3*cell_size, cell_size, Xwindow::Yellow);
        xw.fillRectangle(start_x + 2 * cell_size, start_y+cell_size, cell_size, cell_size, Xwindow::Yellow);
        break;
    case WhoIam::Z:
        xw.fillRectangle(start_x, start_y, 2*cell_size, cell_size, Xwindow::Green);
        xw.fillRectangle(start_x + cell_size, start_y+cell_size, 2 * cell_size, cell_size, Xwindow::Green);
        break;
    case WhoIam::O:
        xw.fillRectangle(start_x, start_y, 2 * cell_size, 2*cell_size, Xwindow::Cyan);
        break;
    case WhoIam::S:
        xw.fillRectangle(start_x + cell_size, start_y, 2 * cell_size, cell_size, Xwindow::Blue);
        xw.fillRectangle(start_x, start_y+cell_size, 2 * cell_size, cell_size, Xwindow::Blue);
        break;
    case WhoIam::I:
        xw.fillRectangle(start_x, (global_offset - 1)*cell_size*0.5, 4 * cell_size, cell_size, Xwindow::Purple);
        break;
    default: break;

    }




}

void GraphicsDisplay::test() {

    int h = win_width / 9;
    for (int i = 0;i < 9;i++) {
        xw.fillRectangle(0, i*h, win_width, h, i);
        xw.drawString(20, i*h + h / 2, "0123456789");
    }

}
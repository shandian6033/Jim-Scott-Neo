#include <iostream>
#include "graphicsdisplay.h"
#include "subject.h"
#include "board.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int width, int length, const Board& my_board)
    :win_width{ width*cell_size }, win_height{ (length + 1)*cell_size }, my_board{ &my_board }, xw{ win_width, win_height} {}

void GraphicsDisplay::clear() {
    xw.fillRectangle(0, 0, win_width, win_height, Xwindow::Background);
    xw.fillRectangle(0, 40, win_width, 5,Xwindow::Black);
}
void GraphicsDisplay::notify(Subject &whoNotified) {
  auto info = whoNotified.getInfo();
  int col_pos = info.col;
  int row_pos = info.row + 1;
  switch(info.id) {
    case WhoIam::L:
        xw.fillRectangle(col_pos * cell_size, row_pos * cell_size, cell_size, cell_size, Xwindow::Red);
        break;
    case WhoIam::T:
        xw.fillRectangle(col_pos * cell_size, row_pos * cell_size, cell_size, cell_size, Xwindow::Orange);
        break;
    case WhoIam::J:
        xw.fillRectangle(col_pos * cell_size, row_pos * cell_size, cell_size, cell_size, Xwindow::Yellow);
        break;
    case WhoIam::Z:
        xw.fillRectangle(col_pos * cell_size, row_pos * cell_size, cell_size, cell_size, Xwindow::Green);
        break;
    case WhoIam::O:
        xw.fillRectangle(col_pos * cell_size, row_pos * cell_size, cell_size, cell_size, Xwindow::Cyan);
        break;
    case WhoIam::S:
        xw.fillRectangle(col_pos * cell_size, row_pos * cell_size, cell_size, cell_size, Xwindow::Blue);
        break;
    case WhoIam::I:
        xw.fillRectangle(col_pos * cell_size, row_pos * cell_size, cell_size, cell_size, Xwindow::Purple);
        break;
    case WhoIam::X:
        xw.fillRectangle(col_pos * cell_size, row_pos * cell_size, cell_size, cell_size, Xwindow::Black);
        break;
    default:
        xw.fillRectangle(col_pos * cell_size, row_pos * cell_size, cell_size, cell_size, Xwindow::Background);
  }

  updateText();
}

void GraphicsDisplay::test() {

    int h = win_width / 9;
    for (int i = 0;i < 9;i++) {
        xw.fillRectangle(0, i*h, win_width, h, i);
        xw.drawString(20, i*h + h / 2, "0123456789");
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
    next_block_str = "Next: " + next_block_str + "Block";

    xw.fillRectangle(0, 0, win_width, 39,Xwindow::Background);
    int offset = 5;
    int space = 90;
    xw.drawString(offset + 0 * space, 23, lev_str);
    xw.drawString(offset + 1 * space, 23, score_str);
    xw.drawString(offset + 2 * space, 23, hi_score_str);
    xw.drawString(offset + 20 + 3 * space, 23, next_block_str);

}
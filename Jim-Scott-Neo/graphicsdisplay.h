#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include "info.h"
#include "observer.h"
#include "window.h"
class Board;

class GraphicsDisplay: public Observer{
    const int cell_size = 40;
    const int global_offset = 3; //# of blocks
    const int width, height; // # of blocks
    const int win_width, win_height; // # of pixels
    const Board* my_board;
    Xwindow xw;

    void displayNextBlock(WhoIam);
    
 public:
  GraphicsDisplay(int width, int length, const Board& my_board);
  void updateText();
  void clear();
  void notify(Subject &whoFrom) override;
  void test();
};
#endif

#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "window.h"
class Board;

class GraphicsDisplay: public Observer{
    const int cell_size = 46;
    const int win_width, win_height; // # of pixels
    const int width, height; // # of blocks
    const Board* my_board;
    Xwindow xw;
    std::vector<std::vector<WhoIam>> the_display;

    void updateText();
    
 public:
  GraphicsDisplay(int width, int length, const Board& my_board);
  void updateGraphic();
  void clear();
  void notify(Subject &whoFrom) override;
  void test();
};
#endif

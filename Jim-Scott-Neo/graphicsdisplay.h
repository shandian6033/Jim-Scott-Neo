#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "window.h"
class Board;

class GraphicsDisplay: public Observer{
    const int cell_size = 46;
    const int win_width, win_height;
    const Board* my_board;
    Xwindow xw;
    void updateText();
 public:
  GraphicsDisplay(int width, int length, const Board& my_board);

  void clear();
  void notify(Subject &whoNotified) override;
  void test();
};
#endif

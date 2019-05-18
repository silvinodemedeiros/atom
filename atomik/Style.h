#ifndef STYLE_H
#define STYLE_H

#include "../colors.h"
#include "StyleTypes.h"

class Style {

  public:
    int x = 0;
    int initX = 0;
    int y = 0;
    int initY = 0;
    int width = 0;
    int initWidth = 0;
    int gap = 6;
    int height = 0;
    int initHeight = 0;
    int childrenFill = 0;
    int fill = 1;

    DisplayStyle display = NONE;
    bool visibility = true;

    int borderColor = DEFAULTGREEN;
    int bgColor = MAINBG;

    Style() {}
  
};

#endif
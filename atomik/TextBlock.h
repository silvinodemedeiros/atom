#ifndef TEXTBLOCK_H
#define TEXTBLOCK_H

#include "Container.h"

class TextBlock : public Container {

  protected:
    String text = "";
    int skeletonW = 135;
    int skeletonH = 25;
  
  public:
    TextBlock(int ux, int uy, String utxt) : Container(ux, uy, 0, 0) {
      text = utxt;
    }

    TextBlock(String utxt) : Container() {
      text = utxt;
    }

    void erase() {
      display->setTextColor(style->bgColor);
      display->setCursor(style->x, style->y);
      display->setTextSize(style->textSize);
      display->print(text);
    }

    void draw() {
      display->setTextColor(style->borderColor);
      display->setCursor(style->x, style->y);
      display->setTextSize(style->textSize);
      display->print(text);
    }
  
};



#endif
#ifndef TEXTBLOCK_H
#define TEXTBLOCK_H

#include "Block.h"

class TextBlock : public Block {

  protected:
    String content = "";
    int skeletonW = 135;
    int skeletonH = 25;
  
  public:
    TextBlock(int ux, int uy, String utxt) : Block(ux, uy, 0, 0) {
      content = utxt;
    }

    TextBlock(String utxt) : Block() {
      content = utxt;
    }

    void erase() {
      display->setTextColor(style->bgColor);
      display->setCursor(style->x, style->y);
      display->setTextSize(style->textSize);
      display->print(content);
    }

    void draw() {
      display->setTextColor(style->borderColor);
      display->setCursor(style->x, style->y);
      display->setTextSize(style->textSize);
      display->print(content);
    }
  
};



#endif
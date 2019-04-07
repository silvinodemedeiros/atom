#ifndef TEXTBLOCK_H
#define TEXTBLOCK_H

#include "Block.h"

class TextBlock : public Block {

  protected:
  String text = "";
  int skeletonW = 135;
  int skeletonH = 25;
  
  public:
  TextBlock(Adafruit_TFTLCD *tft, int ux, int uy) :
  Block(tft, ux, uy) {
    text = String("Test String");
  }

  void erase() {
    display->setTextColor(bgColor);
    display->setCursor(x, y);
    display->setTextSize(2);
    display->print(text);
  }

  void draw() {
    display->setTextColor(borderColor);
    display->setCursor(x, y);
    display->setTextSize(2);
    display->print(text);
  }
  
};



#endif
#ifndef CONTAINER_H
#define CONTAINER_H

#include "Block.h"

class Container : public Block {

  protected:
    int defaultColor = DEFAULTGREEN;
    int activeColor = WHITE;

    // tree attributes
    int chAmt = 0;

    /* 
      NEED FIX:
      Children are specified with Container so derived methods (like ajustChildrenDimensions)
      will be invoked through the Container implementation
    */
    Container **chSet;

    int gap = 6;

  public:
    Container(int ux, int uy, int w, int h) : Block(ux, uy, w, h) {}
    Container() : Block() {}

    void manageState(boolean manageSelf = true) {

      for (int i = 0; i < chAmt; i++) {
        chSet[i]->manageState();
      }

      if (manageSelf) {
        Block::manageState();
      }
    }

    int getChildrenAmount() {
      return chAmt;
    }

    void appendChild(Container *child) {
      Container **newChSet = new Container*[chAmt + 1];

      int i = 0;
      while (i < chAmt) { newChSet[i] = chSet[i]; i++; }

      child->setDisplay(display);
      newChSet[i] = child;
      chSet = newChSet;
      chAmt++;

      adjustChildrenDimensions();
    }

    void adjustChildrenDimensions() {
      int totalGap = gap * (chAmt - 1);
      int currentX = x;

      for (int i = 0; i < chAmt; i++) {
        chSet[i]->setX(currentX);
        chSet[i]->setY(y);
        chSet[i]->setWidth(width);
        chSet[i]->setHeight(height);

        currentX += width + gap;

        if (chSet[i]->getChildrenAmount() > 0) {
          chSet[i]->adjustChildrenDimensions();
        }
      }
    }

    void translateY(int toY, int dir) {
      Block::translateY(toY, dir);

      for (int i = 0; i < chAmt; i++) {
        chSet[i]->translateY(toY + 10, dir);
      }
    }
};

#endif
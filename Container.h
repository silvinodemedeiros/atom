#ifndef CONTAINER_H
#define CONTAINER_H

#include "Block.h"

class Container : public Block {

  private:
    boolean active = false;
    Container *previous;
    Container *next;

    int defaultColor = DEFAULTGREEN;
    int activeColor = WHITE;

    // tree attributes
    int chAmt = 0;
    Block **chSet;

    // tmp container values
    int y0 = 58;
    int x0 = 6;

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

    void appendChild(Block *child) {
      Block **newChSet = new Block*[chAmt + 1];

      int i = 0;
      while (i < chAmt) { newChSet[i] = chSet[i]; i++; }

      child->setDisplay(display);
      newChSet[i] = child;
      chSet = newChSet;
      chAmt++;

      // TASK: adjust dimensions here
      int gap = 6;
      int totalGap = gap * (chAmt - 1);
      int itemHeight = (height - totalGap) / chAmt;
      int currentY = y0;

      for (int i = 0; i < chAmt; i++) {
        chSet[i]->setX(x);
        chSet[i]->setY(currentY);
        chSet[i]->setWidth(width);
        chSet[i]->setHeight(itemHeight);

        currentY += itemHeight + gap;
      }
    }

    void translateY(int toY, int dir) {
      Block::translateY(toY, dir);

      for (int i = 0; i < chAmt; i++) {
        chSet[i]->translateY(toY + 10, dir);
      }
    }









    /* CUSTOM SPECIFIC STUFF */
    
    void focus() {
      setBorderColor(activeColor);
      draw();
    }

    void unfocus() {
      setBorderColor(defaultColor);
      draw();
    }

    Container* getPrevious() {
      return previous;
    }

    Container* getNext() {
      return next;
    }
    
    void setPrevious(Container *container) {
      previous = container;
    }

    void setNext(Container *container) {
      next = container;
    }
};

#endif
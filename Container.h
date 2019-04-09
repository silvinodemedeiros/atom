#ifndef CONTAINER_H
#define CONTAINER_H

#include <stdlib.h>
#include "Block.h"

class Container : public Block {

  private:
    boolean active = false;
    Container *previous;
    Container *next;

    int defaultColor = DEFAULTGREEN;
    int activeColor = WHITE;

    // tree attributes
    size_t chAmt = 0;
    Block **chSet;

    // tmp container values
    int y0 = 58;
    int x0 = 6;

  public:
    Container(Adafruit_TFTLCD *tft, int ux, int uy, int w, int h) : Block(tft, ux, uy, w, h) {}

    void manageState() {

      for (size_t i = 0; i < chAmt; i++) {
        chSet[i]->manageState();
      }

      Block::manageState();
    }

    void appendChild(Block *child) {
      Block **newChSet = new Block*[chAmt + 1];

      size_t i = 0;
      while (i < chAmt) { newChSet[i] = chSet[i]; i++; }
      newChSet[i] = child;
      
      chSet = newChSet;
      chAmt++;
    }

    void translateY(int toY, int dir) {
      Block::translateY(toY, dir);

      for (size_t i = 0; i < chAmt; i++) {
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

    void select() {
      translateY(y0, -1);
    }

    void unselect() {
      translateY(initY, 1);
    }
};

#endif
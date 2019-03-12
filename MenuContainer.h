#ifndef MENUCONTAINER_H
#define MENUCONTAINER_H

#include "Block.h"

class MenuContainer : public Block {

  private:
    boolean active = false;
    MenuContainer *previous;
    MenuContainer *next;

    int defaultColor = DEFAULTGREEN;
    int activeColor = WHITE;

    // tmp container values
    int y0 = 58;
    int x0 = 6;

  public:
    MenuContainer(Adafruit_TFTLCD *tft, int ux, int uy, int w, int h) : 
    Block(tft, ux, uy, w, h) {}

    void focus() {
      setBorderColor(activeColor);
      draw();
    }

    void unfocus() {
      setBorderColor(defaultColor);
      draw();
    }

    MenuContainer* getPrevious() {
      return previous;
    }

    MenuContainer* getNext() {
      return next;
    }
    
    void setPrevious(MenuContainer *container) {
      previous = container;
    }

    void setNext(MenuContainer *container) {
      next = container;
    }

    void select() {
      children = new Block(display, x0, y0 + height + 10, width, 0);
      appendChild(children);
      startTranslationY(y0, -1);
    }

    void unselect() {
      removeChild();
      startTranslationY(initY, 1);
    }

    void translateY(int toY, int dir) {
      startTranslationY(toY, dir);
    }
};

#endif
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
      children = new Block(display, 1000, 0, width, 50);
      doneState = DONE_ANIMATION;
      willRenderChildren = true;
      startTranslateY(y0, -1);
    }

    void unselect() {
      children->erase();
      delete children;
      willRenderChildren = false;
      startTranslateY(initY, 1);
    }

    void translateY(int toY, int dir) {
      startTranslateY(toY, dir);
    }
};

#endif
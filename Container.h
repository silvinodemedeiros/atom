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
    Block *children;
    boolean hasChildren = false;

    // tmp container values
    int y0 = 58;
    int x0 = 6;

  public:
    Container(Adafruit_TFTLCD *tft, int ux, int uy, int w, int h) : 
    Block(tft, ux, uy, w, h) {}

    void manageState() {

      if (hasChildren) {
        children->manageState();
      }

      Block::manageState();
      
    }

    void appendChild(Block *child) {
      children = child;
      hasChildren = true;
      children->draw();
    }

    void translateY(int toY, int dir) {
      startTranslationY(toY, dir);

      if (hasChildren) {
        children->startTranslationY(toY + 10, dir);
      }
    }

    void removeChild() {
      hasChildren = false;
      children->erase();
      delete children;
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
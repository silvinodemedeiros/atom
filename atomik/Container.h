
#ifndef CONTAINER_H
#define CONTAINER_H

#include "Style.h"
#include "StyleTypes.h"
#include "TextBlock.h"
#include "Block.h"

class Container : public Block {

  public:
    void (*manageForwards)(Container*) = 0;
    void (*manageBackwards)(Container*) = 0;
    void (*manageSelection)(Container*) = 0;
    void (*manageReturn)(Container*) = 0;
  
    Container **chSet;
    int chAmt = 0;
    Container *parent = 0;
    Container *next = 0;
    Container *previous = 0;
    bool focused = false;
    int nextSystemState = -1;

    Container(int ux, int uy, int w, int h) : Block(ux, uy, w, h) {}
    Container() : Block() {}

    void setNext(Container *nextContainer) {
      next = nextContainer;
    }

    void setPrevious(Container *previousContainer) {
      previous = previousContainer;
    }

    void manageState() {

      for (int i = 0; i < chAmt; i++) {
        chSet[i]->manageState();
      }

      Block::manageState();
    }

    void erase() {

      for (int i = 0; i < chAmt; i++) {
        chSet[i]->erase();
      }

      Block::erase();
    }

    int isEmpty() {
      return chAmt == 0;
    }

    void appendChild(Container *child) {
      Container **newChSet = new Container*[chAmt + 1];

      int i = 0;
      while (i < chAmt) {
        newChSet[i] = chSet[i];
        i++;
      }

      this->style->childrenFill += child->style->fill;
      
      child->parent = this;
      child->setDisplay(display);
      newChSet[i] = child;
      chSet = newChSet;
      chAmt++;

      configureChildren();
    }

    void configureChildren() {

      int currentY = this->style->y;
      int currentX = this->style->x;

      int totalGap = this->style->gap * (chAmt - 1);
      int unitFillHeight = (HEIGHT - totalGap - 40) / this->style->childrenFill;
      int unitFillWidth = (WIDTH - totalGap - 30) / this->style->childrenFill;

      for (int i = 0; i < chAmt; i++) {

        Container *child = chSet[i];
        child->style->y = currentY;
        child->style->x = currentX;

        switch (this->style->display) {
          case COLUMN:
            child->style->width = this->style->width;
            child->style->height = (child->style->fill * unitFillHeight) + child->style->fill * this->style->gap - this->style->childrenFill;

            currentY += child->style->height + this->style->gap;
          break;

          case ROW:
            child->style->height = this->style->height;
            child->style->width = (child->style->fill * unitFillWidth) + child->style->fill * this->style->gap - this->style->childrenFill;

            currentX += child->style->width + this->style->gap;
          break;

          case NONE:
            currentY += child->style->height + this->style->gap;
          break;
        }

        child->style->initX = child->style->x;
        child->style->initY = child->style->y;

        if (!child->isEmpty() > 0) {
          child->configureChildren();
        }
      }
    }

    void translateY(int deltaY) {
      Block::translateY(deltaY);

      for (int i = 0; i < chAmt; i++) {
        chSet[i]->translateY(deltaY);
      }
    }

    void translateX(int deltaX) {
      Block::translateX(deltaX);

      for (int i = 0; i < chAmt; i++) {
        chSet[i]->translateX(deltaX);
      }
    }

    void expandHeight(int deltaH) {
      Block::expandHeight(deltaH);
    }

    void expandWidth(int deltaW) {
      Block::expandWidth(deltaW);
    }

    void focus() {
      this->style->borderColor = WHITE;
      focused = true;
    }

    void unfocus() {
      this->style->borderColor = DEFAULTGREEN;
      focused = false;
    }

    Container* focusNext() {
      if (next) {
        this->unfocus();
        next->focus();
        return next;
      }
    }

    Container* focusPrevious() {
      if (previous) {
        this->unfocus();
        previous->focus();
        return previous;
      }
    }

};

#endif
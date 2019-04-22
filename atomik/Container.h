
#ifndef CONTAINER_H
#define CONTAINER_H

#include "Style.h"
#include "StyleManager.h"
#include "StyleTypes.h"

#include "Block.h"

class Container : public Block {

  protected:
    int defaultColor = DEFAULTGREEN;
    int activeColor = WHITE;

  public:

    // PUBLIC TEMP: tree attributes
    Container **chSet;
    int chAmt = 0;
    StyleManager *styleMgr = new StyleManager();

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

      configureChildren();
    }

    void configureChildren() {

      for (int i = 0; i < chAmt; i++) {
        chSet[i]->style = styleMgr->getChildrenStyles(this->style, chAmt);
      }

      repositionChildren();
      
      for (int i = 0; i < chAmt; i++) {
        if (chSet[i]->getChildrenAmount() > 0) {
          chSet[i]->configureChildren();
        }
      }
    }

    void repositionChildren() {
      int currentY = this->style->y;
      int currentX = this->style->x;

      for (int i = 0; i < chAmt; i++) {

        switch (this->style->display)
        {
        case COLUMN:
          chSet[i]->style->y = currentY;
          currentY += chSet[i]->style->height + this->style->gap;
          break;
        case ROW:
          chSet[i]->style->x = currentX;
          currentX += chSet[i]->style->width + this->style->gap;
          break;
        case NONE:
          chSet[i]->style->y = currentY;
          currentY += this->style->height + this->style->gap;
          break;
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
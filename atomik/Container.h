
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

    void manageState() {

      for (int i = 0; i < chAmt; i++) {
        chSet[i]->manageState();
      }

      Block::manageState();
    }

    int getChildrenAmount() {
      return chAmt;
    }

    void appendChild(Container *child) {
      Container **newChSet = new Container*[chAmt + 1];

      int i = 0;
      while (i < chAmt) {
        newChSet[i] = chSet[i];
        
        i++;
      }

      child->setDisplay(display);
      newChSet[i] = child;
      chSet = newChSet;
      chAmt++;

      configureChildren();
    }

    void configureChildren() {
      int currentY = this->style->y;
      int currentX = this->style->x;

      for (int i = 0; i < chAmt; i++) {
        Style *oldStyle = chSet[i]->style;
        chSet[i]->style = styleMgr->getChildrenDimensions(this->style, chAmt);
        chSet[i]->style->display = oldStyle->display;

        switch (this->style->display) {
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
        
        if (chSet[i]->getChildrenAmount() > 0) {
          chSet[i]->configureChildren();
        }
      }

      
      for (int i = 0; i < chAmt; i++) {
      }
    }

    void repositionChildren() {

      for (int i = 0; i < chAmt; i++) {
        
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
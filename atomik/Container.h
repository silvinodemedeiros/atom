
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

      this->style->childrenFill += child->style->fill;

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

        Style oldStyle = *child->style;
        child->style = styleMgr->getChildrenDimensions(this->style, chAmt);
        child->style->fill = oldStyle.fill;
        child->style->display = oldStyle.display;
        // child->style->width = oldStyle.width;
        // child->style->height = oldStyle.height;

        switch (this->style->display) {
          case COLUMN:
            child->style->width = this->style->width;
            child->style->height = (child->style->fill * unitFillHeight) + (child->style->fill - 1) * this->style->gap - (this->style->childrenFill * 2);

            child->style->y = currentY;
            currentY += child->style->height + this->style->gap;
          break;

          case ROW:
            child->style->height = this->style->height;
            child->style->width = (child->style->fill * unitFillWidth) + (child->style->fill - 1) * this->style->gap - (this->style->childrenFill * 2);

            child->style->x = currentX;
            currentX += child->style->width + this->style->gap;
          break;

          case NONE:
            child->style->y = currentY;
            currentY += child->style->height + this->style->gap;
          break;
        }
        
        if (child->getChildrenAmount() > 0) {
          child->configureChildren();
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
#ifndef ROW_H
#define ROW_H

#include "Container.h"

class Row : public Container {

  public:
    Row(int ux, int uy, int w, int h) : Container(ux, uy, w, h) {}
    Row() : Container() {}

    void appendChild(Container *child) {
      Container::appendChild(child);

      adjustChildrenDimensions();
    }

    void adjustChildrenDimensions() {
      int totalGap = gap * (chAmt - 1);
      int itemWidth = (width - totalGap) / chAmt;
      int currentX = x;

      for (int i = 0; i < chAmt; i++) {
        chSet[i]->setX(currentX);
        chSet[i]->setY(y);
        chSet[i]->setWidth(itemWidth);
        chSet[i]->setHeight(height);

        currentX += itemWidth + gap;

        if (chSet[i]->getChildrenAmount() > 0) {
          chSet[i]->adjustChildrenDimensions();
        }
      }
    }
};

#endif
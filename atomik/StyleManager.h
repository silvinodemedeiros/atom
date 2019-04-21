#ifndef STYLEMANAGER_H
#define STYLEMANAGER_H

#include "Style.h"
#include "StyleTypes.h"

class StyleManager {

  public:
    StyleManager() {}

    Style* getChildrenStyles(Style *parentStyles, int childrenAmount) {
      int totalGap = parentStyles->gap * (childrenAmount - 1);
      Style *newStyle = new Style();

      // IF CONTAINER RENDER MODE IS COLUMN
      if (parentStyles->display == COLUMN) {

        int itemHeight = (parentStyles->height - totalGap) / childrenAmount;

        newStyle->x = parentStyles->x;
        newStyle->y = parentStyles->nextAvailableY;
        newStyle->width = parentStyles->width;
        newStyle->height = itemHeight;

        return newStyle;
      }

      // IF CONTAINER RENDER MODE IS ROW
      if (parentStyles->display == ROW) {

        int itemWidth = (parentStyles->width - totalGap) / childrenAmount;

        newStyle->x = parentStyles->x;
        newStyle->y = parentStyles->y;
        newStyle->width = itemWidth;
        newStyle->height = parentStyles->height;

        return newStyle;
      }

      // IF IT'S NONE
      newStyle->x = parentStyles->x;
      newStyle->y = parentStyles->nextAvailableY;
      newStyle->width = parentStyles->width;
      newStyle->height = parentStyles->height;

      return newStyle;
    }
};

#endif
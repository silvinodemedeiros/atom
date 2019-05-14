#ifndef STYLEMANAGER_H
#define STYLEMANAGER_H

#include "Style.h"
#include "StyleTypes.h"

class StyleManager {

  public:
    StyleManager() {}

    Style* getChildrenDimensions(Style *parentStyles, int childrenAmount) {
      int totalGap = parentStyles->gap * (childrenAmount - 1);
      Style *childStyle = new Style();

      parentStyles->visibility = false;
      childStyle->x = parentStyles->x;
      childStyle->y = parentStyles->y;

      // IF CONTAINER RENDER MODE IS COLUMN
      if (parentStyles->display == COLUMN) {

        int itemHeight = (parentStyles->height - totalGap) / childrenAmount;

        childStyle->width = parentStyles->width;
        childStyle->height = itemHeight;

        return childStyle;
      }

      // IF CONTAINER RENDER MODE IS ROW
      if (parentStyles->display == ROW) {

        int itemWidth = (parentStyles->width - totalGap) / childrenAmount;

        childStyle->width = itemWidth;
        childStyle->height = parentStyles->height;

        return childStyle;
      }

      // IF IT'S NONE
      childStyle->width = parentStyles->width;
      childStyle->height = parentStyles->height;

      return childStyle;
    }
};

#endif
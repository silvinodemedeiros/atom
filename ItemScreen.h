#ifndef ITEMSCREEN_H
#define ITEMSCREEN_H

#include "atomik/Screen.h"
#include "atomik/Container.h"

#include "TitleBar.h"
class ItemScreen : public Screen {

  public:
    ItemScreen (
      Adafruit_TFTLCD *tft,
      int stateValue,
      String titleValue,
      String screenContent
    ) : Screen (tft) {

      systemState = stateValue;

      Container *root = new Container();
      root->style->display = COLUMN;
      root->style->visibility = false;
      appendChild(root);

      TitleBar *titleBar = new TitleBar(titleValue);
      root->appendChild(titleBar);

      Container *content = new Container();
      content->style->fill = 5;
      content->style->display = COLUMN;
      content->text = screenContent;
      root->appendChild(content);
    }

};


#endif
#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include "atomik/Screen.h"
#include "atomik/Container.h"
#include "atomik/StyleTypes.h"

Screen *homeScreen;

void initializeHomeScreen(Adafruit_TFTLCD *tft) {

  int amount = 5;
  // String items[amount] = {"Item 1", "Item 2", "Item 3"};
  homeScreen = new Screen(tft);

  Container *root = new Container();
  root->style->display = ROW_FILL;
  homeScreen->appendChild(root);

  Container *firstChild = new Container();
  firstChild->style->fill = 5;
  root->appendChild(firstChild);

  Container *secondChild = new Container();
  secondChild->style->display = COLUMN;
  secondChild->style->fill = 3;
  root->appendChild(secondChild);

  secondChild->appendChild(new Container());
  secondChild->appendChild(new Container());
  secondChild->appendChild(new Container());
  secondChild->appendChild(new Container());
  secondChild->appendChild(new Container());
  
}

#endif
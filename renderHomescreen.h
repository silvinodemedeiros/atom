#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include "atomik/Screen.h"
#include "atomik/Container.h"
#include "atomik/StyleTypes.h"

Screen *homeScreen;

void initHomeScreen(Adafruit_TFTLCD *tft) {

  Container *homeRoot = new Container();
  homeRoot->style->display = COLUMN;
  homeRoot->style->visibility = false;

  int amount = 5;
  // String items[amount] = {"Item 1", "Item 2", "Item 3"};
  homeScreen = new Screen(tft);
  homeScreen->appendChild(homeRoot);
  homeScreen->nextSystemState = ITEM_STATE;

  for (int i = 0; i < amount; i++) {
    Container *child = new Container();
    homeRoot->appendChild(child);
  }
}

#endif
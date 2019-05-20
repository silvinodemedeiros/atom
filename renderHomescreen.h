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

  for (int i = 0; i < amount; i++) {
    Container *child = new Container();
    homeRoot->appendChild(child);

    if (i == 0) {
      homeScreen->currentOption = child;
      child->nextSystemState = ITEM_STATE;
      child->focus();
    }
  }

  for (int i = 0; i < homeRoot->chAmt; i++) {
    if (i > 0 && i < homeRoot->chAmt - 1) {
      homeRoot->chSet[i]->next = homeRoot->chSet[i+1];
      homeRoot->chSet[i]->previous = homeRoot->chSet[i-1];
    }

    else if (i == 0) {
      homeRoot->chSet[i]->next = homeRoot->chSet[i+1];
      homeRoot->chSet[i]->previous = homeRoot->chSet[homeRoot->chAmt - 1];
    }

    else if (i == homeRoot->chAmt - 1) {
      homeRoot->chSet[i]->next = homeRoot->chSet[0];
      homeRoot->chSet[i]->previous = homeRoot->chSet[i - 1];
    }
  }
}

#endif
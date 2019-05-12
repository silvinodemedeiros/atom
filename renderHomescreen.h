#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include "atomik/Screen.h"
#include "atomik/Container.h"
#include "atomik/StyleTypes.h"

Screen *homeScreen;

void initializeHomeScreen(Adafruit_TFTLCD *tft) {

  int amount = 5;
  // String items[amount] = {"Item 1", "Item 2", "Item 3"};
  homeScreen = new Screen(tft, COLUMN);

  for (int i = 0; i < amount; i++) {

    homeScreen->appendChild(new Container(););

    int gcAmt = random(1, 5);

    child->style->display = ROW;
    child->style->visibility = false;
    for (int j = 0; j < gcAmt; j++) {
      child->appendChild(new Container(););
    }
  }
  
}

#endif
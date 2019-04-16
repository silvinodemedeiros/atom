#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include "atomik/Screen.h"
#include "atomik/Container.h"
#include "atomik/Row.h"

Screen *homeScreen;

void initializeHomeScreen(Adafruit_TFTLCD *tft) {

  int amount = 5;
  // String items[amount] = {"Item 1", "Item 2", "Item 3"};
  homeScreen = new Screen(tft);

  for (int i = 0; i < amount; i++) {
    Row *child = new Row();

    for (int j = 0; j < 3; j++) {
      Container *grandChild = new Container();
      child->appendChild(grandChild);
    }

    homeScreen->appendChild(child);
  }
  
}

#endif
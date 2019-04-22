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
    Container *child = new Container();
    child->style->display = ROW;
    homeScreen->appendChild(child);

    if (i == 0) {
      for (int j = 0; j < 3; j++) {
        Container *grandChild = new Container();
        grandChild->style->borderColor = RED;
        child->appendChild(grandChild);
      }
    }
  }
  
}

#endif
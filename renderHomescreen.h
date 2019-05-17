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
  root->style->display = NONE;
  root->style->visibility = false;
  homeScreen->appendChild(root);

  Container *child = new Container (
    root->style->x,
    root->style->y,
    100,
    100
  );

  root->appendChild(child);
  homeScreen->setCurrentOption(child);
  
}

#endif
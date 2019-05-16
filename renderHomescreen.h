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
  root->style->display = COLUMN;
  root->style->visibility = false;
  homeScreen->appendChild(root);

  NavigationContainer *firstChild = new NavigationContainer();
  root->appendChild(firstChild);

  NavigationContainer *secondChild = new NavigationContainer();
  root->appendChild(secondChild);

  homeScreen->setCurrentOption(firstChild);
  firstChild->focus();
  
}

#endif
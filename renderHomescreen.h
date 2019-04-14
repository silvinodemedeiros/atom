#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include "atomik/Screen.h"
#include "atomik/Container.h"

Screen *homeScreen;

void initializeHomeScreen(Adafruit_TFTLCD *tft) {

  int amount = 5;

  homeScreen = new Screen(tft);

  for (int counter = 0; counter < amount; counter++) {    
    Container *child = new Container();
    homeScreen->appendChild(child);
  }
  
}

#endif
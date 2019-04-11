#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include "Screen.h"
#include "Container.h"

Screen *homeScreen;

void initializeHomeScreen(Adafruit_TFTLCD *tft) {

  int optAmt = 3;

  homeScreen = new Screen(tft);

  for (int counter = 0; counter < optAmt; counter++) {    
    Container *child = new Container();
    homeScreen->appendChild(child);
  }
  
}

#endif
#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include "Screen.h"
#include "Container.h"

Screen *homeScreen;

void initializeHomeScreen(Adafruit_TFTLCD *tft) {

  homeScreen = new Screen(tft);

  const int optY0 = 58;
  const int optX0 = 6;
  const int optGap = 6;
  const int optAmt = 5;
  int menuContainerW = 228;
  int menuContainerH = 46;
  int currentY = optY0;

  for (int counter = 0; counter < optAmt; counter++) {
    
    Container *child = new Container(tft, optX0, currentY, menuContainerW, menuContainerH);

    homeScreen->appendChild(child);

    currentY += menuContainerH + optGap;
  }
  
}

#endif
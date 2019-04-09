#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include "Screen.h" // home screen attributes

Screen *homeScreen;

void initializeHomeScreen(Adafruit_TFTLCD *tft) {
  homeScreen = new Screen(tft);

  
  
}

#endif
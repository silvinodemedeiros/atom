#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include "MenuScreen.h" // home screen attributes

MenuScreen *homeScreen;

void initializeHomeScreen(Adafruit_TFTLCD *tft) {
  homeScreen = new MenuScreen(tft);
}

#endif
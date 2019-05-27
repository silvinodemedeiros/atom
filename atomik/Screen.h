#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "Container.h"
#include "StyleTypes.h"

class Screen {
  protected:
    Adafruit_TFTLCD *display;
    const int marginH = 15;
    const int marginV = 20;
    const int bgColor = MAINBG;
    int wrapperW = WIDTH - marginH * 2;
    int wrapperH = HEIGHT - marginV * 2;
    
    long inputLock = 0;
    long inputWait = 200;

    fillScreen(int color) {
      display->fillScreen(color);
    };

    enum ScreenState {
      INITIAL,
      IS_UPDATING,
      TRANSITIONING_IN
    };

    ScreenState state = INITIAL;
    bool isActive = false;

  public:
    Container *wrapper;
    Container *currentOption;
    int systemState;
    bool hasTransitionOut = false;
    String name;

    Screen(Adafruit_TFTLCD *tft, DisplayStyle displayStyle = NONE) {
      boolean isActive = false;
      display = tft;
      long timeStamp = 0;

      wrapper = new Container(marginH, marginV, wrapperW, wrapperH);
      wrapper->style->display = displayStyle;
      wrapper->style->visibility = false;
      wrapper->setDisplay(tft);
      
      fillScreen(bgColor);
    }

    void manageState() {
      if (!isActive && !wrapper->isRendering()) { return; }

      wrapper->manageState();
    }

    void appendChild(Container *child) {
      child->setDisplay(display);

      child->style->x = wrapper->style->x;
      child->style->y = wrapper->style->y;
      child->style->width = wrapper->style->width;
      child->style->height = wrapper->style->height;

      wrapper->appendChild(child);
    }

    void activate() {
      isActive = true;
    }

    void deactivate() {
      wrapper->erase();
      isActive = false;
    }

    void toggle() {
      isActive = !isActive;
    }


};

#endif
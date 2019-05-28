#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "Container.h"
#include "StyleTypes.h"

class Screen {
  protected:
    Adafruit_TFTLCD *display;
    const int bgColor = MAINBG;
    
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
    const int marginH = 0;
    const int marginV = 0;
    int wrapperW = WIDTH;
    int wrapperH = HEIGHT;
    Container *wrapper;
    Container *currentOption;
    int systemState;
    String name;

    void (*transitionOut)(Screen *screen) = 0;
    void (*transitionIn)(Screen *screen) = 0;

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

      if (transitionIn) {
        transitionIn(this);
      }

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
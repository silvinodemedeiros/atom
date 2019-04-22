#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "Container.h"
#include "StyleTypes.h"

class Screen {
  private:
    const int marginH = 20;
    const int marginV = 40;
    const int bgColor = MAINBG;
    int wrapperW = WIDTH - marginH * 2;
    int wrapperH = HEIGHT - marginV * 2;
    Container *wrapper;
    Adafruit_TFTLCD *display;
    long inputWait = 0;

    fillScreen(int color) {
      display->fillScreen(color);
    };

    enum ScreenState {
      INITIAL,
      IS_UPDATING
    };

    ScreenState state = INITIAL;

  public:
    Screen(Adafruit_TFTLCD *tft, DisplayStyle displayStyle = NONE) {
      boolean isActive = false;
      display = tft;
      long timeStamp = 0;

      wrapper = new Container(marginH, marginV, wrapperW, wrapperH);
      wrapper->style->display = displayStyle;
      wrapper->style->nextAvailableY = wrapper->style->y;
      wrapper->setDisplay(tft);
      
      fillScreen(bgColor);
    }

    void manageState() {
      manageChildrenState();
      
      switch (state) {
        case IS_UPDATING:
          manageCurrentOptionInput();
          break;
        default:
          manageInput();
      }
    }

    void setState(ScreenState nextState) {
      state = nextState;
    }

    void manageInput() {
      if (selInput == HIGH) {
        // setState(IS_ITEM_SELECTING);
        // selectCurrent();
      }
      // else if (fwInput == HIGH) { focusNext(); }
      // else if (bwInput == HIGH) { focusPrevious(); }
    }

    void manageCurrentOptionInput() {
      if (retInput == HIGH) {
        // setState(IS_ITEM_UNSELECTING);
        // unselectCurrent();
      } else {
        // currentOption->manageInput();
      }
    }

    void appendChild(Container *child) {
      child->setDisplay(display);
      wrapper->appendChild(child);
    }

    void manageChildrenState() {
      wrapper->manageState(false);
    }
};

#endif
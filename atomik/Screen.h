#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "../NavigationContainer.h"
#include "Container.h"
#include "StyleTypes.h"

class Screen {
  private:
    const int marginH = 15;
    const int marginV = 20;
    const int bgColor = MAINBG;
    int wrapperW = WIDTH - marginH * 2;
    int wrapperH = HEIGHT - marginV * 2;
    Adafruit_TFTLCD *display;
    long inputLock = 0;
    long inputWait = 200;

    fillScreen(int color) {
      display->fillScreen(color);
    };

    enum ScreenState {
      INITIAL,
      IS_UPDATING
    };

    ScreenState state = INITIAL;
    NavigationContainer *currentOption;

  public:
    Container *wrapper;

    Screen(Adafruit_TFTLCD *tft, DisplayStyle displayStyle = COLUMN) {
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
      wrapper->manageState();

      switch (state) {
        case IS_UPDATING:
          break;
        default:
          manageInput();
      }
    }

    void setState(ScreenState nextState) {
      state = nextState;
    }

    void manageInput() {
      if (millis() - inputLock < inputWait) { return; }

      if (selInput == HIGH) {
        currentOption->translateY(50);
      }
      else if (retInput == HIGH) {
        currentOption->translateY(-50);
      }

      inputLock = millis();
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

    void setCurrentOption(NavigationContainer *current) {
      currentOption = current;
    }


};

#endif
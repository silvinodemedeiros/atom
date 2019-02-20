#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "MenuContainer.h"

// toolbar vars
int toolbarX = 0;
int toolbarY = 0;
int toolbarH = 12;
int toolbarW = 240;

// header data
int headerX = 0;
int headerY = 18;
int headerH = 24;
int headerW = 240;

class MenuScreen {
  private:
    static const int optAmt = 5;
    const int optY0 = 58;
    const int optX0 = 6;
    const int optGap = 6;
    const int bgColor = MAINBG;
    MenuContainer *optItems[optAmt];
    MenuContainer *currentOption;
    Adafruit_TFTLCD *display;
    long inputWait = 0;
    
    enum states {
      NEW_GAME,
      CREATE_GAME,
      MANAGE_GAMES,
      SETTINGS,
      POWER_OFF
    };

    fillScreen(int color) {
      display->fillScreen(color);
    }

  public:
    MenuScreen(Adafruit_TFTLCD *tft) {
      int counter = 0;
      int currentY = optY0;
      boolean isActive = false;
      display = tft;
      long timeStamp = 0;

      fillScreen(bgColor);
      display->drawRect(toolbarX, toolbarY, toolbarW, toolbarH, DEFAULTGREEN);
      display->drawRect(headerX, headerY, headerW, headerH, DEFAULTGREEN);
      
      while(counter < optAmt) {
        
        // MenuContainer optContainer(optX0, currentY);
        optItems[counter] = new MenuContainer(display, optX0, currentY);
        optItems[counter]->draw();

        // manages navigation chain
        if(counter > 0 && counter < optAmt) {
          optItems[counter - 1]->setNext(optItems[counter]);
          optItems[counter]->setPrevious(optItems[counter - 1]);
        }

        currentY += optItems[counter]->getHeight() + optGap;
        counter++;
      }

      // first option
      optItems[0]->setNext(optItems[1]);
      optItems[0]->setPrevious(optItems[optAmt - 1]);

      // last option
      optItems[optAmt - 1]->setNext(optItems[0]);
      optItems[optAmt - 1]->setPrevious(optItems[optAmt - 2]);

      setCurrentOption(optItems[0]);
      currentOption->focus();
    }

    void setCurrentOption(MenuContainer *container) {
      currentOption = container;
    }

    void focusNext() {
      // unfocus current option
      currentOption->unfocus();

      // swaps option and focus new option
      currentOption = currentOption->getNext();
      currentOption->focus();
      setCurrentOption(currentOption);

      inputLock = true;
      inputWait = millis();
    }

    void focusPrevious() {
      // unfocus current option
      currentOption->unfocus();

      // swaps option and focus new option
      currentOption = currentOption->getPrevious();
      currentOption->focus();
      setCurrentOption(currentOption);

      inputLock = true;
      inputWait = millis();
    }

    boolean isInputWaiting() {
      return (millis() - inputWait < INPUT_DELAY);
    }
};

#endif
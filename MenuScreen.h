#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "MenuContainer.h"

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

    fillScreen(int color) {
      display->fillScreen(color);
    };

  public:
    MenuScreen(Adafruit_TFTLCD *tft) {
      int counter = 0;
      int currentY = optY0;
      boolean isActive = false;
      display = tft;
      long timeStamp = 0;

      fillScreen(bgColor);
      
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

    boolean selectCurrent() {
      int counter = 0;
      boolean isUpperTransitioning = true;
      boolean isLowerTransitioning = true;

      for (counter = 0; counter < optAmt; counter++) {
        if (optItems[counter] == currentOption) {
          counter++;
          break;
        }

        optItems[counter]->erase();
        isUpperTransitioning = optItems[counter]->translateY(-200, -1);
        optItems[counter]->draw();
      }
      
      currentOption->erase();
      
      boolean isCurrentTranslating = currentOption->translateY(optY0, -1);
      boolean isCurrentExpandingHeight = currentOption->expandHeight(250);
      
      currentOption->draw();

      while (counter < optAmt) {
        optItems[counter]->erase();
        isLowerTransitioning = optItems[counter]->translateY(520, 1);
        optItems[counter]->draw();

        counter++;
      }

      return isCurrentTranslating && isCurrentExpandingHeight && isUpperTransitioning && isLowerTransitioning;
    }

    boolean unselectCurrent() {
      int counter = 0;
      boolean isUpperTransitioning = true;
      boolean isLowerTransitioning = true;

      for (counter = 0; counter < optAmt; counter++) {
        if (optItems[counter] == currentOption) {
          counter++;
          break;
        }

        optItems[counter]->erase();
        isUpperTransitioning = optItems[counter]->translateY(optItems[counter]->getInitY(), 1);
        optItems[counter]->draw();
      }
      
      currentOption->erase();

      boolean isCurrentTranslating = currentOption->translateY(currentOption->getInitY(), 1);
      boolean isCurrentShrinkingHeight = currentOption->shrinkHeight();
      
      currentOption->draw();

      while (counter < optAmt) {
        optItems[counter]->erase();
        isLowerTransitioning = optItems[counter]->translateY(optItems[counter]->getInitY(), -1);
        optItems[counter]->draw();

        counter++;
      }

      return isCurrentTranslating && isCurrentShrinkingHeight && isUpperTransitioning && isLowerTransitioning;
    }

    void focus() {
      currentOption->focus();
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
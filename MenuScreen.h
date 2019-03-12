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
    int menuContainerW = 228;
    int menuContainerH = 46;
    MenuContainer *optItems[optAmt];
    MenuContainer *currentOption;
    Adafruit_TFTLCD *display;
    long inputWait = 0;

    fillScreen(int color) {
      display->fillScreen(color);
    };

    enum ScreenState {
      INITIAL,
      IS_ITEM_SELECTING,
      IS_ITEM_UNSELECTING,
      IS_ITEM_SELECTED
    };

    ScreenState state = INITIAL;

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
        optItems[counter] = new MenuContainer(display, optX0, currentY, menuContainerW, menuContainerH);
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

    void manageState() {
      manageChildrenState();
      
      switch (state) {
        case IS_ITEM_SELECTED:
          Serial.println("HOME STATE - item selected");
          manageCurrentOptionInput();
          break;
        case IS_ITEM_SELECTING:
          Serial.println("HOME STATE - selecting item");
          checkSelectionProgress();
          break;
        case IS_ITEM_UNSELECTING:
          Serial.println("HOME STATE - unselecting item");
          checkSelectionProgress();
          break;
        default:
          Serial.println("HOME STATE - initial");
          manageInput();
      }
    }

    void setState(ScreenState nextState) {
      state = nextState;
    }

    void manageInput() {
      if (selInput == HIGH) {
        setState(IS_ITEM_SELECTING);
        selectCurrent();
      }
      else if (fwInput == HIGH) { focusNext(); }
      else if (bwInput == HIGH) { focusPrevious(); }
    }

    void manageCurrentOptionInput() {
      if (retInput == HIGH) {
        setState(IS_ITEM_UNSELECTING);
        unselectCurrent();
      }
    }

    void manageChildrenState() {
      for (int i = 0; i < optAmt; i++) {
        optItems[i]->manageState();
      }
    }

    void setCurrentOption(MenuContainer *container) {
      currentOption = container;
    }

    boolean selectCurrent() {
      int counter = 0;

      for (counter = 0; counter < optAmt; counter++) {
        // stops if it arrives in the current selected item
        if (optItems[counter] == currentOption) { break; }
        optItems[counter]->translateY(-200, -1);
      }

      currentOption->select();
      counter++;

      while (counter < optAmt) {
        optItems[counter]->translateY(520, 1);
        counter++;
      }

      inputLock = true;
      inputWait = millis();
    }

    boolean unselectCurrent() {
      int counter = 0;

      for (counter = 0; counter < optAmt; counter++) {
        // stops if it arrives in the current selected item
        if (optItems[counter] == currentOption) { break; }
        optItems[counter]->translateY(optItems[counter]->getInitY(), 1);
      }

      currentOption->unselect();
      counter++;

      while (counter < optAmt) {
        optItems[counter]->translateY(optItems[counter]->getInitY(), -1);
        counter++;
      }

      inputLock = true;
      inputWait = millis();
    }

    checkSelectionProgress() {

      int counter = 0;
      boolean isRendering = false;

      for (counter = 0; counter < optAmt; counter++) {
        isRendering = optItems[counter]->isRendering();
      }

      if (!isRendering) {
        if (state == IS_ITEM_SELECTING) {
          setState(IS_ITEM_SELECTED);
        } else {
          setState(INITIAL);
        }
      } else {
        inputLock = true;
        inputWait = millis();
      }
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
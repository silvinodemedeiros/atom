#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "Container.h"

class Screen {
  private:
    static const int optAmt = 5;
    const int optY0 = 58;
    const int optX0 = 6;
    const int optGap = 6;
    const int bgColor = MAINBG;
    int menuContainerW = 228;
    int menuContainerH = 46;
    Container *children[optAmt];
    Container *currentOption;
    Container *wrapper;
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
    Screen(Adafruit_TFTLCD *tft) {
      boolean isActive = false;
      display = tft;
      long timeStamp = 0;

      wrapper = new Container(display, optX0, optY0, menuContainerW, menuContainerH);

      fillScreen(bgColor);

      // // first option
      // children[0]->setNext(children[1]);
      // children[0]->setPrevious(children[optAmt - 1]);

      // // last option
      // children[optAmt - 1]->setNext(children[0]);
      // children[optAmt - 1]->setPrevious(children[optAmt - 2]);

      // setCurrentOption(children[0]);
      // currentOption->focus();

    }

    void manageState() {
      manageChildrenState();
      
      switch (state) {
        case IS_ITEM_SELECTED:
          manageCurrentOptionInput();
          break;
        case IS_ITEM_SELECTING:
          checkSelectionProgress();
          break;
        case IS_ITEM_UNSELECTING:
          checkSelectionProgress();
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
      wrapper->appendChild(child);
    }

    void manageChildrenState() {
      wrapper->manageState(false);
    }

    void setCurrentOption(Container *container) {
      currentOption = container;
    }

    boolean selectCurrent() {
      int counter = 0;

      for (counter = 0; counter < optAmt; counter++) {
        // stops if it arrives in the current selected item
        if (children[counter] == currentOption) { break; }
        children[counter]->translateY(-200, -1);
      }

      currentOption->select();
      counter++;

      while (counter < optAmt) {
        children[counter]->translateY(520, 1);
        counter++;
      }

      inputLock = true;
      inputWait = millis();
    }

    boolean unselectCurrent() {
      int counter = 0;

      for (counter = 0; counter < optAmt; counter++) {
        // stops if it arrives in the current selected item
        if (children[counter] == currentOption) { break; }
        children[counter]->translateY(children[counter]->getInitY(), 1);
      }

      currentOption->unselect();
      counter++;

      while (counter < optAmt) {
        children[counter]->translateY(children[counter]->getInitY(), -1);
        counter++;
      }

      inputLock = true;
      inputWait = millis();
    }

    checkSelectionProgress() {

      int counter = 0;
      boolean isRendering = false;

      for (counter = 0; counter < optAmt; counter++) {
        isRendering = children[counter]->isRendering();
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
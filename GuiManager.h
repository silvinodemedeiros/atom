#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "atomik/Screen.h"

#include "states.h"
#include "input.h"
#include "renderHomescreen.h"
#include "renderItemscreen.h"

class GuiManager {

  public:
    Screen *currentScreen = 0;
    Screen **screenSet;
    int screenAmt = 0;

    bool hasLoaded = false;
    bool inputLock = false;
    int lastInput = 0;
    int inputWait = 500;

    int systemState = SYSTEM_INITIAL;

    GuiManager(Adafruit_TFTLCD *tft) {
      initHomeScreen(tft);
      initItemScreen(tft);
    };

    bool isInputReleased () {
      if (fwInput != -1 && bwInput != -1 && selInput != -1 && retInput != -1)
        return fwInput == LOW && bwInput == LOW && selInput == LOW && retInput == LOW;
    }

    void activate(int nextState) {
      
      inputLock = true;
      hasLoaded = false;
      systemState = nextState;

      if (currentScreen) {
        currentScreen->deactivate();
      }
    }

    void appendScreen(Screen *screen) {

    }

    void manageApplication() {
      manageInput();
      manageState();
    }

    void manageInput() {

      //read the pushbutton value into a variable
      bwInput = digitalRead(bw);
      fwInput = digitalRead(fw);
      selInput = digitalRead(sel);
      retInput = digitalRead(ret);

      if (millis() - lastInput < inputWait) { return; }

      if (selInput == HIGH) {
        activate(currentScreen->currentOption->nextSystemState);
        lastInput = millis();
      }

      else if (fwInput == HIGH) {
        currentScreen->currentOption = currentScreen->currentOption->focusNext();
        lastInput = millis();
      }

      else if (bwInput == HIGH) {
        currentScreen->currentOption = currentScreen->currentOption->focusPrevious();
        lastInput = millis();
      }
      
    }

    void manageState() {
      if (systemState == SYSTEM_INITIAL) {
        if (hasLoaded == false) {
          activate(HOME_STATE);
        }
      }

      // home
      else if (systemState == HOME_STATE) {
        if (hasLoaded == false) {
          currentScreen = homeScreen;
          homeScreen->activate();
          hasLoaded = true;
        } else {
          if (isInputReleased()) {
            inputLock = false;
          }
        }

        if (inputLock == false) {
          homeScreen->manageState();
        }
      }

      // item
      else if (systemState == ITEM_STATE) {
        if (hasLoaded == false) {
          currentScreen = itemScreen;
          itemScreen->activate();
          hasLoaded = true;
        } else {
          if (isInputReleased()) {
            inputLock = false;
          }
        }

        if (inputLock == false) {
          itemScreen->manageState();
        }
      }
    }
    
};

#endif
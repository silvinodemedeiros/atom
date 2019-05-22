#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "atomik/Screen.h"

#include "states.h"
#include "input.h"

class GuiManager {

  public:
    Screen *currentScreen = 0;
    Screen **screenSet;
    int screenAmt = 0;

    bool hasLoaded = false;
    bool inputLock = false;
    long lastInput = 0;
    int inputWait = 500;

    int systemState;

    GuiManager() {};

    bool isInputReleased () {
      if (fwInput != -1 && bwInput != -1 && selInput != -1 && retInput != -1)
        return fwInput == LOW && bwInput == LOW && selInput == LOW && retInput == LOW;
    }

    void activate(int nextState) {
      
      if (currentScreen) {
        currentScreen->deactivate();
      }

      inputLock = true;
      hasLoaded = false;
      systemState = nextState;

      for (int i = 0; i < screenAmt; i++) {
        if (screenSet[i]->systemState == systemState) {
          currentScreen = screenSet[i];
          break;
        }
      }

      currentScreen->activate();
    }

    void appendScreen(Screen *screen) {
      Screen **newScreenSet = new Screen*[screenAmt + 1];

      int i = 0;
      while (i < screenAmt) {
        newScreenSet[i] = screenSet[i];
        i++;
      }

      newScreenSet[i] = screen;
      screenSet = newScreenSet;
      screenAmt++;
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
        if (currentScreen->currentOption->nextSystemState != -1) {
          activate(currentScreen->currentOption->nextSystemState);
          lastInput = millis();
        } else {
          currentScreen->currentOption->manageSelection(currentScreen->currentOption);
          lastInput = millis();
        }

      }

      else if (fwInput == HIGH) {
        currentScreen->currentOption = currentScreen->currentOption->focusNext();
        lastInput = millis();
      }

      else if (bwInput == HIGH) {
        currentScreen->currentOption = currentScreen->currentOption->focusPrevious();
        lastInput = millis();
      }

      else if (retInput == HIGH) {
        currentScreen->currentOption->manageReturn(currentScreen->currentOption);
        lastInput = millis();
      }
    }

    void manageState() {

      switch (currentScreen->systemState) {
        case HOME_STATE:
          Serial.println("HOME_STATE");
        break;
        case ITEM_STATE:
          Serial.println("ITEM_STATE");
        break;
      }

      if (hasLoaded == false) {
        activate(systemState);
        hasLoaded = true;
      } else {
        if (isInputReleased()) {
          inputLock = false;
        }
      }

      if (inputLock == false) {
        currentScreen->manageState();
      }
    }
    
};

#endif
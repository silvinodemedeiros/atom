#include <SPFD5408_Adafruit_GFX.h>		// graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // hardware specific library

long playerStallTime = 33;
unsigned long playerStallPrev = 0;
#include "constants.h"							// useful project constants
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#include "colors.h" 								// color set
#include "states.h"									// machine states
#include "shared.h"									// useful functions
#include "input.h" 									// input ports

#include "renderHomescreen.h"
#include "renderGamescreen.h"

void goToState (int nextState) {
	inputLock = true;
	hasLoaded = false;
	state = nextState;
}

bool isInputReleased () {
	if (fwInput != -1 && bwInput != -1 && selInput != -1 && retInput != -1)
		return fwInput == LOW && bwInput == LOW && selInput == LOW && retInput == LOW;
}

void setup() {
	tft.reset();
	tft.begin(0x9341);
	tft.setRotation(rot);
	state = INITIAL;

	Serial.begin(9600);

	pinMode(bw, INPUT_PULLUP);
	pinMode(fw, INPUT_PULLUP);
	pinMode(sel, INPUT_PULLUP);
	pinMode(ret, INPUT_PULLUP);
}

void loop() {
	//read the pushbutton value into a variable
	bwInput = digitalRead(bw);
	fwInput = digitalRead(fw);
	selInput = digitalRead(sel);
	retInput = digitalRead(ret);

	long currentMillis = millis();
	
	if (state == INITIAL) {
		if (hasLoaded == false) {
			goToState(HOME_STATE);
		}
	}

	// home
	else if (state == HOME_STATE) {
		Serial.println("HOME_STATE");
		if (hasLoaded == false) {
			initializeHomeScreen(&tft);
			hasLoaded = true;
		} else {
			if (isInputReleased()) {
				inputLock = false;
			}
		}

		if (inputLock == false || !homeScreen->isInputWaiting()) {
			if (selInput == HIGH) { goToState(HOME_SELECT); }
			else if (fwInput == HIGH) { homeScreen->focusNext(); }
			else if (bwInput == HIGH) { homeScreen->focusPrevious(); }
		}
	}
	
	// home -> item_selected
	else if (state == HOME_SELECT) {
		Serial.println("HOME_SELECT");
		if (homeScreen->selectCurrent()) {
			goToState(ITEM_SELECTED);
		}
	}
	
	// home -> item_selected
	else if (state == HOME_UNSELECT) {
		Serial.println("HOME_UNSELECT");
		if (homeScreen->unselectCurrent()) {
			goToState(HOME_STATE);
			homeScreen->focus();
			hasLoaded = true;
		}
	}

	else if (state == ITEM_SELECTED) {
		Serial.println("ITEM_SELECTED");
		if (hasLoaded == false) {
			hasLoaded = true;
		} else {
			if (isInputReleased()) {
				inputLock = false;
			}
		}

		if (inputLock == false || !homeScreen->isInputWaiting()) {
			if (retInput == HIGH) {
				goToState(HOME_UNSELECT);
				hasLoaded = true;
			}
		}
	}

	// game
	if (state == GAME_STATE) {
		if (hasLoaded == false) {
			initializeGameScreen(&tft);
			hasLoaded = true;
		} else if (isInputReleased()) {

			gameScreen->animate();
			playerStallPrev = currentMillis;
			
			inputLock = false;
		}

		if (inputLock == false) {
			if (retInput == HIGH) {
				goToState(HOME_STATE);
			}
		}

		if (currentMillis - playerStallPrev >= playerStallTime) {
			gameScreen->animate();
			playerStallPrev = currentMillis;
		}
	}

	// game -> home
	else if (state == FROM_GAME_TO_HOME) {
		if (hasLoaded == false) {
			goToState(HOME_STATE);
		}
	}
		
}


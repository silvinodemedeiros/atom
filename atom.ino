#include <SPFD5408_Adafruit_GFX.h>
#include <SPFD5408_Adafruit_TFTLCD.h>

#include "constants.h"							// useful project constants
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#include "colors.h" 								// color set
#include "states.h"									// machine states
#include "shared.h"									// useful functions
#include "input.h" 									// input ports

#include "renderHomescreen.h"
#include "renderItemscreen.h"

bool isInputReleased () {
	if (fwInput != -1 && bwInput != -1 && selInput != -1 && retInput != -1)
		return fwInput == LOW && bwInput == LOW && selInput == LOW && retInput == LOW;
}

void setup() {
	srand((unsigned)millis());
	tft.reset();
	tft.begin(0x9341);
	tft.setRotation(rot);
	systemState = SYSTEM_INITIAL;

	Serial.begin(9600);

	pinMode(bw, INPUT_PULLUP);
	pinMode(fw, INPUT_PULLUP);
	pinMode(sel, INPUT_PULLUP);
	pinMode(ret, INPUT_PULLUP);

	randomSeed(analogRead(0));

	initHomeScreen(&tft);
	initItemScreen(&tft);
}

void loop() {

	switch (systemState) {
		case HOME_STATE:
			Serial.println("HOME_STATE");
		break;
		case ITEM_STATE:
			Serial.println("ITEM_STATE");
		break;
	}

	//read the pushbutton value into a variable
	bwInput = digitalRead(bw);
	fwInput = digitalRead(fw);
	selInput = digitalRead(sel);
	retInput = digitalRead(ret);
	
	if (systemState == SYSTEM_INITIAL) {
		if (hasLoaded == false) {
			goToState(HOME_STATE);
		}
	}

	// home
	else if (systemState == HOME_STATE) {
		if (hasLoaded == false) {
			itemScreen->deactivate();
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
			homeScreen->deactivate();
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


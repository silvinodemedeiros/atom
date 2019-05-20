#include <SPFD5408_Adafruit_GFX.h>
#include <SPFD5408_Adafruit_TFTLCD.h>

#include "constants.h"							// useful project constants

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#include "colors.h" 								// color set
#include "states.h"									// machine states
#include "input.h" 									// input ports
#include "shared.h"									// useful functions

#include "GuiManager.h"

GuiManager *guiMgr;

void setup() {
	srand((unsigned)millis());
	tft.reset();
	tft.begin(0x9341);
	tft.setRotation(rot);
	guiMgr->systemState = SYSTEM_INITIAL;

	Serial.begin(9600);

	pinMode(bw, INPUT_PULLUP);
	pinMode(fw, INPUT_PULLUP);
	pinMode(sel, INPUT_PULLUP);
	pinMode(ret, INPUT_PULLUP);

	randomSeed(analogRead(0));

	guiMgr = new GuiManager(&tft);
}

void loop() {

	switch (guiMgr->systemState) {
		case HOME_STATE:
			Serial.println("HOME_STATE");
		break;
		case ITEM_STATE:
			Serial.println("ITEM_STATE");
		break;
	}

	guiMgr->manageApplication();

}


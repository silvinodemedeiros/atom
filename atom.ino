#include <SPFD5408_Adafruit_GFX.h>
#include <SPFD5408_Adafruit_TFTLCD.h>

#include "constants.h"							// useful project constants

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#include "colors.h" 								// color set
#include "states.h"									// machine states
#include "input.h" 									// input ports

#include "atomik/Screen.h"
#include "atomik/GuiManager.h"

#include "ItemScreen.h"
#include "initHomeScreen.h"

GuiManager *guiMgr;

void setup() {
	tft.reset();
	tft.begin(0x9341);
	tft.setRotation(2);

	pinMode(bw, INPUT_PULLUP);
	pinMode(fw, INPUT_PULLUP);
	pinMode(sel, INPUT_PULLUP);
	pinMode(ret, INPUT_PULLUP);

	guiMgr = new GuiManager();

	Screen *homeScreen = new Screen(&tft);

	ItemScreen *firstScreen = new ItemScreen(
		&tft, FIRST_STATE, "First Screen", "Content Here");

	ItemScreen *secondScreen = new ItemScreen(
		&tft, SECOND_STATE, "Second Screen", "Another Content");

	ItemScreen *thirdScreen = new ItemScreen(
		&tft, THIRD_STATE, "Third Screen", "Third Content");

	initHomeScreen(homeScreen);

	guiMgr->appendScreen(homeScreen);
	guiMgr->appendScreen(firstScreen);
	guiMgr->appendScreen(secondScreen);
	guiMgr->appendScreen(thirdScreen);

	guiMgr->systemState = HOME_STATE;
}

void loop() {

	guiMgr->manageApplication();

}


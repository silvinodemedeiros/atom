
#include "GameScreen.h"
GameScreen *gameScreen;

void initializeGameScreen (Adafruit_TFTLCD *tft) {
	gameScreen = new GameScreen(tft);
}
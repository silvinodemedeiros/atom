#include "Player.h"
#include "Tile.h"
#include "Ball.h"

#ifndef GAMESCREEN_H
#define GAMESCREEN_H

class GameScreen {

	private:
		int tileRegW = WIDTH;
		int tileRegH = 150;
		static const int tileCols = 10;
		static const int tileRows = 10;
		int tileW = tileRegW / tileCols;
		int tileH = tileRegH / tileRows;
		int bgColor = MAINBG;
		Adafruit_TFTLCD *display;
		Ball *ball;
		Player *player;
		
	public:
		GameScreen(Adafruit_TFTLCD *tft) {
			display = tft;
			display->fillScreen(bgColor);

			player = new Player(tft);
			ball = new Ball(tft);

			player->draw();
		}

		void animate() {
			player->move();
			ball->animate(player);
		}

};

#endif

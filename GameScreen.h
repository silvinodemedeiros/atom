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
		Tile *tiles[tileRows][tileCols];
		Adafruit_TFTLCD *display;
		Ball *ball;
		Player *player;
		Tile *collisionSetHead;
		
	public:
		GameScreen(Adafruit_TFTLCD *tft) {
			display = tft;
			display->fillScreen(bgColor);
			drawTiles();

			player = new Player(tft);
			ball = new Ball(tft, collisionSetHead);

			player->draw();
		}

		void animate() {
			player->move();
			ball->animate(player);
		}

		void drawTiles() {
			int currentX = 0;
			int currentY = 0;

			collisionSetHead = new Tile(display, -100, -100, 5, 5);

			for (int i = 0; i < tileRows; i++) {
				currentY = i * tileH;

				for (int j = 0; j < tileCols; j++) {
					currentX = j * tileW;
					tiles[i][j] = new Tile(display, currentX, currentY, tileW, tileH);
					tiles[i][j]->draw();
				}

			}

			for (int i = 0; i < tileRows; i++) {
				for (int j = 0; j < tileCols; j++) {
					if (i - 1 >= 0) { tiles[i][j]->setUp(tiles[i-1][j]); }
					if (j + 1 < tileCols) { tiles[i][j]->setRight(tiles[i][j+1]); }
					if (i + 1 < tileRows) { tiles[i][j]->setDown(tiles[i+1][j]); }
					if (j - 1 >= 0) { tiles[i][j]->setLeft(tiles[i][j-1]); }
				}
			}

			createCollisionSet();

		}

		void createCollisionSet () {
			int row = tileRows-1;
			int i = 0;

			collisionSetHead->setNextOnCollision(tiles[row][0]);

			for (i = 1; i < tileCols - 1; i++) {
				tiles[row][i]->setNextOnCollision(tiles[row][i+1]);
			}

			tiles[row][i]->setNextOnCollision(NULL);
		}

		void removeTiles () {
			int currentX = 0;
			int currentY = 0;

			for (int i = 0; i < tileCols; i++) {
				currentX = i * tileW;
				for (int j = 0; j < tileRows; j++) {
					currentY = j * tileH;
					tiles[i][j]->remove();
					delete tiles[i][j];
				}
			}
		}

};

#endif

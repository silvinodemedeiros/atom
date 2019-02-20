#include "constants.h"
#include "colors.h"
#include "input.h"
#include "shared.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player {

	private:
		int bottomMargin = 50;
		int width = 100;
		int height = 10;
		int initPosX = (WIDTH/2) - (width / 2);
		int initPosY = HEIGHT - bottomMargin;
		int posX = initPosX;
		int posY = initPosY;
		int dir = 1;
		int speed = 10;
		int border = 1;
		int color = DEFAULTGREEN;
		int bgColor = MAINBG;
		Adafruit_TFTLCD *display;

		boolean checkOverlapingX(int x);
		boolean checkOverlapingY(int y);

	public:
		Player(Adafruit_TFTLCD *tft) ;

		int getPosX ();
		int getPosY();
		int getWidth();
		int getHeight();
		int getBorder();
	
		void draw ();

		void remove ();

		void move ();

		boolean verifyCollision(int ox, int oy);
};

#endif
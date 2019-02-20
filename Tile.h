#ifndef TILE_H
#define TILE_H

class Tile {
	private:
		int posX = -1;
		int posY = -1;
		int width = -1;
		int height = -1;
		int tileColor = DEFAULTGREEN;
		int bgColor = MAINBG;
		Adafruit_TFTLCD *display;
		Tile *up;
		Tile *down;
		Tile *left;
		Tile *right;
		Tile *prevOnCollision;
		Tile *nextOnCollision = NULL;

	public:
		Tile(Adafruit_TFTLCD *tft, int x, int y, int w, int h) {
			display = tft;
			posX = x;
			posY = y;
			width = w;
			height = h;
		}

		void draw() {
			display->drawRect(posX, posY, width, height, tileColor);
		}

		void remove() {
			// TODO: will summon explosion object after self destructs

			display->drawRect(posX, posY, width, height, bgColor);
			// delete this;
		}

		int getWidth () { return width; }
		Tile* getUp () { return up; }
		Tile* getDown () { return down; }
		Tile* getLeft () { return left; }
		Tile* getRight () { return right; }
		Tile* getNextOnCollision () { return nextOnCollision; }
		Tile* getPreviousOnCollision () { return prevOnCollision; }

		void setUp(Tile* u) { up = u; }
		void setDown(Tile* d) { down = d; }
		void setLeft(Tile* l) { left = l; }
		void setRight(Tile* r) { right = r; }
		void setNextOnCollision(Tile *noc) { nextOnCollision = noc; }
		void setPreviousOnCollision(Tile *poc) { prevOnCollision = poc; }

		boolean checkOverlapingX(int x) {

			boolean overlap = (x >= posX) && (x <= posX + width);

			return overlap;
		}

		boolean checkOverlapingY(int y) {

			boolean overlap = (y >= posY) && (y <= posY + width);

			return overlap;
		}

		boolean verifyCollision(int ox, int oy) {
			return checkOverlapingX(ox) && checkOverlapingY(oy);
		}
};

#endif
#include <SPFD5408_Adafruit_GFX.h>		// graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // hardware specific library
#include "Player.h"

#ifndef PLAYER_CPP
#define PLAYER_CPP

boolean Player::checkOverlapingX(int x) {

  boolean overlap = (x >= posX - border) && (x <= posX + border + width);

  return overlap;
}

boolean Player::checkOverlapingY(int y) {

	boolean overlap = (y >= posY - border) && (y <= posY + border + width);

	return overlap;
}

Player::Player(Adafruit_TFTLCD *tft) {
	display = tft;
	draw();
}

int Player::getPosX () {
	return posX;
}

int Player::getPosY() {
	return posY;
}

int Player::getWidth() {
	return width;
}

int Player::getHeight() {
	return height;
}

int Player::getBorder() {
	return border;
}

void Player::draw () {
	display->drawRect(posX, posY, width, height, color);
}

void Player::remove () {
	display->drawRect(posX, posY, width, height, bgColor);
}

void Player::move () {
	int length = 0;

	// get direction based on input
	if (bwInput == HIGH) {
		dir = -1;
		length = speed;
	}
	else if (fwInput == HIGH) {
		dir = 1;
		length = speed;
	}

	// gets player edge based on direction
	int edgeRight = posX + width + border;
	int edgeLeft = posX - border;

	// updates position if player is on screen
	if (edgeRight < WIDTH && edgeLeft > 0 && length != 0) {
		remove();
		posX += length * dir;

		// brings player westwards
		while (posX + width + border >= WIDTH) {
			posX--;
		}

		// brings player eastwards
		while (posX - border <= 0) {
			posX++;
		}

		draw();
	}
}

boolean Player::verifyCollision(int ox, int oy) {
	return checkOverlapingX(ox) && checkOverlapingY(oy);
}

#endif
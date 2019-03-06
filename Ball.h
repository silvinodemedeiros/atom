#include "Player.h"
#include "Tile.h"

#ifndef BALL_H
#define BALL_H

class Ball {

  private:
    int speed = 7;
    int initDirH = 1;
    int initDirV = -1;
    int dirH = initDirH;
    int dirV = initDirV;
    int initPosX = (WIDTH/2);
    int initPosY = (HEIGHT/2) + 50;
    int posX = initPosX;
    int posY = initPosY;
    int nextPosX = initPosX;
    int nextPosY = initPosY;
    int ballRadius = 10;
    int ballBorder = 1;
    int ballColor = DEFAULTGREEN;
    int bgColor = MAINBG;
    Adafruit_TFTLCD* display;

  public:
    Ball(Adafruit_TFTLCD *tft) {
      display = tft;
    }

    void draw() {
      for (int i = 0; i < ballBorder; i++)  {
        display->drawCircle(nextPosX, nextPosY, ballRadius - i, ballColor);
      }
    }

    void remove() {
      for (int i = 0; i < ballBorder; i++) {
        display->drawCircle(posX, posY, ballRadius - i, bgColor);
      }
    }

    void setNextPosY (Player *player) {
      // gets ball bottom edge point
      int ballEdgeBottom = posY + ballRadius + ballBorder;
      int ballEdgeTop = posY - ballRadius - ballBorder;

      // check player collision to change direction
      if (player->verifyCollision(posX, ballEdgeBottom)) { dirV = -1; }
      // check top wall collision
      else if (ballEdgeTop <= 0) { dirV = 1; }

      // get next position based on direction
      nextPosY += speed * dirV;
    }

    void setNextPosX () {
      // check wall collision to reverse direction
      if (posX + ballRadius + ballBorder >= WIDTH) {
        dirH = -1;
      } else if (posX - ballRadius - ballBorder <= 0) {
        dirH = 1;
      }

      // get next position based on direction
      nextPosX += speed * dirH;
    }

    void animate (Player *player) {
      setNextPosX();
      setNextPosY(player);

      remove();
      draw();

      // updates position variables
      posX = nextPosX;
      posY = nextPosY;
    }
  
};

#endif
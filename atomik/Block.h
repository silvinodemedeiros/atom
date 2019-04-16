#ifndef BLOCK_H
#define BLOCK_H

#include <SPFD5408_Adafruit_GFX.h>
#include <SPFD5408_Adafruit_TFTLCD.h>

class Block {

  protected:
    Adafruit_TFTLCD *display;

    // states
    enum BlockState {
      INITIAL,
      IS_TRANSITIONING_Y,
      IS_TRANSITIONING_X,
      IS_EXPANDING_HEIGHT,
      IS_EXPANDING_WIDTH,
      IS_SHRINKING_HEIGHT,
      DONE_RENDER
    };

    BlockState state = INITIAL;

    // static attributes
    int x = 0;
    int initX = 0;
    int y = 0;
    int initY = 0;
    int width = 0;
    int initWidth = 0;
    int height = 0;
    int initHeight = 0;
    int borderColor = DEFAULTGREEN;
    int bgColor = MAINBG;
    
    // animation attributes
    int translationToY = -1;
    int translationDirY = 0;
    int translationStep = 30;
    int expansionHeightStep = 30;
    int expansionToHeight = -1;

  public:
    Block(int ux, int uy, int w, int h) {
      x = ux;
      y = uy;
      initX = x;
      initY = y;
      width = w;
      height = h;
      initWidth = width;
      initHeight = height;
    }

    // for array initialization
    Block() {}

    void draw() {
      display->drawRect(x, y, width, height, borderColor);
    }

    void erase() {
      display->drawRect(x, y, width, height, bgColor);
    }

    int getHeight() {
      return height;
    }

    int getWidth() {
      return width;
    }

    int getInitHeight() {
      return initHeight;
    }

    int getInitWidth() {
      return initWidth;
    }

    int getInitY() {
      return initY;
    }

    int getInitX() {
      return initX;
    }
    
    int getX () {
      return x;
    }

    int getY() {
      return y;
    }
    
    void setDisplay(Adafruit_TFTLCD *tft) {
      display = tft;
    }
    
    void setX (int nx) {
      x = nx;
    }

    void setY(int ny) {
      y = ny;
    }

    void setWidth(int w) {
      width = w;
    }

    void setHeight(int h) {
      height = h;
    }

    void setBorderColor(int bc) {
      borderColor = bc;
    }

    void setState(BlockState nextState) {
      state = nextState;
    }

    boolean isRendering() {
      return state != INITIAL;
    }

    /* USR= NEEDS TO BE USER IMPLEMENTED */
    void manageInput() {}

    void manageState() {
      
      switch(state) {
        case IS_TRANSITIONING_Y:
          stepTranslationY();
          break;
        case IS_EXPANDING_HEIGHT:
          stepExpansionHeight();
          break;
        case DONE_RENDER:
          setState(INITIAL);
          break;
        case INITIAL:
          draw();
          break;
      }
    }

    // BASIC ANIMATIONS
    void translateY(int toY, int dir) {
      translationToY = toY;
      translationDirY = dir;

      setState(IS_TRANSITIONING_Y);
    }

    void stepTranslationY() {

      erase();

      // downward translation
      if (translationDirY == 1) {

        y += translationStep;

        // is animation done?
        if (y > translationToY) {
          y = translationToY;
          translationToY = -1;
          translationDirY = 0;
          
          setState(DONE_RENDER);
        }
      }

      // upwards translation
      else {
        y -= translationStep;

        // is animation done?
        if (y < translationToY) {
          y = translationToY;
          translationToY = -1;
          translationDirY = 0;
          
          setState(DONE_RENDER);
        }
      }

      draw();
    }

    void startExpansionHeight(int toHeight) {
      expansionToHeight = toHeight;
      setState(IS_EXPANDING_HEIGHT);
    }

    void stepExpansionHeight () {

      erase();

      height += expansionHeightStep;

      if (height >= expansionToHeight) {
        height = expansionToHeight;
        expansionToHeight = -1;

        setState(DONE_RENDER);
      }

      draw();
    }

    boolean shrinkHeight () {

      height -= expansionHeightStep;
    
      if (height < initHeight) {
        height = initHeight;
        return true;
      }

      return false;

    }

};


#endif
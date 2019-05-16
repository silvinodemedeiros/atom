#ifndef BLOCK_H
#define BLOCK_H

#include <SPFD5408_Adafruit_GFX.h>
#include <SPFD5408_Adafruit_TFTLCD.h>
#include "Style.h"

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
      IS_SHRINKING_WIDTH,
      IS_SHRINKING_HEIGHT,
      DONE_RENDER
    };

    BlockState state = INITIAL;
    
    // animation attributes
    int translationDeltaY = 0;
    int translationToY = -1;
    int translationDirY = 0;
    int translationStep = 5;
    int expansionHeightStep = 30;
    int expansionToHeight = -1;

    int BlockId = 0;

  public:

    Style *style;

    Block(int ux, int uy, int w, int h) {
      style = new Style();

      style->x = ux;
      style->y = uy;
      style->nextAvailableY = uy;
      style->initX = ux;
      style->initY = uy;
      style->width = w;
      style->height = h;
      style->initWidth = w;
      style->initHeight = h;
    }

    // for array initialization
    Block() {}

    void draw() {
      if (style->visibility) {
        display->drawRect(style->x, style->y, style->width, style->height, style->borderColor);
      }
    }

    void erase() {
      display->drawRect(style->x, style->y, style->width, style->height, style->bgColor);
    }

    int getHeight() {
      return style->height;
    }

    int getWidth() {
      return style->width;
    }

    int getInitHeight() {
      return style->initHeight;
    }

    int getInitWidth() {
      return style->initWidth;
    }

    int getInitY() {
      return style->initY;
    }

    int getInitX() {
      return style->initX;
    }
    
    int getX () {
      return style->x;
    }

    int getY() {
      return style->y;
    }
    
    void setDisplay(Adafruit_TFTLCD *tft) {
      display = tft;
    }
    
    void setX (int nx) {
      style->x = nx;
    }

    void setY(int ny) {
      style->y = ny;
    }

    void setWidth(int w) {
      style->width = w;
    }

    void setHeight(int h) {
      style->height = h;
    }

    void setBorderColor(int bc) {
      style->borderColor = bc;
    }

    void setState(BlockState nextState) {
      state = nextState;
    }

    boolean isRendering() {
      return state != INITIAL;
    }

    void manageState() {
      
      switch(state) {
        case IS_TRANSITIONING_Y:
          stepTranslationY();
          Serial.println("TRANSITIONING Y");
          break;
        case IS_EXPANDING_HEIGHT:
          // stepExpansionHeight();
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
    // void translateY(int toY, int dir) {
    void translateY(int deltaY) {
      translationDeltaY = deltaY;
      style->initY = style->y;
      // translationToY = toY;
      // translationDirY = dir;

      setState(IS_TRANSITIONING_Y);
    }

    void stepTranslationY() {

      erase();

      // downward translation
      // if (translationDirY == 1) {
      if (translationDeltaY > 0) {

        style->y += translationStep;

        // is animation done?
        if (style->y - style->initY > translationDeltaY) {
          style->y = style->initY + translationDeltaY;
          // style->y = translationToY;
          // translationToY = -1;
          // translationDirY = 0;
          
          setState(DONE_RENDER);
        }
      }

      // upwards translation
      else {
        style->y -= translationStep;

        // is animation done?
        if (style->y - style->initY < translationDeltaY) {
          style->y = style->initY + translationDeltaY;
          // style->y = translationToY;
          // translationToY = -1;
          // translationDirY = 0;
          
          setState(DONE_RENDER);
        }
      }

      draw();
    }

    // void startExpansionHeight(int toHeight) {
    //   expansionToHeight = toHeight;
    //   setState(IS_EXPANDING_HEIGHT);
    // }

    // void stepExpansionHeight () {

    //   erase();

    //   height += expansionHeightStep;

    //   if (height >= expansionToHeight) {
    //     height = expansionToHeight;
    //     expansionToHeight = -1;

    //     setState(DONE_RENDER);
    //   }

    //   draw();
    // }

    // boolean shrinkHeight () {

    //   height -= expansionHeightStep;
    
    //   if (height < initHeight) {
    //     height = initHeight;
    //     return true;
    //   }

    //   return false;

    // }

};


#endif
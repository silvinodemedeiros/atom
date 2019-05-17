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
    int translationDeltaX = 0;
    int translationStep = 15;
    int expansionHeightStep = 15;
    int expansionDeltaHeight = -1;

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
    Block() {
      style = new Style();
    }

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
          break;
        case IS_TRANSITIONING_X:
          stepTranslationX();
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

    void translateY(int deltaY) {
      translationDeltaY = deltaY;
      style->initY = style->y;
      setState(IS_TRANSITIONING_Y);
    }

    void stepTranslationY() {

      erase();

      if (translationDeltaY > 0) {

        style->y += translationStep;

        // is animation done?
        if (style->y - style->initY > translationDeltaY) {
          style->y = style->initY + translationDeltaY;
          setState(DONE_RENDER);
        }
      }

      // upwards translation
      else {
        style->y -= translationStep;

        // is animation done?
        if (style->y - style->initY < translationDeltaY) {
          style->y = style->initY + translationDeltaY;
          setState(DONE_RENDER);
        }
      }

      draw();
    }

    void translateX(int deltaX) {
      translationDeltaX = deltaX;
      style->initX = style->x;
      setState(IS_TRANSITIONING_X);
    }

    void stepTranslationX() {

      erase();

      if (translationDeltaX > 0) {

        style->x += translationStep;

        // is animation done?
        if (style->x - style->initX > translationDeltaX) {
          style->x = style->initX + translationDeltaX;
          setState(DONE_RENDER);
        }
      }

      // upwards translation
      else {
        style->x -= translationStep;

        // is animation done?
        if (style->x - style->initX < translationDeltaX) {
          style->x = style->initX + translationDeltaX;
          setState(DONE_RENDER);
        }
      }

      draw();
    }

    void expandHeight(int deltaH) {
      expansionDeltaHeight = deltaH;
      style->initHeight = style->height;
      setState(IS_EXPANDING_HEIGHT);
    }

    void stepExpansionHeight () {

      erase();


      if (expansionDeltaHeight > 0) {
        style->height += expansionHeightStep;

        if (style->height - style->initHeight > expansionDeltaHeight) {
          style->height = style->initHeight + expansionDeltaHeight;

          setState(DONE_RENDER);
        }
      }

      else {
        style->height -= expansionHeightStep;
        
        if (style->height - style->initHeight < expansionDeltaHeight) {
          style->height = style->initHeight + expansionDeltaHeight;

          setState(DONE_RENDER);
        }
      }

      draw();
    }

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
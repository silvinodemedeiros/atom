#ifndef BLOCK_H
#define BLOCK_H

class Block {

  protected:
    Adafruit_TFTLCD *display;

    // states
    enum BlockState {
      INITIAL,
      IS_DISABLING,
      DISABLED,
      IS_TRANSITIONING_Y,
      IS_TRANSITIONING_X,
      IS_EXPANDING_HEIGHT,
      IS_SHRINKING_HEIGHT,
      SELECTED
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
    int translationStep = 20;
    int expansionHeightStep = 30;

  public:
    Block(Adafruit_TFTLCD *tft, int ux, int uy, int w, int h) {
      display = tft;
      x = ux;
      y = uy;
      width = w;
      height = h;
      initX = x;
      initY = y;
      initWidth = width;
      initHeight = height;
    }

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
    
    void setWidth (int w) {
      width = w;
    }

    void setHeight (int h) {
      height = h;
    }

    void setBorderColor (int bc) {
      borderColor = bc;
    }

    void manageInput () {
      if (selInput == HIGH) {
        goToState(GAME_STATE);
      }
    }

    void manageState() {
      switch(state) {
        case IS_TRANSITIONING_Y:
          stepTransitionY();
        case SELECTED:
          manageInput();
      }
    }

    void setState(BlockState nextState) {
      state = nextState;
    }

    boolean isAnimating() {
      if (state == IS_TRANSITIONING_Y) {
        return true;
      }

      return false;
    }

    // BASIC ANIMATIONS
    void startTranslateY(int toY, int dir) {
      translationToY = toY;
      translationDirY = dir;

      setState(IS_TRANSITIONING_Y);
      stepTransitionY();
    }

    void stepTransitionY() {

      erase();

      // downward translation
      if (translationDirY == 1) {

        y += translationStep;

        // is animation done?
        if (y > translationToY) {
          y = translationToY;
          translationToY = -1;
          translationDirY = 0;
          setState(SELECTED);
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
          setState(SELECTED);
        }
      }

      draw();
    }

    boolean translateY(int toY, int dir) {

      if (dir == 1) {

        y += translationStep;

        // is animation done?
        if (y > toY) {
          y = toY;
          return true;
        }

      } else {
        y -= translationStep;

        if (y < toY) {
          y = toY;
          return true;
        }
      }
      
      return false;
    }

    boolean expandHeight (int toHeight) {

      height += expansionHeightStep;
    
      if (height > toHeight) {
        height = toHeight;
        return true;
      }
      
      return false;
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
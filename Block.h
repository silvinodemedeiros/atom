#ifndef BLOCK_H
#define BLOCK_H

class Block {

  protected:
    Adafruit_TFTLCD *display;

    // states
    enum BlockState {
      INITIAL,
      WILL_RERENDER,
      IS_TRANSITIONING_Y,
      IS_TRANSITIONING_X,
      IS_EXPANDING_HEIGHT,
      IS_SHRINKING_HEIGHT,
      DONE_ANIMATION,
      WILL_RENDER_CHILDREN,
      IS_RENDERING_CHILDREN
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
    BlockState doneState = INITIAL;

    // tree attributes
    Block *children;
    Block *parentNode;
    boolean willRenderChildren = false;
    boolean isChildrenRendered = false;

    // tmp container values
    int y0 = 58;
    int x0 = 6;

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

    void manageInput() {
      if (selInput == HIGH) {
        goToState(GAME_STATE);
      }
    }

    void manageState() {
      switch(state) {
        case WILL_RENDER_CHILDREN:
          startChildrenRender();
          break;
        case IS_RENDERING_CHILDREN:
          stepChildrenRender();
          break;
        case IS_TRANSITIONING_Y:
          stepTransitionY();
          break;
        case DONE_ANIMATION:
          setState(WILL_RERENDER);
          break;
        case WILL_RERENDER:
          draw();
          break;
      }
    }

    void setState(BlockState nextState) {
      state = nextState;
    }

    boolean isRendering() {
      if (state == IS_TRANSITIONING_Y ||
          state == WILL_RENDER_CHILDREN ||
          state == IS_RENDERING_CHILDREN) {
        return true;
      }

      return false;
    }

    void startChildrenRender() {
      setState(IS_RENDERING_CHILDREN);
    }

    void stepChildrenRender() {
      children->setX(x0);
      children->setY(y0 + height + 10);
      children->draw();

      setState(doneState);
    }

    // BASIC ANIMATIONS
    void startTranslateY(int toY, int dir) {
      translationToY = toY;
      translationDirY = dir;

      setState(IS_TRANSITIONING_Y);
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
          
          if (willRenderChildren) {
            setState(WILL_RENDER_CHILDREN);
          } else {
            setState(DONE_ANIMATION);
          }
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
          
          if (willRenderChildren) {
            setState(WILL_RENDER_CHILDREN);
          } else {
            setState(DONE_ANIMATION);
          }
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
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
      IS_EXPANDING_WIDTH,
      IS_SHRINKING_HEIGHT,
      DONE_RENDER,
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
    int expansionToHeight = -1;

    // tree attributes
    Block *children;
    Block *parentNode;
    boolean hasChildren = false;

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

    void setState(BlockState nextState) {
      state = nextState;
    }

    void manageInput() {
      if (selInput == HIGH) {
        goToState(GAME_STATE);
      }
    }

    boolean isRendering() {
      return state != INITIAL;
    }

    void manageState() {

      manageChildrenState();
      
      switch(state) {
        case WILL_RENDER_CHILDREN:
          startChildrenRender();
          break;
        case IS_RENDERING_CHILDREN:
          checkChildrenRender();
          break;
        case IS_TRANSITIONING_Y:
          stepTranslationY();
          break;
        case IS_EXPANDING_HEIGHT:
          stepExpansionHeight();
          break;
        case DONE_RENDER:
          setState(WILL_RERENDER);
          break;
        case WILL_RERENDER:
          draw();
          setState(INITIAL);
          break;
      }
    }

    void manageChildrenState() {
      if (hasChildren) {
        children->manageState();
      }
    }

    void appendChild(Block *child) {
      children = child;
      hasChildren = true;
    }

    void removeChild() {
      hasChildren = false;
      children->erase();
      delete children;
    }

    void startChildrenRender() {
      setState(IS_RENDERING_CHILDREN);
      children->startExpansionHeight(150);
    }

    void checkChildrenRender() {
      if (hasChildren && !children->isRendering())
        setState(DONE_RENDER);
    }

    // BASIC ANIMATIONS
    void startTranslationY(int toY, int dir) {
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
          
          if (hasChildren) {
            setState(WILL_RENDER_CHILDREN);
          } else {
            setState(DONE_RENDER);
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
          
          if (hasChildren) {
            setState(WILL_RENDER_CHILDREN);
          } else {
            setState(DONE_RENDER);
          }
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

        if (hasChildren) {
          setState(WILL_RENDER_CHILDREN);
        } else {
          setState(DONE_RENDER);
        }
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
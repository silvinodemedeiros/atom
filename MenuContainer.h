
class MenuContainer {
  private:
    int width = 228;
    int initWidth = 228;
    int height = 46;
    int initHeight = 46;
    int x = 0;
    int initX = 0;
    int y = 0;
    int initY = 0;
    int toX = -1;
    int nextY = -1;

    boolean active = false;
    boolean isTranslatingY = false;
    int borderWidth = 2;
    MenuContainer *previous;
    MenuContainer *next;
    Adafruit_TFTLCD *display;
    
    int translationStep = 20;
    int expansionHeightStep = 30;
    int defaultColor = DEFAULTGREEN;
    int activeColor = WHITE;

  public: 
        
    MenuContainer(Adafruit_TFTLCD *tft, int ux, int uy) {
      display = tft;
      x = ux;
      y = uy;
      initX = x;
      initY = y;
    }

    void draw() {
      display->drawRect(x, y, width, height, defaultColor);
    }

    void erase() {
      display->drawRect(x, y, width, height, MAINBG);
    }

    void focus() {
      display->drawRect(x, y, width, height, activeColor);
    }

    void unfocus() {
      draw();
    }

    boolean translateY(int toY, int dir) {

      // is animation done?
      if (dir == 1) {

        y += translationStep;

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

    MenuContainer* getPrevious() {
      return previous;
    }

    MenuContainer* getNext() {
      return next;
    }
    
    void setPrevious(MenuContainer *container) {
      previous = container;
    }

    void setNext(MenuContainer *container) {
      next = container;
    }

    void setTranslationY() {
      isTranslatingY = true;
    }
};
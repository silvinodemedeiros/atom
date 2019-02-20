
class MenuContainer {
  private:
    int width = 228;
    int height = 46;
    int x = 0;
    int y = 0;
    boolean active = false;
    int borderWidth = 2;
    MenuContainer *previous;
    MenuContainer *next;
    Adafruit_TFTLCD *display;

    int defaultColor = DEFAULTGREEN;
    int activeColor = WHITE;

  public: 
        
    MenuContainer(Adafruit_TFTLCD *tft, int ux, int uy) {
      display = tft;
      x = ux;
      y = uy;
    }

    void draw() {
      for (int i = 0; i < borderWidth; i++)  {
        display->drawRoundRect(x + i, y + i, width, height, 3, defaultColor);
      }
    }

    void focus() {
      for (int i = 0; i < borderWidth; i++)  {
        display->drawRoundRect(x + i, y + i, width, height, 3, activeColor);
      }
    }

    void unfocus() {
      draw();
    }

    int getHeight() {
      return height;
    }

    int getWidth() {
      return width;
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
};
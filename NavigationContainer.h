#ifndef NAVCONTAINER_H
#define NAVCONTAINER_H

#include "atomik/Container.h"

class NavigationContainer : public Container {

  public:
    NavigationContainer(int ux, int uy, int w, int h) : Container(ux, uy, w, h) {}
    NavigationContainer() : Container() {}

    bool focused = false;
    NavigationContainer *next;
    NavigationContainer *previous;

    void setNext(NavigationContainer *nextContainer) {
      next = nextContainer;
    }

    void setPrevious(NavigationContainer *previousContainer) {
      previous = previousContainer;
    }

    void focus() {
      this->style->borderColor = WHITE;
      focused = true;
    }

    void unfocus() {
      this->style->borderColor = DEFAULTGREEN;
      focused = false;
    }

    NavigationContainer* focusNext() {
      this->unfocus();
      next->focus();
      return next;
    }

    NavigationContainer* focusPrevious() {
      this->unfocus();
      previous->focus();
      return previous;
    }

};

#endif
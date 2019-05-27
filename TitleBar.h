#ifndef TITLEBAR_H
#define TITLEBAR_H

#include "atomik/Container.h"

class TitleBar : public Container {

  public:

    TitleBar (String textValue) : Container() {
      text = textValue;
      style->fill = 1;
      style->border = false;
    }
  
};

#endif
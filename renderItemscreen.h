#ifndef ITEMSCREEN_H
#define ITEMSCREEN_H

#include "atomik/Screen.h"
#include "atomik/Container.h"
#include "atomik/StyleTypes.h"
#include "atomik/TextBlock.h"

Screen *itemScreen;

void initItemScreen(Adafruit_TFTLCD *tft) {

  Container *itemRoot = new Container();
  itemRoot->style->display = COLUMN;
  itemRoot->style->visibility = false;

  itemScreen = new Screen(tft);
  itemScreen->appendChild(itemRoot);
  itemScreen->nextSystemState = HOME_STATE;
  
  // TextBlock *textBlock = new TextBlock("35");
  // textBlock->style->x = (WIDTH / 2) - 10;
  // textBlock->style->y = (HEIGHT / 2) - 10;
  // textBlock->style->textSize = 3;
  // itemRoot->appendChild(textBlock);

  itemRoot->appendChild(new Container());
  itemRoot->appendChild(new Container());
  itemRoot->appendChild(new Container());

}

#endif
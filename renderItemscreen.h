#ifndef ITEMSCREEN_H
#define ITEMSCREEN_H

#include "atomik/Screen.h"
#include "atomik/Container.h"
#include "atomik/StyleTypes.h"
#include "atomik/TextBlock.h"

void initItemScreen(Screen *itemScreen) {

  itemScreen->systemState = ITEM_STATE;
  itemScreen->name = "ITEM";

  Container *itemRoot = new Container();
  itemRoot->style->display = COLUMN;
  itemRoot->style->visibility = false;
  itemScreen->appendChild(itemRoot);

  Container *child = new Container();
  itemScreen->currentOption = child;
  child->nextSystemState = HOME_STATE;
  child->focus();

  itemRoot->appendChild(child);
  itemRoot->appendChild(new Container());
  itemRoot->appendChild(new Container());

}

#endif
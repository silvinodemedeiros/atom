#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include "atomik/Screen.h"
#include "atomik/Container.h"
#include "atomik/StyleTypes.h"

void initHomeScreen(Screen *homeScreen) {

  String title = "Home Screen";
  int itemAmt = 3;
  String itemTitles[itemAmt] = {"First Option", "Second Option", "Third Option"};
  int nextStates[itemAmt] = {
    FIRST_STATE, 
    SECOND_STATE, 
    THIRD_STATE
  };

  homeScreen->hasTransitionOut = true;
  homeScreen->systemState = HOME_STATE;

  Container *root = new Container();
  root->style->display = COLUMN;
  root->style->visibility = false;
  homeScreen->appendChild(root);

  Container *titleBar = new Container();
  titleBar->style->fill = 1;
  titleBar->style->border = false;
  titleBar->text = title;
  root->appendChild(titleBar);

  Container *itemContainer = new Container();
  itemContainer->style->fill = 5;
  itemContainer->style->display = COLUMN;
  itemContainer->style->visibility = false;
  root->appendChild(itemContainer);

  for (int i = 0; i < itemAmt; i++) {
    Container *item = new Container();
    item->text = itemTitles[i];
    item->nextSystemState = nextStates[i];
    itemContainer->appendChild(item);

    if (i == 0) {
      homeScreen->currentOption = item;
      item->focus();
    }
  }

  itemContainer->establishNavigation();

}

#endif
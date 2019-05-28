#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include "atomik/Screen.h"
#include "atomik/Container.h"
#include "atomik/StyleTypes.h"

void slideOutLeft (Screen *screen) {
  screen->wrapper->translateX(-WIDTH);
}

void slideInLeft (Screen *screen) {
  screen->wrapper->translateX(WIDTH);
}

void initHomeScreen(Screen *homeScreen) {

  String title = "Home Screen";
  int itemAmt = 3;
  String itemTitles[itemAmt] = {"First Option", "Second Option", "Third Option"};
  int nextStates[itemAmt] = {
    FIRST_STATE, 
    SECOND_STATE, 
    THIRD_STATE
  };

  homeScreen->systemState = HOME_STATE;
  homeScreen->transitionOut = slideOutLeft;
  homeScreen->transitionIn = slideInLeft;
  homeScreen->wrapper->moveX(-WIDTH);

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
  itemContainer->style->fill = 6;
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
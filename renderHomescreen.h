#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include "atomik/Screen.h"
#include "atomik/Container.h"
#include "atomik/StyleTypes.h"

void expose(Container *item) {
  Container *parent = item->link->parent;
  bool hasFound = false;

  for (int i = 0; i < parent->chAmt; i++) {
    Container *child = parent->chSet[i];

    if (hasFound) {
      child->translateX(WIDTH);
    } else {
      child->translateX(-WIDTH);
    }
    
    if (child == item->link) {
      child->translateY(parent->style->y - child->style->y);
      hasFound = true;
    }
  }
}

void comeback(Container *item) {
  Container *parent = item->link->parent;
  bool hasFound = false;

  for (int i = 0; i < parent->chAmt; i++) {
    Container *child = parent->chSet[i];

    if (hasFound) {
      child->translateX(child->style->initX - child->style->x);
    } else {
      child->translateX(child->style->initX - child->style->x);
    }
    
    if (child == item->link) {
      child->translateY(child->style->initY - child->style->y);
      hasFound = true;
    }
  }
}

// creates screen
void initHomeScreen(Screen *homeScreen) {

  int tabAmt = 3;
  int contentAmt = 3;
  String tabTitles[tabAmt] = {"A", "B", "C" };
  String contentTitles[contentAmt] = { "Start Game", "Controls", "Options" };

  homeScreen->systemState = HOME_STATE;
  homeScreen->name = "HOME";

  Container *root = new Container();
  root->style->display = COLUMN;
  root->style->visibility = false;
  homeScreen->appendChild(root);

  Container *content = new Container();
  content->style->fill = 3;
  content->style->visibility = false;
  content->style->display = COLUMN;

  for (int i = 0; i < contentAmt; i++) {
    Container *contentItem = new Container();
    contentItem->text = contentTitles[i];
    content->appendChild(contentItem);
  }

  Container *toolbar = new Container();
  toolbar->style->fill = 1;
  toolbar->style->display = ROW;
  toolbar->style->visibility = false;

  for (int i = 0; i < tabAmt; i++) {
    Container *tab = new Container();
    tab->text = tabTitles[i];
    tab->link = content->chSet[i];
    tab->manageSelection = expose;
    tab->manageReturn = comeback;
    toolbar->appendChild(tab);

    if (i == 0) {
      homeScreen->currentOption = tab;
    }
  }
  toolbar->establishNavigation();
  root->appendChild(toolbar);
  root->appendChild(content);
}

#endif
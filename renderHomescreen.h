#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include "atomik/Screen.h"
#include "atomik/Container.h"
#include "atomik/StyleTypes.h"

void enlarge(Container *container) {
  Container *parent = container->parent;
  
  for (int i = 0; i < parent->chAmt; i++) {
    if (parent->chSet[i] != container) {
      parent->chSet[i]->erase();
      parent->chSet[i]->style->visibility = false;
    } else {
      container->erase();
      container->translateY(parent->style->initY - container->style->y);
    }
  }
}

void shrink(Container *container) {
  Container *parent = container->parent;
  
  for (int i = 0; i < parent->chAmt; i++) {
    if (parent->chSet[i] != container) {
      parent->chSet[i]->style->visibility = true;
    } else {
      container->erase();
      container->translateY(container->style->initY - container->style->y);
    }
  }
}

// creates screen
void initHomeScreen(Screen *homeScreen) {

  int amount = 5;
  String items[amount] = {
    "1. My Games",
    "2. Manage",
    "3. States",
    "4. Elements",
    "5. Options"
  };
  homeScreen->systemState = HOME_STATE;
  homeScreen->name = "HOME";

  Container *homeRoot = new Container();
  homeRoot->style->display = COLUMN;
  homeRoot->style->visibility = false;
  homeScreen->appendChild(homeRoot);

  for (int i = 0; i < amount; i++) {
    Container *child = new Container();
    homeRoot->appendChild(child);

    child->manageSelection = enlarge;
    child->manageReturn = shrink;
    child->text = items[i];
    
    if (i == 0) {
      homeScreen->currentOption = child;
      child->focus();
    }
  }

  for (int i = 0; i < homeRoot->chAmt; i++) {
    if (i > 0 && i < homeRoot->chAmt - 1) {
      homeRoot->chSet[i]->next = homeRoot->chSet[i+1];
      homeRoot->chSet[i]->previous = homeRoot->chSet[i-1];
    }

    else if (i == 0) {
      homeRoot->chSet[i]->next = homeRoot->chSet[i+1];
      homeRoot->chSet[i]->previous = homeRoot->chSet[homeRoot->chAmt - 1];
    }

    else if (i == homeRoot->chAmt - 1) {
      homeRoot->chSet[i]->next = homeRoot->chSet[0];
      homeRoot->chSet[i]->previous = homeRoot->chSet[i - 1];
    }
  }
}

#endif
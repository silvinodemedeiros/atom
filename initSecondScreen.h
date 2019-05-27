#ifndef SECONDSCREEN_H
#define SECONDSCREEN_H

#include "atomik/Screen.h"
#include "atomik/Container.h"
#include "atomik/StyleTypes.h"

void initSecondScreen(Screen *secondScreen) {

  String title = "Second Screen";

  secondScreen->systemState = SECOND_STATE;

  Container *root = new Container();
  root->style->display = COLUMN;
  root->style->visibility = false;
  secondScreen->appendChild(root);

  Container *titleBar = new Container();
  titleBar->style->fill = 1;
  titleBar->text = title;
  root->appendChild(titleBar);

  Container *content = new Container();
  content->style->fill = 5;
  content->style->display = COLUMN;
  content->text = "Content Here";
  root->appendChild(content);

}

#endif
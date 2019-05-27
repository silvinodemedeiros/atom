#ifndef THIRDSCREEN_H
#define THIRDSCREEN_H

#include "atomik/Screen.h"
#include "atomik/Container.h"
#include "atomik/StyleTypes.h"

void initThirdScreen(Screen *thirdScreen) {

  String title = "Third Screen";

  thirdScreen->systemState = THIRD_STATE;

  Container *root = new Container();
  root->style->display = COLUMN;
  root->style->visibility = false;
  thirdScreen->appendChild(root);

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
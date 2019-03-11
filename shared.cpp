#include "colors.h"
#include "states.h"

#ifndef SHARED_CPP
#define SHARED_CPP

int currentBg = WHITE;
bool hasLoaded = false;
bool inputLock = false;
int state = SYSTEM_INITIAL;
int rot = 2;
int transitionStep = 5;

void goToState(int nextState) {
  inputLock = true;
  hasLoaded = false;
  state = nextState;
}

#endif
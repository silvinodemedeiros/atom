#include "colors.h"
#include "states.h"

#ifndef SHARED_CPP
#define SHARED_CPP

int currentBg = WHITE;
bool hasLoaded = false;
bool inputLock = false;
int state = INITIAL;
int rot = 2;
int transitionStep = 5;

#endif
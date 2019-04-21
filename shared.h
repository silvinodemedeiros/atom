#ifndef SHARED_H
#define SHARED_H

extern int currentBg;      // current background
extern bool hasLoaded;     // stores screen loading status
extern bool inputLock;     // stores input lock status
extern int state;          // stores current machine state
extern int rot;            // screen rotation for portrait orientation rendering
extern int transitionStep; // step for animation purposes

void goToState(int nextStep);


#endif
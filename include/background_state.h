// background_state.h

#ifndef BACKGROUND_STATE_H
#define BACKGROUND_STATE_H

#include<String>
#include<raylib.h>

extern const Color green ;
extern const Color darkGreen ;



extern const int cellSize ;
extern const int cellCount ;

extern bool flagPause;

extern unsigned int minLimit;
extern unsigned int maxLimit;

extern unsigned int countBackground;


typedef enum {
    ANIMATION_UP,
    ANIMATION_DOWN
} BackgroundState;

const char * getString(const std::string title);

void drawBackground(BackgroundState& backgroundState);

std::string backgroundStateToString(BackgroundState state);

void reverseBackground(BackgroundState& backgroundState);


#endif // BACKGROUND_STATE_H

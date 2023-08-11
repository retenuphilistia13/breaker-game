#include"background_state.h"

void reverseBackground(BackgroundState& backgroundState){
    backgroundState = (backgroundState==ANIMATION_UP) ? backgroundState=ANIMATION_DOWN : ANIMATION_UP;
}


const char * getString(const std::string title) {
    const char * titleCStr = title.c_str();
    return titleCStr;
}

void drawBackground(BackgroundState& backgroundState) {
    // Check if the animation is up or down based on countBackground value

    if(!flagPause)
    if (countBackground >= maxLimit) {
       // reverseBackground(backgroundState);
        //countBackground--;
        countBackground=minLimit;
    } else if (countBackground < minLimit) {
        //reverseBackground(backgroundState);
       // countBackground++;
        countBackground=maxLimit;
    }
    
    // Drawing
    for (int row = 0; row < cellCount; ++row) {
        for (int col = 0; col < cellCount; ++col) {
            int x = col * cellSize;
            int y = row * cellSize;
            if ((row + col) % countBackground == 0) {
                DrawRectangle(x, y, cellSize, cellSize, darkGreen);
            } else {
                DrawRectangle(x, y, cellSize, cellSize, BLUE);
            }
        }
    }
   //  std::cout << "backgroundState: " << backgroundStateToString(backgroundState) << std::endl;

      //  std::cout<<"countBackground: "<<countBackground<<std::endl;

}

// Function to convert the enum value to a string representation
std::string backgroundStateToString(BackgroundState state) {
    switch (state) {
        case BackgroundState::ANIMATION_UP:
            return "ANIMATION_UP";
        case BackgroundState::ANIMATION_DOWN:
            return "ANIMATION_DOWN";
        default:
            return "UNKNOWN";
    }
}
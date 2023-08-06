#include <iostream>

#include<String>

////game headers/////
#include <raylib.h>

#include"Player.h" 

#include"Ball.h"

#include"background_state.h"

#include"Game.h"

#include"Brick.h"

 // Add this line to include the thread library
using namespace std;

const Color green = {
    173,
    204,
    96,
    255
};
const Color darkGreen = {
    43,
    51,
    24,
    255
};



const int cellSize = 20;
const int cellCount = 40;

const std::string Title = "Shape Collider";


bool flagPause = false;

double lastUpdateTime = 0;
unsigned int countBackground=3;


bool EventTriggered(double interval);

const char * getString(const std::string title);

void drawBackground(BackgroundState& backgroundState);

std::string backgroundStateToString(BackgroundState state);

void reverseBackground(BackgroundState& backgroundState);



void reverseBackground(BackgroundState& backgroundState){
    backgroundState = (backgroundState==ANIMATION_UP) ? backgroundState=ANIMATION_DOWN : ANIMATION_UP;
}

int main() {
    const char * titleCStr = getString(Title);

    // Initialize the window and other settings
 BackgroundState backgroundState=BackgroundState::ANIMATION_UP;

    InitWindow((cellSize * cellCount), (cellSize * cellCount), "Shape Collider");

    SetWindowPosition(250, 100);

    SetTargetFPS(60);

    Game game;


    size_t ballNumber = 200;

    game.generateMultipleBall(ballNumber);

    int textWidth = MeasureText(titleCStr, 40);
    int x = (cellSize * cellCount) / 2 - (textWidth / 2);

while (!WindowShouldClose()) {
   
    if (EventTriggered(1.0)&&(!flagPause)) { // Check for event every 1.0 second
        if (backgroundState == BackgroundState::ANIMATION_UP) {
            countBackground++;
        } else if (backgroundState == BackgroundState::ANIMATION_DOWN) {
            countBackground -= 1;
        }
    }

    BeginDrawing();

    ////record and observation variable///
    game.ballsDrawn = 0;
    game.ballsUpdates = 0;

    //////pause game logic//////
    int keyPressed = GetKeyPressed();

    if (keyPressed == KEY_P) {
        flagPause = !flagPause;
    }

drawBackground(backgroundState);

    if (!flagPause) {
        game.update();
    }
   else if (flagPause) {
        DrawText("Paused", x, 80, 40, WHITE);
    } 

    /////player input////////
    game.player.userInput();

    game.draw();


    ///////draw title//////
    if (!flagPause) {
        DrawText(titleCStr, x, 80, 40, WHITE);
    }
    // Draw the integer as text at the specified position (100, 100)
    std::string drawnBallsString = TextFormat("ball drawn: %i BallsQuantity: %i ballsUpdates:%i", game.ballsDrawn, game.getBallsQuantity(), game.ballsUpdates);
    DrawText(drawnBallsString.c_str(), x - 200, 100, 30, RED);

    DrawFPS(10, 10);
    EndDrawing();

}

    CloseWindow();
    return 0;
}

const char * getString(const std::string title) {
    const char * titleCStr = title.c_str();
    return titleCStr;
}

void drawBackground(BackgroundState& backgroundState) {
    // Check if the animation is up or down based on countBackground value

    if(!flagPause)
    if (countBackground >= 30) {
        reverseBackground(backgroundState);
        countBackground--;
    } else if (countBackground < 3) {
        reverseBackground(backgroundState);
        countBackground++;
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
     std::cout << "backgroundState: " << backgroundStateToString(backgroundState) << std::endl;

        std::cout<<"countBackground: "<<countBackground<<std::endl;

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
 
bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}
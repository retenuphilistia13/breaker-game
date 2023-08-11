#include <iostream>

#include<String>

////game headers/////
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

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

bool EventTriggered(double interval);

unsigned int minLimit = 3;
unsigned int maxLimit = 13;

unsigned int countBackground = maxLimit;

int main() {

   const char * titleCStr = getString(Title);

   // Initialize the window and other settings
   BackgroundState backgroundState = BackgroundState::ANIMATION_UP;

   InitWindow((cellSize * cellCount), (cellSize * cellCount), "Shape Collider");

   SetWindowPosition(250, 100);
   // layout_name: controls initialization
   //----------------------------------------------------------------------------------

   //----------------------------------------------------------------------------------
   SetTargetFPS(60);

   Game * game = new Game();

   bool running = false;

   size_t ballNumber = 1;

   int textWidth = MeasureText(titleCStr, 40);
   int x = (cellSize * cellCount) / 2 - (textWidth / 2);

   ///initalize bricks///
   game -> createMultipleBrick();
   ///

   // Create a rectangle for the button
   Rectangle buttonRec = {
      (float) GetScreenWidth() / 2 - 100,
      (float) GetScreenHeight() / 2 - 40,
      200,
      80
   };

   ///game loop////
   while (!WindowShouldClose()) {

      if (EventTriggered(1.0) && (!flagPause)) { // Check for event every 1.0 second
         if (backgroundState == BackgroundState::ANIMATION_UP) {
            countBackground++;
         } else if (backgroundState == BackgroundState::ANIMATION_DOWN) {
            countBackground -= 1;
         }
      }

      BeginDrawing();
      // Update
      if (GuiButton(buttonRec, "Click Me!")) {

         running = true; // You can add your own code here to respond to the button click
      }

      if (IsKeyDown(KEY_Q)) {
         running = false;
      } else if (IsKeyDown(KEY_R)) {
         // Delete the previous instance and create a new one
         delete game;
         game = new Game();

         running = false;
         //game->generateMultipleBall(ballNumber);
         game -> createMultipleBrick();

      }
      if (GuiButton(buttonRec, "restart")) { // Button was clicked
         game -> generateMultipleBall(ballNumber);
      }

      ////record and observation variable///
      game -> ballsDrawn = 0;
      game -> ballsUpdates = 0;

      //////pause game logic//////
      int keyPressed = GetKeyPressed();

      if (keyPressed == KEY_P) { //pause if p entered
         flagPause = !flagPause;
      }

      drawBackground(backgroundState);

      if (!flagPause && running == true) {
         game -> update();
      } else if (flagPause) {
         DrawText("Paused", x, 80, 40, WHITE);
      }

      /////player input////////
      game -> player.userInput();

      game -> draw();

      // Draw the button
      if (!running) {
         DrawRectangleRec(buttonRec, darkGreen);
         DrawText("Start Game ", buttonRec.x + buttonRec.width / 2 - MeasureText("Start Game", 20) / 2,
            buttonRec.y + buttonRec.height / 2 - 20 / 2, 20, LIGHTGRAY);
      }
      ///////draw title//////
      //if (!flagPause) 
      DrawText(titleCStr, x, 80, 40, WHITE);

      // Draw the integer as text at the specified position (100, 100)
      std::string drawnBallsString = TextFormat("ball drawn: %i BallsQuantity: %i ballsUpdates:%i", game -> ballsDrawn, game -> getBallsQuantity(), game -> ballsUpdates);
      DrawText(drawnBallsString.c_str(), x - 200, 100, 30, RED);

      DrawFPS(10, 10);
      EndDrawing();

   }

   CloseWindow();
   return 0;
}

bool EventTriggered(double interval) {
   double currentTime = GetTime();
   if (currentTime - lastUpdateTime >= interval) {
      lastUpdateTime = currentTime;
      return true;
   }
   return false;
}
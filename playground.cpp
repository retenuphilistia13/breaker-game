
#include <iostream>
#include <raylib.h>
#include <raymath.h>

#include <memory>

#include<vector>
#include <algorithm> 
#include<String>

#include"Player.h"
#include"Ball.h"


using namespace std;


const Color green = {173, 204, 96, 255};
const Color darkGreen = {43, 51, 24, 255};

const int cellSize = 20;
const int cellCount = 40;

const std::string Title="Shape Collider";


bool flagPause=false;
double lastUpdateTime = 0;

const char* getString(const std::string title );
void drawBackground();



 int CountPosition=0;
 int CountSpeed=0;


class Game{
public:

    int ballsDrawn=0;
    int ballsUpdates=0;

    Player player;
 
    std::vector<Ball> balls;


    void detectCollision() {
        for (auto& ball : balls) {
            if (CheckCollisionCircleRec(ball.position, static_cast<float>(ball.ballRadius), { player.position.x, player.position.y, player.dimension.x, player.dimension.y })) {
                // Handle collision between the ball and the player 

                ball.ballSpeed.x *= -1.0f;
                ball.ballSpeed.y *= -1.0f;
            }
        }
    }

    void createInstance(int countPosition, int countSpeed) {
        balls.emplace_back(countPosition, countSpeed);
    }


void update(){
    player.update();
detectCollision();
  for (auto& ball : balls){ball.update();ballsUpdates++;}
 // Remove balls that are no longer needed
        balls.erase(
            std::remove_if(balls.begin(), balls.end(), [this](const Ball& ball) {

                return ballShouldBeDeleted(ball);
            }),
            balls.end()
        );
}


void draw(){
    player.draw();
  for (auto& ball : balls){ball.draw();
    ballsDrawn++;
      }
}

    int getBallsQuantity(){
       return balls.size();
    }

    private:

     // Helper function to determine if a ball should be deleted based on certain conditions.
    bool ballShouldBeDeleted(const Ball& ball) {
// Check if the ball is off the screen (reached the bottom)
        int twentyPercent = (cellSize >> 2) + (cellSize >> 4);//twenty percent of cellsize 0.2*cellSize
        if ( ball.position.y >= GetScreenHeight()-ball.ballRadius-twentyPercent) {
            return true;
        }

        return false;
    }

};


int main()
{

    // Initialize the window and other settings

    cout << "Starting the game..." << endl;
    InitWindow( (cellSize * cellCount), (cellSize * cellCount), "Shape Collider");


    SetWindowPosition(250, 100);  

    SetTargetFPS(30);

Game game;

size_t ballNumber=10;
for (size_t i=0; i < ballNumber; ++i){//crete ball instances
    game.createInstance(CountPosition,CountSpeed);
        CountSpeed+=0;
    CountPosition+=cellSize/(ballNumber*0.1);
}


 // Calculate the number of cells to draw in each color
    int cellsInDarkGreen = cellCount * cellCount / 2;
    int cellsInLightBlue = cellCount * cellCount - cellsInDarkGreen;


 const char* titleCStr = getString(Title);

int textWidth = MeasureText(titleCStr, 40);
int x = (cellSize * cellCount) / 2 - (textWidth / 2);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();


drawBackground();

game.ballsDrawn=0;
game.ballsUpdates=0;
        int keyPressed=GetKeyPressed();

            if (keyPressed==KEY_P)
            {
                flagPause=!(flagPause);
            //       if (game.balls.size() > 1)
            // {
            //     game.balls.erase(game.balls.begin() + 1);
            // }
                                
            }

if(flagPause){
    DrawText("Paused", x, 80, 40, WHITE);
}

else{
    game.update();
}



      
      
        

///////draw title//////
      if(!flagPause)
       DrawText(titleCStr, x, 80, 40, WHITE);

/////player input////////
   game.player.userInput();   

    game.draw();
         // Draw the integer as text at the specified position (100, 100)
std::string drawnBallsString = TextFormat("ball drawn: %i BallsQuantity: %i ballsUpdates:%i", game.ballsDrawn, game.getBallsQuantity(),game.ballsUpdates);
        DrawText(drawnBallsString.c_str(), x-400, 100, 30, RED);


 DrawFPS(10, 10);


        EndDrawing();


    }
    CloseWindow();
    return 0;
}
void drawTitle(){



}
const char* getString(const std::string title ){
     const char* titleCStr = title.c_str();
     return titleCStr;
}
void drawBackground(){

  // Drawing
        for (int row = 0; row < cellCount; ++row)
        {
            for (int col = 0; col < cellCount; ++col)
            {
                int x = col * cellSize;
                int y = row * cellSize;
                if ((row + col) % 2 == 0)
                {
                    DrawRectangle(x, y, cellSize, cellSize, darkGreen);
                }
                else
                {
                    DrawRectangle(x, y, cellSize, cellSize, BLUE);
                }
            }
        }


}
// bool EventTriggered(double interval)
// {
//     double currentTime = GetTime();
//     if (currentTime - lastUpdateTime >= interval)
//     {
//         lastUpdateTime = currentTime;
//         return true;
//     }
//     return false;
// }


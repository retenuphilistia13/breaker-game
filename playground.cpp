
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
const int cellCount = 45;

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
    vector<unique_ptr<Ball>> balls;

 void detectCollision() {
        for (auto& ball : balls) {
            if (CheckCollisionCircleRec(ball->position, static_cast<float>(ball->ballRadius), { player.position.x, player.position.y, player.dimension.x, player.dimension.y })) {
                // Handle collision between the ball and the player (e.g., reset the ball position, update score, etc.)
                // For now, let's just make the ball bounce off the player's position.
                ball->ballSpeed.x *= -1.0f;
                ball->ballSpeed.y *= -1.0f;
            }
        }
    }
void createInstance(int countPosition,int countSpeed){

    balls.push_back(make_unique<Ball>(countPosition,countSpeed));

 
}

void update(){
    player.update();
detectCollision();
  for (auto& ball : balls){ball->update();ballsUpdates++;}

}


void draw(){
    player.draw();
  for (auto& ball : balls){ball->draw();
    ballsDrawn++;
      }
}

    int getBallsQuantity(){
       return balls.size();
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
size_t ballNumber=50;
for (size_t i=0; i < ballNumber; ++i){//crete ball instances
    game.createInstance(CountPosition,CountSpeed);
        CountSpeed+=0;
    CountPosition+=cellSize;
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
game.ballsDrawn=0;
game.ballsUpdates=0;
        int keyPressed=GetKeyPressed();

            if (keyPressed==KEY_P)
            {
                flagPause=!(flagPause);
                  if (game.balls.size() > 1)
            {
                game.balls.erase(game.balls.begin() + 1);
            }
                                
            }



game.update();

        if(flagPause){
DrawText("game Paused",  55, 20, 40, darkGreen);
        }

      
      drawBackground();
        


            
            // Draw the text in the middle of the screen
            DrawText(titleCStr, x, 80, 40, WHITE);

//std::string integerAsString = std::to_string(game.getBallsQuantity());



           if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) )
{
game.player.PlayerSpeed.x-=1.0f;
}

if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)))
{
 game.player.PlayerSpeed.x+=1.0f;
}        

    game.draw();
std::string drawnBallsString = TextFormat("ball drawn: %i BallsQuantity: %i ballsUpdates:%i", game.ballsDrawn, game.getBallsQuantity(),game.ballsUpdates);


         // Draw the integer as text at the specified position (100, 100)
        DrawText(drawnBallsString.c_str(), x-400, 100, 30, RED);
// DrawFPS(10, 10);


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


#include <iostream>

#include <raylib.h>

#include<vector>

#include <algorithm>

#include<String>

#include <iomanip>

#include"Player.h"

#include"Ball.h"

#include"background_state.h"

#include"chrono"

#include <thread> // Add this line to include the thread library
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
class Game;

bool flagPause = false;

double lastUpdateTime = 0;
unsigned int countBackground=3;



bool EventTriggered(double interval);
const char * getString(const std::string title);
void drawBackground(BackgroundState& backgroundState);

int CountPosition = 0;
int CountSpeed = 0;


std::string backgroundStateToString(BackgroundState state);

class Game {
    public:

        int ballsDrawn = 0;
    int ballsUpdates = 0;

    Player player;

    std::vector < Ball > balls;

    void playerBallCollision(Ball & ballToCheck) {
        if (CheckCollisionCircleRec(ballToCheck.position, static_cast < float > (ballToCheck.radius), {
                player.position.x,
                player.position.y,
                player.dimension.x,
                player.dimension.y
            })) {
            // Handle collision between the ball and the player
            float relativePos = ballToCheck.position.x - player.position.x;
            float playerCenterX = player.position.x + player.dimension.x / 2;

            // Boost the ball's speed after hitting the player
            const float speedBoost = 5.0f;
            if (relativePos < 0) {
                // Ball is on the left side of the player
                ballToCheck.speed.x -= speedBoost;
            } else {
                // Ball is on the right side of the player
                ballToCheck.speed.x += speedBoost;
            }

            // Increase the ball's speed by a constant factor after hitting the player
            const float speedBoostFactor = 1.2f;
            ballToCheck.speed.x *= speedBoostFactor;
            ballToCheck.speed.y *= speedBoostFactor;
        }
    }

    void createInstance(int countPosition, int countSpeed) {
        balls.emplace_back(countPosition, countSpeed);
    }

    void ballSpeedRegulator(Ball & ball) {
        if (-ball.speed.x * 2 < ball.speed.y) {
            ball.speed.x += ball.speed.y / 3;
        } else if (-ball.speed.y * 2 < ball.speed.x) {

            ball.speed.y += ball.speed.x / 3;
        }

    }
    // Method to calculate and print the average speed of balls on the screen
    void printAverageSpeeds() {
        // Calculate the average speed in the x direction
        float avgSpeedX = 0.0f;
        float avgSpeedY = 0.0f;

        for (const auto & ball: balls) {
            avgSpeedX += ball.speed.x;
            avgSpeedY += ball.speed.y;
        }

        // Calculate the average speed in the y direction
        if (!balls.empty()) {
            avgSpeedX /= balls.size();
            avgSpeedY /= balls.size();
        }

        // Print the average speeds on the middle of the screen
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();

        // Convert average speeds to strings
        std::ostringstream avgSpeedXStr, avgSpeedYStr;
        avgSpeedXStr << std::fixed << std::setprecision(3) << avgSpeedX;
        avgSpeedYStr << std::fixed << std::setprecision(3) << avgSpeedY;

        // Draw the text on the screen
        int textPosX = screenWidth / 2 - MeasureText("Average Speed (X): 000.000", 20) / 2;
        int textPosY = screenHeight / 2 - 40;
        DrawText(("Average Speed (X): " + avgSpeedXStr.str()).c_str(), textPosX, textPosY, 20, RED);

        textPosY += 40;
        DrawText(("Average Speed (Y): " + avgSpeedYStr.str()).c_str(), textPosX, textPosY, 20, RED);

    }

    void update() {

        ////update ball and check collotion///
        for (auto & ball: balls) {
            ball.update(player.getRectangle());

            printAverageSpeeds(); //average ball speed

            ballsUpdates++;
        }
        player.update();
        // Remove balls that are no longer needed
        balls.erase(
            std::remove_if(balls.begin(), balls.end(), [this](const Ball & ball) {

                return ballShouldBeDeleted(ball);
            }),
            balls.end()
        );
    }

    void draw() {

        for (auto & ball: balls) {
            ball.draw();
            ballsDrawn++;
        }
        player.draw();
    }

    int getBallsQuantity() {
        return balls.size();
    }
    private:

        // Helper function to determine if a ball should be deleted based on certain conditions.
        bool ballShouldBeDeleted(const Ball & ball) {
            // Check if the ball is off the screen (reached the bottom) for deletion
            if (ball.isOutOfBound()) return true;
            if (ball.state == Ball::State::DEAD) return true;

            return false;
        }

};

void generateMultipleBall(size_t ballNumber, Game & game) {

    for (size_t i = 0; i < ballNumber; ++i) { //crete ball instances
        CountSpeed = 200;
        game.createInstance(CountPosition, CountSpeed);

        CountPosition += cellSize / (ballNumber * 0.1);
    }

}
void reverseBackground(BackgroundState& backgroundState);

void reverseBackground(BackgroundState& backgroundState){
    //backgroundState = (backgroundState==ANIMATION_UP) ? backgroundState=ANIMATION_DOWN : ANIMATION_UP;
 if(backgroundState==BackgroundState::ANIMATION_DOWN)backgroundState=ANIMATION_UP;
 else{
   backgroundState=ANIMATION_DOWN;
 }

}
int main() {
    const char * titleCStr = getString(Title);

    // Initialize the window and other settings
 BackgroundState backgroundState=BackgroundState::ANIMATION_UP;


   cout << "Starting the game..." << endl;
    InitWindow((cellSize * cellCount), (cellSize * cellCount), "Shape Collider");

    SetWindowPosition(250, 100);

    SetTargetFPS(60);

    Game game;

    size_t ballNumber = 200;

    generateMultipleBall(ballNumber, game);

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

    ///////draw title//////
    if (!flagPause) {
        DrawText(titleCStr, x, 80, 40, WHITE);
    }

    /////player input////////
    game.player.userInput();

    game.draw();

    // Draw the integer as text at the specified position (100, 100)
    std::string drawnBallsString = TextFormat("ball drawn: %i BallsQuantity: %i ballsUpdates:%i", game.ballsDrawn, game.getBallsQuantity(), game.ballsUpdates);
    DrawText(drawnBallsString.c_str(), x - 400, 100, 30, RED);

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
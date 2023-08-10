#pragma once

#include "Player.h"
#include "Ball.h"
#include"Brick.h"
#include"SoundManager.h"

#include<chrono>

#include <iomanip> 

#include <vector>

#include <thread> 
extern const int cellSize;

extern const int cellCount;





class Game {
private:

   AudioManager audioManager;


    // Sound death_sound
    // ,brick_sound,
    // reflection_sound;



public:
    int ballsDrawn = 0;
    int ballsUpdates = 0;

    int CountPosition = 0;
    int CountSpeed = 0;


    Player player;


 int brickWidth = 80; // Adjust to your brick's width
    int brickHeight = 40; // Adjust to your brick's height

    // int rowCount = 10; // Number of rows of bricks
    // int verticalSpacing = 0; // Spacing between rows
    int brickCount=0;

std::vector<std::unique_ptr<Brick>> brickVector;

    std::vector<Ball> balls;
    Game();
    ~Game();
    void playerBallCollision(Ball& ballToCheck);

void ballBrickCollision(Ball& ball);

    void createBallInstance(int countPosition, int countSpeed);

    void createBrickInstance(Vector2 pos,Brick::BRICKSIZE brickSize);

    void createMultipleBrick();

    void generateMultipleBall(size_t ballNumber);



    void update();

    void draw();

//////stats//////
    void printAverageSpeeds();

    int getBallsQuantity();

private:
    bool ballShouldBeDeleted(const Ball& ball);
};



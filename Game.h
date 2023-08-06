#pragma once

#include "Player.h"
#include "Ball.h"
#include"Brick.h"
#include<chrono>

#include <iomanip> 

#include <vector>

#include <thread> 

class Game {
public:
    int ballsDrawn = 0;
    int ballsUpdates = 0;

    int CountPosition = 0;
    int CountSpeed = 0;


    Player player;
    std::vector<Ball> balls;

    std::unique_ptr<Brick> brick = std::make_unique<Brick>(Vector2{0,0}, brick->BRICKSIZE::SMALL);



    void playerBallCollision(Ball& ballToCheck);

    void createInstance(int countPosition, int countSpeed);

    void generateMultipleBall(size_t ballNumber);



    void update();

    void draw();

//////stats//////
    void printAverageSpeeds();

    int getBallsQuantity();

private:
    bool ballShouldBeDeleted(const Ball& ball);
};



#pragma once

#include<raylib.h>
#include "Player.h"
#include <raymath.h>
#include<cmath>
#include <iostream>
#include <algorithm>
extern const int cellSize;
extern const int cellCount;

class Ball {
public:
    Vector2 position = { static_cast<float>(cellCount * cellSize / 2 - 1), static_cast<float>(cellCount * cellSize / 2 - 1) };
   // Vector2 direction = { 0.3f, 0.4f };
    Vector2 speed = { 100.0f, 10.0f };
    int radius = static_cast<int>(cellSize);


    // Current boost factor
    float boostFactor = 1.0f;


enum State {
    NORMAL,
    DEAD,
    WALL_COLLISION,
    PLAYER_COLLISION
};
mutable State state; 

public:
    Ball();
Ball(int CountSpeed,int CountPosition);

    Vector2 ballPosition(int CountPosition);

    Vector2 BallSpeed(int CountSpeed);

    //void update(const Player player);

    void update();

    void draw();

    bool isOutOfBound() const;

    void resetState();

    void setState(State newState);

        // Method to get the speed of the ball
    Vector2& getSpeed() ;
     Vector2 getPosition() const;

    

     int getRadius() const;

public :
void updatePosition(float deltaTime);

// void playerBallCollision(const Rectangle & playerRect);
};

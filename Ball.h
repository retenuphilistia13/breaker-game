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

enum State {
    NORMAL,
    DEAD,
    WALL_COLLISION,
    PLAYER_COLLISION
};

enum BallSize{
SMALL,
MEDIUM,
BIG
};



    // Current boost factor
    float boostFactor = 1.0f;
private:
    int maxLimit=500;

    float maxXSpeed = 450.0f;
    
    float maxYSpeed = 450.0f;

    int radius = static_cast<int>(cellSize);

public:
    Vector2 position = { static_cast<float>(cellCount * cellSize / 2 - 1), static_cast<float>(cellCount * cellSize / 2 - 1) };
   // Vector2 direction = { 0.3f, 0.4f };
    Vector2 speed = { 10.0f, 50.0f };
mutable State state; 

mutable BallSize ballSize; 

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
    // Method to calculate the angle of movement
    float calculateAngle() const {
        return atan2(speed.y, speed.x);
    }

Vector2 reflectVector(const Vector2& incoming, const Vector2& normal) {
    // Calculate the dot product between incoming vector and normal
    float dotProduct = incoming.x * normal.x + incoming.y * normal.y;

    // Calculate the reflection vector
    Vector2 reflection;
    reflection.x = incoming.x - 2.0f * dotProduct * normal.x;
    reflection.y = incoming.y - 2.0f * dotProduct * normal.y;

    return reflection;
}



// void playerBallCollision(const Rectangle & playerRect);
};

#pragma once

#include<raylib.h>
#include "Player.h"
#include <raymath.h>
extern const int cellSize;
extern const int cellCount;

class Ball {
public:
    Vector2 position = { static_cast<float>(cellCount * cellSize / 2 - 1), static_cast<float>(cellCount * cellSize / 2 - 1) };
    Vector2 direction = { 0.3f, 0.4f };
    Vector2 ballSpeed = { 1.0f, 1.0f };
    int ballRadius = static_cast<int>(cellSize / 2);



public:
    Ball();
Ball(int CountSpeed,int CountPosition);

    Vector2 ballPosition(int CountPosition);

    Vector2 BallSpeed(int CountSpeed);

    void update();

    void draw();

    bool checkCollisionWithPlayer(const Player& player);

};

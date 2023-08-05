#pragma once

#include<raylib.h>
#include "Player.h"
#include <raymath.h>
#include<cmath>
#include <iostream>
extern const int cellSize;
extern const int cellCount;

class Ball {
public:
    Vector2 position = { static_cast<float>(cellCount * cellSize / 2 - 1), static_cast<float>(cellCount * cellSize / 2 - 1) };
   // Vector2 direction = { 0.3f, 0.4f };
    Vector2 speed = { 100.0f, 10.0f };
    int radius = static_cast<int>(cellSize);


enum State{
ALIVE,
DEAD
};
mutable State state; 

public:
    Ball();
Ball(int CountSpeed,int CountPosition);

    Vector2 ballPosition(int CountPosition);

    Vector2 BallSpeed(int CountSpeed);

    void update(const Player player);

    void draw();

    bool isOutOfBound() const;

};

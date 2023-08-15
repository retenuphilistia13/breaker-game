// #ifndef PLAYER_H
// #define PLAYER_H
#pragma once
#include "raylib.h"
 // Include any necessary headers here
// Use extern to declare the global constants defined in main.cpp
extern const int cellSize;
extern const int cellCount;

class Player {
public:

    Vector2 dimension = { static_cast<float>(cellSize * 5), static_cast<float>(cellSize) };
    Vector2 position = { static_cast<float>(GetScreenWidth() / 2) - (dimension.x / 2), static_cast<float>(cellSize * cellCount) - cellSize * 3 };

    Vector2 PlayerSpeed = { (float)dimension.x/11 , 0.0f };

    //Vector2 direction = { 1.0f, 0.0f };


public:
    Vector2 getSpeed(){

        return PlayerSpeed;
    }

    Vector2 getPosition(){

        return position;
    }
    
    Rectangle getRectangle() const;// Method to get the player's hitbox as a Rectangle

    void draw();
    void update();
    void userInput();

double lastUpdateTime = 0;

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

};

// #endif // PLAYER_H

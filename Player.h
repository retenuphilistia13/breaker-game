// #ifndef PLAYER_H
// #define PLAYER_H
#pragma once
#include <raylib.h> // Include any necessary headers here
// Use extern to declare the global constants defined in main.cpp
extern const int cellSize;
extern const int cellCount;

class Player {
public:

    Vector2 dimension = { static_cast<float>(cellSize * (cellCount/3)), static_cast<float>(cellSize) };
    Vector2 position = { static_cast<float>(GetScreenWidth() / 2) - (dimension.x / 2), static_cast<float>(cellSize * cellCount) - cellSize * 3 };

    Vector2 PlayerSpeed = { 2.0f, 0.0f };
    Vector2 direction = { 0.0f, 0.0f };

public:
    void draw();
    void update();
    void userInput();
};

// #endif // PLAYER_H

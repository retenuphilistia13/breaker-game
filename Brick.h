#pragma once

#include<raylib.h>

extern const int cellSize;
extern const int cellCount;
class Brick{

public:

enum BRICKSIZE{
    BIG,
    SMALL,
    MEDIUM,
};

private:
  Vector2 position{ static_cast<float>(cellSize * cellCount) / 2 , 100 };
    Vector2 dimension{ static_cast<float>(cellSize * 3) , static_cast<float>(cellSize * 1.5) };

bool isActive;

public:


 Brick();

 Brick(Vector2 position1, BRICKSIZE size);

void draw();


public:

    BRICKSIZE brickSize;

void setBrickSize(BRICKSIZE brickSize);

};
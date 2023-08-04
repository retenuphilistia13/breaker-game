// Ball.cpp

#include "Ball.h"

extern const int cellSize;
extern const int cellCount;



Ball::Ball(int countPosition,int countSpeed) {

    position = ballPosition(countPosition);
    speed = BallSpeed(countSpeed);
}

Vector2 Ball::ballPosition(int CountPosition) {
    float x, y = 0;
    x = static_cast<float>(cellCount * cellSize / 2) + static_cast<int>(CountPosition);
    y = static_cast<float>(cellCount * cellSize / 2);
    CountPosition += cellSize * 2;
    return Vector2{ x, y };
}

Vector2 Ball::BallSpeed(int CountSpeed) {
    float x, y = 0;
    x = speed.x + CountSpeed + 2;
    y = speed.y + CountSpeed + 2;
    CountSpeed += 2;
    return Vector2{ x, y };
}

void Ball::update() {


    position.x += speed.x;
    position.y += speed.y;

     if (position.x >= GetScreenWidth() - ballRadius || position.x <= ballRadius) {
            speed.x *= -1.0f;
            position.x += speed.x;
           
        }

        if (position.y >= GetScreenHeight() - ballRadius || position.y <= ballRadius) {
            speed.y *= -1.0f;
            position.y += speed.y;
           
        } 

     // Calculate the ratios for x and y speeds
    float ratioX = speed.x / speed.y;
    float ratioY = speed.y / speed.x;

    if (ratioX < 0.0f) {
        ratioX *= -1.0f;
    }

    if (ratioY < 0.0f) {
        ratioY *= -1.0f;
    }

    const float targetRatio = 0.3f; // Set a fixed threshold for the ratio
    const float maxSpeedChange = 0.5f; // Limit the maximum speed change

    // Adjust speed in x coordinate
    if (ratioX < targetRatio) {
        float speedChangeX = (targetRatio - ratioX) * maxSpeedChange;
        speed.x += speed.x >= 0.0f ? speedChangeX : -speedChangeX;
    }

    // Adjust speed in y coordinate
    if (ratioY < targetRatio) {
        float speedChangeY = (targetRatio - ratioY) * maxSpeedChange;
        speed.y += speed.y >= 0.0f ? speedChangeY : -speedChangeY;
    }
    //////limit ball maximum speed///////
//// crazy ball code////
// if(speed.x>10.0f){
//     speed.x-=0.2f;
// }
// if(speed.y>10.0f)
// speed.y-=0.2f;
// 

////sane way to do it//////
    const float maxSpeed = 10.0f;


    float speedMagnitude = sqrtf(speed.x * speed.x + speed.y * speed.y);

    // Normalize the speed vector
    if (speedMagnitude > maxSpeed) {
        float scale = maxSpeed / speedMagnitude;
        speed.x *= scale;
        speed.y *= scale;
    }

}

void Ball::draw() {
    DrawCircleV(position, static_cast<float>(ballRadius), MAROON);
}





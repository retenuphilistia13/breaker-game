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

    return Vector2{ x, y };
}

Vector2 Ball::BallSpeed(int CountSpeed) {
    float x, y = 0;
    x = speed.x + CountSpeed + 2;
    y = speed.y + CountSpeed + 2;

    return Vector2{ x, y };
}
void Ball::update(const Player player) {
    float deltaTime = GetFrameTime(); // Get the delta time in seconds

    position.x += speed.x * deltaTime;
    position.y += speed.y * deltaTime;

    if ((position.x >= GetScreenWidth() - radius || position.x <= radius) ) {//for right wall position.x >= GetScreenWidth() for left wall position.x <= radius
        speed.x *= -1.0f;
        position.x += speed.x * deltaTime; // Move the ball one more frame to prevent sticking to the wall
    }
    if(position.x >= GetScreenWidth() + radius || position.x <= 0){
state=State::DEAD;
std::cout<<"out of bound"<<std::endl;
    }

    if ( position.y <= radius) {//ball bounce only on the top wall
        speed.y *= -1.0f;
        position.y += speed.y * deltaTime; // Move the ball one more frame to prevent sticking to the wall
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

    const float targetRatio = 500.0f; // Set a fixed threshold for the ratio
    const float maxSpeedChange = 700.0f; // Limit the maximum speed change

    // Adjust speed in x coordinate
    if (ratioX > targetRatio) {
        float speedChangeX = (targetRatio - ratioX) * maxSpeedChange;
        speed.x -= speed.x >= 0.0f ? speedChangeX : -speedChangeX;
    }

    // Adjust speed in y coordinate
    if (ratioY > targetRatio) {
        float speedChangeY = (targetRatio - ratioY) * maxSpeedChange;
        speed.y -= speed.y >= 0.0f ? speedChangeY : -speedChangeY;
    }

    // // Limit ball maximum speed
    const float maxSpeed = maxSpeedChange*1.2;
    float speedMagnitude = sqrtf(speed.x * speed.x + speed.y * speed.y);

    // Normalize the speed vector
    if (speedMagnitude > maxSpeed) {
        float scale = maxSpeed / speedMagnitude;
        speed.x *= scale;
        speed.y *= scale;
    }
}


void Ball::draw() {
    DrawCircleV(position, static_cast<float>(radius), MAROON);
}

bool Ball::isOutOfBound() const{

        if ( position.y >= GetScreenHeight()+radius) {//delete it after its unseen
            state=State::DEAD;
            return true;
        }else{
        return false;}
}



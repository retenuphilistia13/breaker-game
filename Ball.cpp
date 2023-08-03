// Ball.cpp

#include "Ball.h"

extern const int cellSize;
extern const int cellCount;



Ball::Ball(int countPosition,int countSpeed) {

    position = ballPosition(countPosition);
    ballSpeed = BallSpeed(countSpeed);
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
    x = ballSpeed.x + CountSpeed + 2;
    y = ballSpeed.y + CountSpeed + 2;
    CountSpeed += 2;
    return Vector2{ x, y };
}

void Ball::update() {


    position.x += ballSpeed.x;
    position.y += ballSpeed.y;

     if (position.x >= GetScreenWidth() - ballRadius || position.x <= ballRadius) {
            ballSpeed.x *= -1.0f;
            position.x += ballSpeed.x;
           
        }

        if (position.y >= GetScreenHeight() - ballRadius || position.y <= ballRadius) {
            ballSpeed.y *= -1.0f;
            position.y += ballSpeed.y;
           
        }
}

void Ball::draw() {
    DrawCircleV(position, static_cast<float>(ballRadius), MAROON);
}

 bool Ball::checkCollisionWithPlayer(const Player& player) {
        // Calculate the swept AABB for the ball's movement

        // Check collision with the player's rectangle
        if (CheckCollisionCircleRec(position, static_cast<float>(ballRadius),
            (Rectangle){ player.position.x - player.dimension.x / 2, player.position.y - player.dimension.y / 2, player.dimension.x, player.dimension.y }))
        {
            if (ballSpeed.y > 0) {
                ballSpeed.y *= -1.0f;
                // Adjust the ball's x-speed based on the position relative to the player's center
                ballSpeed.x = (position.x - player.position.x) / (player.dimension.x / 2) * 5.0f;
            }

            return true;
        }

        return false;
    }
// Ball.cpp

#include "Ball.h"

extern
const int cellSize;
extern
const int cellCount;

const float maxSpeedChange = 40.5f;

Ball::Ball(int countPosition, int countSpeed) {

    position = ballPosition(countPosition);
    speed = BallSpeed(countSpeed);
    state = State::NORMAL; // Initialize state to NORMAL
}

Vector2 Ball::ballPosition(int CountPosition) {
    float x, y = 0;
    x = static_cast < float > (cellCount * cellSize / 2) + static_cast < int > (CountPosition);
    y = static_cast < float > (cellCount * cellSize / 2);

    return Vector2 {
        x,
        y
    };
}

Vector2 Ball::BallSpeed(int CountSpeed) {
    float x, y = 0;
    x = speed.x + CountSpeed + 2;
    y = speed.y + CountSpeed + 2;

    return Vector2 {
        x,
        y
    };
}

void Ball::update() {
    float deltaTime = GetFrameTime(); // Get the delta time in seconds

    updatePosition(deltaTime);

    // Check if the ball hits the left or right wall
    if (position.x >= GetScreenWidth() - radius || position.x <= radius) {
        // Reverse the x-speed and apply the boost
        speed.x *= -1.0f;

        position.x += speed.x * deltaTime; // Move the ball one more frame to prevent sticking to the wall
        state = State::WALL_COLLISION;
    }

    // Check if the ball hits the top wall
    if (position.y <= radius) {
        // Reverse the y-speed and apply the boost
        speed.y *= -1.0f;

        position.y += speed.y * deltaTime; // Move the ball one more frame to prevent sticking to the wall
        state = State::WALL_COLLISION;
    }

   //playerBallCollision(playerRect);

    if (state == State::NORMAL) {
        // Limit the ball's maximum speed in x and y directions
        const float maxXSpeed = 500.0f;
        const float maxYSpeed = 500.0f;

        // Normalize the speed vector
        float speedMagnitude = sqrtf(speed.x * speed.x + speed.y * speed.y);

        if (speedMagnitude > maxXSpeed) {
            float scale = maxXSpeed / speedMagnitude;
            speed.x *= scale;
            speed.y *= scale;
        }

        // Adjust speed in y coordinate
        if (fabsf(speed.y) > maxYSpeed) { // compare using absolute value
            speed.y = copysignf(maxYSpeed, speed.y);
        }

    }
    ////if ball out of bounds ////
    if (position.x >= GetScreenWidth() + radius || position.x <= -radius) {
        state = State::DEAD;
    } else {
        resetState();
    }

}

void Ball::updatePosition(float deltaTime) {

    position.x += speed.x * deltaTime;
    position.y += speed.y * deltaTime;
}

void Ball::draw() {
    DrawCircleV(position, static_cast < float > (radius), MAROON);
}

bool Ball::isOutOfBound() const {

    if (position.y >= GetScreenHeight() + radius) { //delete it after its unseen
        state = State::DEAD;
        return true;
    } else {
        return false;
    }
}

void Ball::resetState() {
    state = State::NORMAL;
};

void Ball::setState(State newState){

state=newState;

}

    // Method to get the speed of the ball
    Vector2& Ball::getSpeed() {
        return speed;
    }

        // Method to get the speed of the ball
    Vector2 Ball::getPosition() const {
        return position;
    }



    int Ball::getRadius() const{

return radius;

    }
// void Ball::playerBallCollision(const Rectangle & playerRect){
//  // Check if the ball hits the player
//     const float playerHitboxSize = 0.0f; // Adjust this value to change the hitbox size
//     if (CheckCollisionCircleRec(position, static_cast < float > (radius), {
//             playerRect.x - playerRect.width * playerHitboxSize,
//             playerRect.y - playerRect.height * playerHitboxSize,
//             playerRect.width * (1 + 2 * playerHitboxSize),
//             playerRect.height * (1 + 2 * playerHitboxSize)
//         })) {
//         // Handle collision between the ball and the player

//         // Calculate the angle of incidence between the ball and the player's center
//         float relativePos = position.x - playerRect.x;
//         float playerCenterX = playerRect.x + playerRect.width / 2;
//         float angleOfIncidence = atan2f(position.y - playerRect.y, relativePos - playerRect.width / 2);

//         // Reflect the ball's velocity based on the angle of incidence
//         float ballSpeedMagnitude = sqrtf(speed.x * speed.x + speed.y * speed.y);
//         speed.x = ballSpeedMagnitude * cosf(angleOfIncidence);
//         speed.y = ballSpeedMagnitude * sinf(angleOfIncidence);

//         // Increase the ball's speed by a constant factor after hitting the player
//         const float speedBoostFactor = 1.3f;
//         speed.x *= speedBoostFactor;
//         speed.y *= speedBoostFactor;

//         state = State::PLAYER_COLLISION;
//     }

// }

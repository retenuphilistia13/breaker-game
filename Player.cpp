#include "Player.h" // Include the Player.h header file

void Player::draw() {
    DrawRectangle(position.x, position.y, dimension.x, dimension.y, BLACK);
}

void Player::update() {
    //position.x += PlayerSpeed.x;
// position.x += direction.x+PlayerSpeed.x;
    if (position.x >= GetScreenWidth() - dimension.x || position.x <= 0) {
        PlayerSpeed.x *= -1.0f;
        position.x += PlayerSpeed.x;
    }
}

void Player::userInput() {

    float moveAmount = dimension.x /8;

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        float moveLeft = position.x - moveAmount;

        if (moveLeft <= 0) {
            position.x = 1;
        } else {
            position.x = moveLeft;
        }
    } else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        float moveRight = position.x + moveAmount;

        if (moveRight >= GetScreenWidth() - dimension.x) {
            position.x = GetScreenWidth() - dimension.x - 1;
        } else {
            position.x = moveRight;
        }
    }
}


// Method to get the player's hitbox as a Rectangle
Rectangle Player::getRectangle() const {
    return { position.x, position.y, dimension.x, dimension.y };
}
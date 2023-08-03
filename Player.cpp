#include "Player.h" // Include the Player.h header file

void Player::draw() {
    DrawRectangle(position.x, position.y, dimension.x, dimension.y, BLACK);
}

void Player::update() {
    position.x += PlayerSpeed.x;
// position.x += direction.x+PlayerSpeed.x;
    if (position.x >= GetScreenWidth() - dimension.x || position.x <= 0) {
        PlayerSpeed.x *= -1.0f;
        position.x += PlayerSpeed.x;
    }
}
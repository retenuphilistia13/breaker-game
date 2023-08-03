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

void Player::userInput(){

if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))
{
    float moveLeft = position.x - (dimension.x / 10);
    
    if (moveLeft <= 0)
    {
        position.x = 1;
    }
    else
    {
        position.x = moveLeft;
    }
}

else if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)))
{
    float moveRight=position.x+(dimension.x/10);

    if(  (moveRight >= GetScreenWidth() - dimension.x) )
 {
  position.x=GetScreenWidth() - dimension.x-1;
 }else if(moveRight >= 0){
    position.x=moveRight;
 }

}

}
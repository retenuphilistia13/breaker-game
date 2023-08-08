

#include"Brick.h"


 Brick::Brick() {
        isActive = true;
        setBrickSize(BRICKSIZE::MEDIUM);
    }

    Brick::Brick(Vector2 position1, BRICKSIZE size) {
        isActive = true;
        this->position = position1;
        setBrickSize(size);
    }

void Brick::draw(){

DrawRectangle(this->position.x, this->position.y, this->dimension.x, this->dimension.y, BLACK);

}

float Brick::getBrickWidth(){
    return dimension.x;
}
float Brick::getBrickHeight(){
return dimension.y;
}

void Brick::setBrickSize(BRICKSIZE brickSize) {

switch(brickSize){
case SMALL:{
// this->dimension={(float)cellSize*2.0f,(float)cellSize*1.2f};
this->dimension={(float)cellSize,(float)cellSize};
break;
}
case MEDIUM:{
this->dimension={(float)cellSize*2.0f,(float)cellSize*1.2f};
 break;
}

case BIG:{
this->dimension={(float)cellSize*3.0f,(float)cellSize*1.5f};
    break;
}


}


}
Vector2 Brick::getPosition(){

    return position;
}

Vector2 Brick::getSize() {
    return dimension; // 'size' is a Vector2 member variable that holds the size of the brick
}

 Vector2 Brick::getVector2ForBrickSize(BRICKSIZE brickSize) {
    static std::map<BRICKSIZE, Vector2> sizeMap = {
        {BRICKSIZE::SMALL, Vector2{(float)cellSize*2.0f,(float)cellSize*1.2f}},
        {BRICKSIZE::BIG, Vector2{(float)cellSize*5.0f,(float)cellSize*4.0f}},
        {BRICKSIZE::MEDIUM, Vector2{(float)cellSize*4.0f,(float)cellSize*2.0f}}
    };

    return sizeMap[brickSize];
}
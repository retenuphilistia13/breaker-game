

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


void Brick::setBrickSize(BRICKSIZE brickSize) {

switch(brickSize){
case SMALL:{
this->dimension={(float)cellSize*2.0f,(float)cellSize*1.2f};
break;
}
case MEDIUM:{
this->dimension={(float)cellSize*4.0f,(float)cellSize*2.0f};
 break;
}

case BIG:{
this->dimension={(float)cellSize*5.0f,(float)cellSize*4.0f};
    break;
}


}


}


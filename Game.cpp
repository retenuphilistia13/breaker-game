
#include"Game.h"
#include "Sounds.h" // Include the enums

void Game::LoadSounds() {
    for (const auto& entry : soundFilePaths) {
        audioManager.LoadCustomSound(entry.second);
    }
}

void Game::UnloadSounds() {
    audioManager.UnloadAllSounds();
}

void Game::PlayCustomSound(SoundFile soundFile) {
    switch (soundFile) {
        case SoundFile::Death:
            audioManager.PlayCustomSound(SoundFile::Death);
            break;
        case SoundFile::BrickExplosion:
            audioManager.PlayCustomSound(SoundFile::BrickExplosion);
            break;
        case SoundFile::Reflect:
            audioManager.PlayCustomSound(SoundFile::Reflect);
            break;
        // Add more cases for other SoundFile enum values if needed
        default:
            TraceLog(LOG_WARNING, "Unknown SoundFile: %d", static_cast<int>(soundFile));
            break;
    }
}

Game::Game() {


 LoadSounds();


}


Game::~Game(){

 //UnloadSounds();
 brickVector.clear();


//unload automatically in audio manager
}




void Game::ballBrickCollision(Ball& ball) {
    for (auto brick = brickVector.begin(); brick != brickVector.end();) {
        auto brickBounds = Rectangle{
            (*brick)->getPosition().x,    // Use (*brick)-> to access the underlying Brick object
            (*brick)->getPosition().y,
            (*brick)->getSize().x,
            (*brick)->getSize().y
        };

        if (CheckCollisionCircleRec(ball.getPosition(), ball.getRadius(), brickBounds)) {
            brick = brickVector.erase(brick);

            ball.speed.y*=-1.0;
PlayCustomSound(SoundFile::BrickExplosion);

           // ball.speed.x*=1.09;//crazy mode
           // ball.updatePosition(GetFrameTime());
            brickCount--;
        } else {
            ++brick;
        }
    }
}





   void Game::playerBallCollision(Ball& ballToCheck) {
    // Check if the ball hits the player
    const float playerHitboxSize = 0.0f; // Adjust this value to change the hitbox size
    if (CheckCollisionCircleRec(ballToCheck.getPosition(), static_cast<float>(ballToCheck.getRadius()), {
            player.position.x - player.dimension.x * playerHitboxSize,
            player.position.y - player.dimension.y * playerHitboxSize,
            player.dimension.x * (1 + 2 * playerHitboxSize),
            player.dimension.y * (1 + 2 * playerHitboxSize)
        })) {
        //////reflection sound/////////
        PlayCustomSound(SoundFile::Reflect);

        
        // Handle collision between the ball and the player

        // Calculate the angle of incidence between the ball and the player's center
        float relativePos = ballToCheck.getPosition().x - player.position.x;
        float playerCenterX = player.position.x + player.dimension.x / 2;
        float angleOfIncidence = atan2f(ballToCheck.getPosition().y - player.position.y, relativePos - player.dimension.x / 2);

        // Calculate the angle of reflection based on the angle of incidence
        float reflectionAngle = PI - angleOfIncidence;

        // Reflect the ball's velocity based on the reflection angle
        float ballSpeedMagnitude = sqrtf(ballToCheck.getSpeed().x * ballToCheck.getSpeed().x + ballToCheck.getSpeed().y * ballToCheck.getSpeed().y);
        ballToCheck.getSpeed().x = -( ballSpeedMagnitude * cosf(reflectionAngle));
        ballToCheck.getSpeed().y = ballSpeedMagnitude * sinf(reflectionAngle);


        // Increase the ball's speed by a constant factor after hitting the player
        const float speedBoostFactor = 1.1f;
        ballToCheck.getSpeed().x *= speedBoostFactor;
        ballToCheck.getSpeed().y *= speedBoostFactor;

        ballToCheck.setState(Ball::State::PLAYER_COLLISION);


    }
}

    void Game::createBallInstance(Vector2 pos, Vector2 speed) {
        balls.emplace_back(pos, speed);
    }



    void Game::update() {

        ////update ball and check collotion///
        player.update();
        for (auto & ball: balls) {

            ball.update();

        playerBallCollision(ball);

        ballBrickCollision(ball);

            printAverageSpeeds(); //average ball speed

            ballsUpdates++;
        }
        
        // Remove balls that are no longer needed
        balls.erase(
            std::remove_if(balls.begin(), balls.end(), [this](const Ball & ball) {

        if(ball.state == Ball::State::WALL_COLLISION){
                   PlayCustomSound(SoundFile::Reflect);

        
            
        }
bool isDeleted=ballShouldBeDeleted(ball);
if(isDeleted==true){
            PlayCustomSound(SoundFile::Death);

        
    //death Sound///
}
    // Cleanup
                return isDeleted;
            }),
            balls.end()
        );
    }

    void Game::draw() {
    for (auto &brick : brickVector) {
        brick->draw();
        //std::cout<<"brick count "<<brickCount<<std::endl;
    }
        for (auto & ball: balls) {
            ball.draw();
            ballsDrawn++;
        }
        player.draw();
    }

    int Game::getBallsQuantity() {
        return balls.size();
    }
    

        // Helper function to determine if a ball should be deleted based on certain conditions.
        bool Game::ballShouldBeDeleted(const Ball & ball) {
            // Check if the ball is off the screen (reached the bottom) for deletion
            if (ball.isOutOfBound()) return true;
            if (ball.state == Ball::State::DEAD) return true;
            if(brickVector.size()<=0)return true;

            return false;
        }


    void Game::generateMultipleBall(size_t ballNumber) {

    for (size_t i = 0; i < ballNumber; ++i) { //crete ball instances
       // CountSpeed = 200;
        Vector2 pos={this->player.getPosition().x-2*cellSize,this->player.getPosition().y-2*cellSize};
        Vector2 speed={200,200};

        createBallInstance(speed, pos);

        CountPosition += cellSize / (ballNumber * 0.1);
    }

}

///helper to generate multiple brick///
void Game::createBrickInstance(Vector2 pos,Brick::BRICKSIZE brickSize){

std::unique_ptr<Brick> brickInstance = std::make_unique<Brick>(Vector2{pos.x, pos.y}, brickSize);
 
 brickVector.push_back(std::move(brickInstance));

  brickCount++;
}

void Game::createMultipleBrick() {
    Brick::BRICKSIZE brickSize = Brick::BRICKSIZE::SMALL;

    Vector2 size = Brick::getVector2ForBrickSize(brickSize);
// Clear any existing bricks from the vector
    brickVector.clear();

  int patternSize = 10; // Size of the face pattern

    // Calculate the total size of the face pattern
    float patternTotalSize = patternSize * size.x;

    // Calculate the starting position for the face to center it
    Vector2 startPosition = {
        (GetScreenWidth() - patternTotalSize) / 2,
        (GetScreenHeight() - patternSize * size.y) / 2
    };

    // Define the face pattern using a 2D array
   int facePattern[patternSize][patternSize];

    // // Populate the array with 1 ///standart
    // for (int row = 0; row < patternSize; ++row) {
    //     for (int col = 0; col < patternSize; ++col) {
        
    //         facePattern[row][col] = 1;
        
    //     }
    // }


// hollow square////
     for (int i = 0; i < patternSize; i++) {

        for (int j = 0; j < patternSize; j++) {// cut the hollow square patternSize/2
      // print only bricks in first and last row
      if (i == 0 || i == patternSize - 1) {
        facePattern[i][j]=1;
      }
      else {
        // print bricks only at first and last position row
        if (j == 0 || j == patternSize - 1) {
          facePattern[i][j]=1;
        }
        else {////empty/////
          facePattern[i][j]=0;
        }

      }

    }
  
  }

   // Populate the array with a right triangle  pattern
    // for (int row = 0; row < patternSize; ++row) {
    //     for (int col = 0; col < patternSize - row - 1; ++col) {
    //         facePattern[row][col] = 0; // Fill with 0 (spaces)
    //     }
    //     for (int col = patternSize - row - 1; col < patternSize + row; ++col) {
    //         facePattern[row][col] = 1; // Fill with 1 (stars)
    //     }
    // }

    // pyramid 
//     int sizeArrX,sizeArrY;

//     sizeArrX=patternSize-2;
//     sizeArrY=2 * patternSize - 3;

//     int facePattern[sizeArrX][sizeArrY];
// startPosition = {
//         (GetScreenWidth() - (float)patternTotalSize*1.5) ,
//         (GetScreenHeight() - patternSize * size.y) / 2
//     };
//     // Populate the array with a pyramid pattern
//     for (int row = 0; row < sizeArrX; ++row) {
//         for (int col = 0; col < sizeArrX - row - 1; ++col) {
//             facePattern[row][col] = 0; // Fill with 0 (spaces)
//         }
//         for (int col = sizeArrX - row - 1; col < sizeArrX + row; ++col) {
//             facePattern[row][col] = 1; // Fill with 1 (stars)
//         }
//     }
  // // Loop over the face pattern and create bricks for pyramid only
    // for (int y = 0; y < sizeArrX; y++) {
    //     for (int x = 0; x <sizeArrY; x++) {
    //         if (facePattern[y][x] == 1) {
    //             Vector2 brickPosition = {
    //                 startPosition.x + x * size.x,
    //                 startPosition.y + y * size.y
    //             };
    //             createBrickInstance(brickPosition, brickSize);
    //         }
    //     }
    // }

    ///standart/////
   for (int y = 0; y < patternSize; y++) {
        for (int x = 0; x <  patternSize ; x++) {
            if (facePattern[y][x] == 1) {
                Vector2 brickPosition = {
                    startPosition.x + x * size.x,
                    startPosition.y + y * size.y
                };
                createBrickInstance(brickPosition, brickSize);
            }
        }
    }

  
}



    // Method to calculate and print the average speed of balls on the screen
    void Game::printAverageSpeeds() {
        // Calculate the average speed in the x direction
        float avgSpeedX = 0.0f;
        float avgSpeedY = 0.0f;

        for (const auto & ball: balls) {
            avgSpeedX += ball.speed.x;
            avgSpeedY += ball.speed.y;
        }

        // Calculate the average speed in the y direction
        if (!balls.empty()) {
            avgSpeedX /= balls.size();
            avgSpeedY /= balls.size();
        }

        // Print the average speeds on the middle of the screen
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();

        // Convert average speeds to strings
        std::ostringstream avgSpeedXStr, avgSpeedYStr,countBrick;
        avgSpeedXStr << std::fixed << std::setprecision(3) << avgSpeedX;
        avgSpeedYStr << std::fixed << std::setprecision(3) << avgSpeedY;

        countBrick << std::fixed << std::setprecision(3) << brickCount;

        // Draw the text on the screen
        int textPosX = screenWidth / 2 - MeasureText("Average Speed (X): 000.000", 20) / 2;
        int textPosY = screenHeight / 2 - 40;
        DrawText(("Average Speed (X): " + avgSpeedXStr.str()).c_str(), textPosX, textPosY, 20, RED);

        textPosY += 40;
        DrawText(("Average Speed (Y): " + avgSpeedYStr.str()).c_str(), textPosX, textPosY, 20, RED);
     textPosY+=40;
       DrawText(("brickCount: " + countBrick.str()).c_str(), textPosX, textPosY, 20, RED);

    };
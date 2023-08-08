
#include"Game.h"
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

            //ball.speed.x*=0.99;//arcade mode (fun mode)
            //ball.speed.x*=1.09;//crazy mode
            ball.updatePosition(GetFrameTime());
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
            // Handle collision between the ball and the player

            // Calculate the angle of incidence between the ball and the player's center
            float relativePos = ballToCheck.getPosition().x - player.position.x;
            float playerCenterX = player.position.x + player.dimension.x / 2;
            float angleOfIncidence = atan2f(ballToCheck.getPosition().y - player.position.y, relativePos - player.dimension.x / 2);

            // Reflect the ball's velocity based on the angle of incidence
            float ballSpeedMagnitude = sqrtf(ballToCheck.getSpeed().x * ballToCheck.getSpeed().x + ballToCheck.getSpeed().y * ballToCheck.getSpeed().y);
            ballToCheck.getSpeed().x = ballSpeedMagnitude * cosf(angleOfIncidence);
            ballToCheck.getSpeed().y = ballSpeedMagnitude * sinf(angleOfIncidence);

            // Increase the ball's speed by a constant factor after hitting the player
            const float speedBoostFactor = 1.3f;
            ballToCheck.getSpeed().x *= speedBoostFactor;
            ballToCheck.getSpeed().y *= speedBoostFactor;

            ballToCheck.setState(Ball::State::PLAYER_COLLISION);
        }
    }

    void Game::createBallInstance(int countPosition, int countSpeed) {
        balls.emplace_back(countPosition, countSpeed);
    }

    // void ballSpeedRegulator(Ball & ball) {
    //     if (-ball.speed.x * 2 < ball.speed.y) {
    //         ball.speed.x += ball.speed.y / 3;
    //     } else if (-ball.speed.y * 2 < ball.speed.x) {

    //         ball.speed.y += ball.speed.x / 3;
    //     }

    // }
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

                return ballShouldBeDeleted(ball);
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

            return false;
        }


    void Game::generateMultipleBall(size_t ballNumber) {

    for (size_t i = 0; i < ballNumber; ++i) { //crete ball instances
        CountSpeed = 200;
        createBallInstance(CountPosition, CountSpeed);

        CountPosition += cellSize / (ballNumber * 0.1);
    }

}
// void Game::createBrickInstance(Vector2 position){
//    Brick::BRICKSIZE brickSize = Brick::BRICKSIZE::SMALL;

//     Vector2 size = Brick::getVector2ForBrickSize(brickSize);

//     int brickSpacingX = size.x / 3; // Initialize spacing for each brick in a row
//     int brickSpacingY = size.y / 3; // Initialize spacing for each row of bricks

//     brickWidth = size.x;
//     brickHeight = size.y;

//     for (int row = 0; row < rowCount; ++row) {
//         for (int col = 0; col < cellCount; ++col) {
//             int x = col * (brickWidth + brickSpacingX);
//             int y = row * (brickHeight + brickSpacingY);

//             // Check if the brick is within the screen boundaries
//             if (x + brickWidth > 0 && x < GetScreenWidth()-brickSpacingX && y + brickHeight > 0 && y < GetScreenHeight()-brickSpacingY) {
//                 std::unique_ptr<Brick> brickInstance = std::make_unique<Brick>(Vector2{x, y}, brickSize);
//                 brickVector.push_back(std::move(brickInstance));
//                 brickCount++;
//             }
//         }
//     }
    
// }


void Game::createMultipleBrick() {
    Brick::BRICKSIZE brickSize = Brick::BRICKSIZE::MEDIUM;

    Vector2 size = Brick::getVector2ForBrickSize(brickSize);

    float brickSpacingX = size.x / 40; // Initialize spacing for each brick in a row
    float brickSpacingY = size.y / 30; // Initialize spacing for each row of bricks

    brickWidth = size.x;
    brickHeight = size.y;

    Vector2 startRowRange = {3, 8}; // Specify the start and end rows
    Vector2 startColRange = {1, (float)cellCount - 2}; // Specify the start and end columns

    for (int row = startRowRange.x; row < startRowRange.y; ++row) {
        for (int col = startColRange.x; col < startColRange.y; ++col) {
            float x =(float) col * (brickWidth + brickSpacingX) + (brickSpacingX * (col - startColRange.x));
            float y =(float) row * (brickHeight + brickSpacingY);

            // Debugging: Print calculated x and y positions
            //std::cout << "Row: " << row << " Col: " << col << " X: " << x << " Y: " << y << std::endl;

            if (x + brickWidth > 0 && x < GetScreenWidth() - (brickWidth + brickSpacingX) && y + brickHeight > 0 && y < GetScreenHeight() - (brickHeight + brickSpacingY)) {
createBrickInstance({x,y},brickSize);
            }
        }
    }
}

///helper to generate multiple brick///
void Game::createBrickInstance(Vector2 pos,Brick::BRICKSIZE brickSize){

std::unique_ptr<Brick> brickInstance = std::make_unique<Brick>(Vector2{pos.x, pos.y}, brickSize);
 
 brickVector.push_back(std::move(brickInstance));

  brickCount++;
}

                // if((brickSpacing*cellSize)>GetScreenWidth())

                //     {brickNewLine+=cellSize; brickSpacing=0;}else{
                //         brickNewLine=cellSize;
                //     }
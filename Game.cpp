
#include"Game.h"

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

    void Game::createInstance(int countPosition, int countSpeed) {
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
        std::ostringstream avgSpeedXStr, avgSpeedYStr;
        avgSpeedXStr << std::fixed << std::setprecision(3) << avgSpeedX;
        avgSpeedYStr << std::fixed << std::setprecision(3) << avgSpeedY;

        // Draw the text on the screen
        int textPosX = screenWidth / 2 - MeasureText("Average Speed (X): 000.000", 20) / 2;
        int textPosY = screenHeight / 2 - 40;
        DrawText(("Average Speed (X): " + avgSpeedXStr.str()).c_str(), textPosX, textPosY, 20, RED);

        textPosY += 40;
        DrawText(("Average Speed (Y): " + avgSpeedYStr.str()).c_str(), textPosX, textPosY, 20, RED);

    }

    void Game::update() {

        ////update ball and check collotion///
        player.update();
        for (auto & ball: balls) {

            ball.update();

            playerBallCollision(ball);

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

        for (auto & ball: balls) {
            
            brick->draw();

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
        createInstance(CountPosition, CountSpeed);

        CountPosition += cellSize / (ballNumber * 0.1);
    }

}


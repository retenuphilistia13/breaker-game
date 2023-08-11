#pragma once

#include "Player.h"
#include "Ball.h"
#include"Brick.h"

#include"SoundManager.h"
#include <unordered_map>

#include<chrono>

#include <iomanip> 

#include <vector>

#include <thread> 
#include "Sounds.h" // Include the enums

extern const int cellSize;

extern const int cellCount;

// Forward declaration of AudioManager
// class AudioManager;

// enum class SoundFile;
enum class SoundFile; // Forward declare the enum

class Game {

private:


    // Map to associate each SoundFile enum with its file path
    const std::unordered_map<SoundFile, const char*> soundFilePaths = {
            {SoundFile::AnotherSound, "sounds/another_sound.wav"},
    {SoundFile::YetAnotherSound, "sounds/yet_another_sound.wav"},
        {SoundFile::Reflect, "sounds/reflect.wav"},
        {SoundFile::BrickExplosion, "sounds/brick_Explosian.wav"},
        {SoundFile::Death, "sounds/death.wav"}
        
    };


   AudioManager audioManager;

    const char* GetFilePathForSound(SoundFile soundFile) {
        auto it = soundFilePaths.find(soundFile);
        if (it != soundFilePaths.end()) {
            return it->second;
        }
        return nullptr;
    }
    // Sound death_sound
    // ,brick_sound,
    // reflection_sound;



public:


    void LoadSounds();
    void UnloadSounds();
    void PlayCustomSound(SoundFile soundFile);

    // Method to load and play a sound using the SoundFile enum


    int ballsDrawn = 0;
    int ballsUpdates = 0;

    int CountPosition = 0;
    int CountSpeed = 0;


    Player player;


 int brickWidth = 80; // Adjust to your brick's width
    int brickHeight = 40; // Adjust to your brick's height

    // int rowCount = 10; // Number of rows of bricks
    // int verticalSpacing = 0; // Spacing between rows
    int brickCount=0;

std::vector<std::unique_ptr<Brick>> brickVector;

    std::vector<Ball> balls;
    Game();
    ~Game();
    void playerBallCollision(Ball& ballToCheck);

void ballBrickCollision(Ball& ball);

    void createBallInstance(int countPosition, int countSpeed);

    void createBrickInstance(Vector2 pos,Brick::BRICKSIZE brickSize);

    void createMultipleBrick();

    void generateMultipleBall(size_t ballNumber);



    void update();

    void draw();

//////stats//////
    void printAverageSpeeds();

    int getBallsQuantity();

private:
    bool ballShouldBeDeleted(const Ball& ball);
};



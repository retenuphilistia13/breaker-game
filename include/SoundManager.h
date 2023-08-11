#pragma once
#include "raylib.h"


#include<vector>
#include <cstddef> // Add this include for 'size_t'
// Forward declaration of SoundFile enum from Game.h

#include "Sounds.h" // Include the enums


class AudioManager {
public:
    AudioManager();
    ~AudioManager();

    void LoadCustomSound(const char* filePath);
    void UnloadAllSounds();
    void PlayCustomSound(SoundFile soundFile);

private:
    std::vector<Sound> sounds;
};
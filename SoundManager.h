#pragma once
#include<raylib.h>
#include<vector>
#include <cstddef> // Add this include for 'size_t'

class AudioManager {
public:
    AudioManager();
    ~AudioManager();

    void LoadCustomSound(const char* filePath);
    void PlayCustomSound(int i);
    void UnloadCustomSounds();
        
    
private:
    std::vector<Sound> sounds;
};
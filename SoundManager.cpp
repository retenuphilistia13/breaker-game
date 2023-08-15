#include"SoundManager.h"

// #include "Game.h" // Include Game here for the enum


AudioManager::AudioManager() {
 InitAudioDevice();

}

AudioManager::~AudioManager() {
   UnloadAllSounds();
 CloseAudioDevice();
}


void AudioManager::LoadCustomSound(const char* filePath) {
    sounds.push_back(LoadSound(filePath));
}

void AudioManager::UnloadAllSounds() {
    for (const auto& sound : sounds) {
        UnloadSound(sound);
    }
    sounds.clear();
}

void AudioManager::PlayCustomSound(SoundFile soundFile) {
    if (static_cast<size_t>(soundFile) < sounds.size()) {
        PlaySound(sounds[static_cast<size_t>(soundFile)]);
    }
}



    

#include"SoundManager.h"



AudioManager::AudioManager() {
    InitAudioDevice();
}

AudioManager::~AudioManager() {
    CloseAudioDevice();
}

void AudioManager::LoadCustomSound(const char* filePath) {
    sounds.push_back(LoadSound(filePath));
}

void AudioManager::PlayCustomSound(int i) {
    if (i >= 0 && static_cast<size_t>(i) < sounds.size()) {
        PlaySound(sounds[i]);
    }
}

void AudioManager::UnloadCustomSounds() {
    for (size_t i = 0; i < sounds.size(); ++i) {
        UnloadSound(sounds[i]);
    }
    sounds.clear();
}



    

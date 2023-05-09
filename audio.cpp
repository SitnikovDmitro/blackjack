#include "audio.h"

Audio::Audio() {

}

Audio& Audio::getInstance() {
    static Audio instance;
    return instance;
}

void Audio::playCardSound() const {

}

bool Audio::isSoundEnabled() const {
    return soundEnabled;
}

void Audio::setSoundEnabled(const bool enabled) {
    soundEnabled = enabled;
}

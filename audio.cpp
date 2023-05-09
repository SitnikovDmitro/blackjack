#include "audio.h"
#include <QSoundEffect>
#include <QDebug>

Audio::Audio() {
    cardSound.setSource(QUrl(":/sounds/sound.mp3"));
}

Audio& Audio::getInstance() {
    static Audio instance;
    return instance;
}

void Audio::playCardSound() {
    if (soundEnabled) {
        cardSound.play();
        qDebug() << "Sound played!";
    }
}

bool Audio::isSoundEnabled() const {
    return soundEnabled;
}

void Audio::setSoundEnabled(const bool enabled) {
    soundEnabled = enabled;
}

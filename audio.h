#ifndef AUDIO_H
#define AUDIO_H

#include <QSoundEffect>

class Audio
{
private:
    QSoundEffect cardSound;
    bool soundEnabled = true;
public:
    Audio();
    static Audio& getInstance();
    void playCardSound();
    bool isSoundEnabled() const;
    void setSoundEnabled(const bool enabled);
};

#endif // AUDIO_H

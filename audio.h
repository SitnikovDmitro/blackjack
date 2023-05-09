#ifndef AUDIO_H
#define AUDIO_H


class Audio
{
private:
    bool soundEnabled;
public:
    Audio();
    static Audio& getInstance();
    void playCardSound() const;
    bool isSoundEnabled() const;
    void setSoundEnabled(const bool enabled);
};

#endif // AUDIO_H

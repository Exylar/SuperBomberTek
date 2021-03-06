/*
** EPITECH PROJECT, 2020
** joujou_cmake
** File description:
** MusicManager
*/

#include "Exceptions.h"
#include "MusicManager.hpp"

Indie::MusicManager::MusicManager()
    : musics()
    , currentMusic(0)
    , volume(100)
    , isMuted(false)
    , isPlaying(false)
{
}

void Indie::MusicManager::addMusic(const std::string filepath)
{
    auto ptr = std::make_unique<Indie::Music>(filepath);

    ptr->loop();
    ptr->setVolume((float)volume);
    if (isMuted)
        ptr->setVolume(0);
    musics.push_back(std::move(ptr));
}

void Indie::MusicManager::setMusic(size_t id)
{
    if (id >= musics.size())
        throw Indie::Exceptions::InvalidIndexException(ERROR_STR, "Music at index " + std::to_string(id) + " doesn't exist.");
    if (id == currentMusic)
        return;
    for (size_t i = 0; i < musics.size(); i++)
        musics[i]->stopMusic();
    currentMusic = id;
    if (isPlaying)
        musics[currentMusic]->playMusic();
}

void Indie::MusicManager::setVolume(int vol)
{
    for (size_t i = 0; i < musics.size(); i++) {
        if (!isMuted)
            musics[i]->setVolume(float((vol + 3) / 4));
    }
    volume = vol;
}

int Indie::MusicManager::getMusicVolume(void) const
{
    return this->volume;
}

void Indie::MusicManager::mute()
{
    setVolume(0);
    isMuted = true;
}

void Indie::MusicManager::unMute()
{
    setVolume(volume);
    isMuted = false;
}

void Indie::MusicManager::playMusic()
{
    pauseMusic();
    musics[currentMusic]->playMusic();
    isPlaying = true;
}

void Indie::MusicManager::pauseMusic()
{
    musics[currentMusic]->pauseMusic();
    isPlaying = false;
}

void Indie::MusicManager::stopMusic()
{
    musics[currentMusic]->stopMusic();
    isPlaying = false;
}

void Indie::MusicManager::restartMusic()
{
    stopMusic();
    playMusic();
}

void Indie::MusicManager::update()
{
    for (size_t i = 0; i < musics.size(); i++) {
        musics[i]->update();
    }
}

Indie::Music::Status Indie::MusicManager::getStatus()
{
    return musics[currentMusic]->getStatus();
}

void Indie::MusicManager::setStatus(Indie::Music::Status status)
{
    musics[currentMusic]->setStatus(status);
}

bool Indie::MusicManager::isMusicMuted() const
{
    return isMuted;
}
#include <QFileInfo>
#include <QDebug>
#include "AudioPlayer.h"
#include "Track.h"
#include "TrackList.h"

AudioPlayer::AudioPlayer() {
    player_ = new QMediaPlayer;
    connect(player_, SIGNAL(positionChanged(qint64)), this, SLOT(changePosition(qint64)));
    connect(player_, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(onMediaStatusChanged(QMediaPlayer::MediaStatus)));
    connect(player_, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(onMediaStateChanged(QMediaPlayer::State)));
}

AudioPlayer::~AudioPlayer() = default;

void AudioPlayer::openFile(const QString& fileLocation) {
    std::shared_ptr<Track> t = TrackList::createTrack(fileLocation);
    addTrack(t);
    openTrack(currentTrack_);
}

void AudioPlayer::play() {
    player_->play();
}

void AudioPlayer::pause() {
    player_->pause();
}

void AudioPlayer::stop() {
    player_->stop();
}

int AudioPlayer::getVolume() {
    return player_->volume();
}

void AudioPlayer::setVolume(int volume) {
    player_->setVolume(volume);
}

int AudioPlayer::getPosition() {
    return player_->position();
}

void AudioPlayer::setPosition(int position) {
    player_->setPosition(position);
}

bool AudioPlayer::isPlaying() {
    return player_->state() == QMediaPlayer::PlayingState;
}

int AudioPlayer::getDuration() {
    return player_->duration();
}

void AudioPlayer::changePosition(qint64 position) {
    emit posChanged(position);
}

void AudioPlayer::addTrack(const std::shared_ptr<Track>& track) {
    currentTrack_ = track;
}

void AudioPlayer::onMediaStatusChanged(QMediaPlayer::MediaStatus status) {
    if (status == QMediaPlayer::LoadedMedia) {
        emit mediaLoaded(currentTrack_);
        play();
    } else if (status == QMediaPlayer::InvalidMedia) {
        // Output error string if there was a problem loading the file
        qDebug() << player_->errorString();
    }
}

void AudioPlayer::openTrack(const std::shared_ptr<Track>& track) {
    currentTrack_ = track;
    player_->setMedia(QUrl::fromLocalFile((QFileInfo(currentTrack_->getFileLocation()).absoluteFilePath())));
}

void AudioPlayer::onMediaStateChanged(QMediaPlayer::State state) {
    emit stateChanged(state);
}

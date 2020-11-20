#include <QStyle>
#include <QToolButton>
#include <QSlider>
#include <QBoxLayout>
#include <memory>
#include "PlaybackCtrls.h"

PlaybackCtrls::PlaybackCtrls(QWidget *parent) : QWidget(parent), playButton(nullptr), volumeSlider(nullptr), positionSlider(nullptr), nextButton(nullptr), prevButton(nullptr),
                                                durationLabel(nullptr), currentPositionLabel(nullptr) {
    playButton = new QToolButton(this);
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    volumeSlider = new CustomSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);
    volumeSlider->setSliderPosition(50);

    positionSlider = new CustomSlider(Qt::Horizontal, this);
    positionSlider->setRange(0, 10000);

    nextButton = new QToolButton(this);
    nextButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));

    prevButton = new QToolButton(this);
    prevButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));

    durationLabel = new QLabel(this);
    durationLabel->setText("0:00");

    currentPositionLabel = new QLabel(this);
    currentPositionLabel->setText("0:00");

    connect(playButton, SIGNAL(clicked()), this, SLOT(playClicked()));
    connect(volumeSlider, SIGNAL(valueChanged(int)), this, SIGNAL(changeVolume(int)));
    connect(positionSlider, SIGNAL(sliderReleased()), this, SLOT(sendNewSliderPosition()));
    connect(nextButton, SIGNAL(clicked()), this, SIGNAL(next()));
    connect(prevButton, SIGNAL(clicked()), this, SIGNAL(previous()));

    QBoxLayout *ctrlsLayout = new QHBoxLayout;
    ctrlsLayout->addWidget(prevButton);
    ctrlsLayout->addWidget(playButton);
    ctrlsLayout->addWidget(nextButton);
    ctrlsLayout->addWidget(currentPositionLabel);
    ctrlsLayout->addWidget(positionSlider);
    ctrlsLayout->addWidget(durationLabel);
    ctrlsLayout->addWidget(volumeSlider);
    this->setLayout(ctrlsLayout);
    this->adjustSize();
}

void PlaybackCtrls::playClicked() {
    if (btnState == "play") {
        emit play();
    } else if (btnState == "pause") {
        emit pause();
    } 
}

void PlaybackCtrls::setVolume(int volume) {
    volumeSlider->setValue(volume);
}

void PlaybackCtrls::setPosition(int position) {
    positionSlider->setSliderPosition(position);
}

void PlaybackCtrls::sendNewSliderPosition() {
    emit changePosition(positionSlider->sliderPosition());
}

bool PlaybackCtrls::checkPositionSliderDown() {
    return positionSlider->isSliderDown();
}

void PlaybackCtrls::onMediaLoaded(std::shared_ptr<Track> &track) {
    durationLabel->setText(formatSecondsToMinutesString(track->getDuration()));
}

void PlaybackCtrls::onTrackPositionUpdated(int newPos) {
    currentPositionLabel->setText(formatSecondsToMinutesString(newPos));
}

QString PlaybackCtrls::formatSecondsToMinutesString(int totalSeconds) {
    int minutes = totalSeconds / 60;
    int remainingSeconds = totalSeconds % 60;
    return remainingSeconds > 9
	? QString::number(minutes) + ":" + QString::number(remainingSeconds)
    	: QString::number(minutes) + ":" + "0" + QString::number(remainingSeconds);
}

void PlaybackCtrls::onMediaStateChanged(QMediaPlayer::State newState) {
    if (newState == QMediaPlayer::PlayingState) {
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        btnState = "pause";
    } else {
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        btnState = "play";
    }
}

#include "PlayerGUI.h"
#include "ui_PlayerGUI.h"
#include <iostream>
#include <QFileDialog>
#include <cmath>
#include <QKeyEvent>

PlayerGUI::PlayerGUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerGUI),
    audioPlayer(new AudioPlayer)
{
    ui->setupUi(this);

    audioPlayer->setVolume(25); // Maybe get rid of these hard-coded values...

    ui->trackList->setPlayer(audioPlayer);


    // Set up connections to playback controls
    connect(ui->ctrls, SIGNAL(play()), this, SLOT(play()));
    connect(ui->ctrls, SIGNAL(pause()), this, SLOT(pause()));
    connect(ui->ctrls, SIGNAL(changeVolume(int)), this, SLOT(setVolume(int)));
    connect(ui->ctrls, SIGNAL(changePosition(int)), this, SLOT(setPositionFromSlider(int)));
    connect(ui->ctrls, SIGNAL(next()), this, SLOT(next()));
    connect(ui->ctrls, SIGNAL(previous()), this, SLOT(previous()));

    // Set up connections to audioPlayer
    connect(audioPlayer, SIGNAL(posChanged(qint64)), this, SLOT(setSliderPositionFromTrack(qint64)));
    connect(audioPlayer, SIGNAL(mediaLoaded(std::shared_ptr<Track>&)), ui->currentMetadata, SLOT(onMediaLoaded(std::shared_ptr<Track>&)));
    connect(audioPlayer, SIGNAL(mediaLoaded(std::shared_ptr<Track>&)), ui->ctrls, SLOT(onMediaLoaded(std::shared_ptr<Track>&)));
    connect(audioPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), ui->ctrls, SLOT(onMediaStateChanged(QMediaPlayer::State)));

    this->setFolder();
}

PlayerGUI::~PlayerGUI()
{
    delete ui;
}

void PlayerGUI::toggleTlist() {
    auto *w = ui->trackList;
    bool b = w->isVisible();
    w->setVisible(!b);
    auto *w2 = ui->currentMetadata;
    bool m = w2->isVisible();
    w2->setVisible(!m);
}

void PlayerGUI::resetFolder() {
    ui->trackList->clear();
}

void PlayerGUI::mute() {
    if (audioPlayer->getVolume() != 0) {
            setVolume(0);
    }
    else 
    {
        setVolume(50);
    }

}

void PlayerGUI::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this,
    QObject::tr("Open File"), "/home", QObject::tr("Audio files (*.mp3)"));
    audioPlayer->openFile(fileName);
}

void PlayerGUI::setFolder() {
   QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->trackList->load(dir);
}

void PlayerGUI::play() {
    audioPlayer->play();
}

void PlayerGUI::pause() {
    audioPlayer->pause();
}

void PlayerGUI::setVolume(int volume) {
    qreal linear = QAudio::convertVolume(volume / qreal(100.0), QAudio::LogarithmicVolumeScale, QAudio::LinearVolumeScale);
    audioPlayer->setVolume(qRound(linear * 100));
}

void PlayerGUI::setSliderPositionFromTrack(qint64 position) {
    if (!ui->ctrls->checkPositionSliderDown()) {
        float coef = float(position)/float(audioPlayer->getDuration());
        ui->ctrls->setPosition(coef*10000);
    }
    // Tell playback controls to update the track position label
    ui->ctrls->onTrackPositionUpdated(std::round(position/1000));
}

void PlayerGUI::setPositionFromSlider(int position) {
    float coef = float(position)/10000;
    audioPlayer->setPosition(int(coef*audioPlayer->getDuration()));
}

void PlayerGUI::next() {
    ui->trackList->nextTrack();
}

void PlayerGUI::previous() {
    ui->trackList->prevTrack();
}

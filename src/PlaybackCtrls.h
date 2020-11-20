#ifndef PLAYBACKCTRLS_H
#define PLAYBACKCTRLS_H

#include <QAbstractButton>
#include <QAbstractSlider>
#include <QLabel>
#include <QWidget>
#include "Track.h"
#include "CustomSlider.h"
#include <QMediaPlayer>

class PlaybackCtrls : public QWidget {

    Q_OBJECT 

public: 
    explicit PlaybackCtrls(QWidget *parent = nullptr);
    bool checkPositionSliderDown();

    /**
     * Handle updates to track position. Sets the current playback position label to the appropriate value. Position in seconds.
     * @param newPos
     */
    void onTrackPositionUpdated(int newPos);

public slots:
    void playClicked();
    void setVolume(int volume);
    void setPosition(int position);
    void sendNewSliderPosition();

    /**
     * React to media being loaded. Updates the track's duration label to the appropriate value.
     * @param track
     */
    void onMediaLoaded(std::shared_ptr<Track>& track);

    /**
     * React to changes in the player's state. Changes the play/pause icon and state to be appropriate.
     * @param newState
     */
    void onMediaStateChanged(QMediaPlayer::State newState);

signals:
    void play();
    void pause();
    void changeVolume(int volume);
    void changePosition(int position);
    void next();
    void previous();

private:
    QAbstractButton *playButton;
    CustomSlider *volumeSlider;
    CustomSlider *positionSlider;
    QAbstractButton *nextButton;
    QAbstractButton *prevButton;
    QLabel *durationLabel;
    QLabel *currentPositionLabel;
    std::string btnState = "play";

    /**
     * Formats the given amount of seconds to a string that represents time in the format m:ss.
     * @param totalSeconds
     * @return
     */
    static QString formatSecondsToMinutesString(int totalSeconds);
};

#endif
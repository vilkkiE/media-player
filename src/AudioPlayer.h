#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QMediaPlayer>
#include <memory>

class Track;

class AudioPlayer : public QObject {

    Q_OBJECT 

public:
    /**
     * Constructor. Creates the QMediaPlayer and connects the necessary signals to the corresponding slots.
     */
    AudioPlayer();

    /**
     * Default destructor.
     */
    ~AudioPlayer() override;

    /**
     * Tries to create a Track object based on the file in the fileLocation and then starts playing it.
     * @param fileLocation
     */
    void openFile(const QString& fileLocation);

    /**
     * Sets the given track as currentTrack and starts playing it.
     * @param track
     */
    void openTrack(const std::shared_ptr<Track>& track);

    /**
     * Play the current loaded media.
     */
    void play();

    /**
     * Pause the current loaded media.
     */
    void pause();

    /**
     * Stop the current loaded media.
     */
    void stop();

    /**
     * Return the current playback volume.
     * @return
     */
    int getVolume();

    /**
     * Set the playback volume to the given value.
     * @param volume
     */
    void setVolume(int volume);

    /**
     * Return the playback position of the currently loaded media. Returns 0 if no media is loaded.
     * @return
     */
    int getPosition();

    /**
     * Set the playback position of the loaded media to the given position.
     * @param position
     */
    void setPosition(int position);

    /**
     * Return whether any media is currently playing.
     * @return
     */
    bool isPlaying();

    /**
     * Get the duration of the currentTrack. Returns 0 if no media is loaded.
     * @return
     */
    int getDuration();

    /**
     * Sets the given track as currentTrack.
     */
    void addTrack(const std::shared_ptr<Track>& track);

public slots:
    /**
     * Emits that position has changed.
     * @param position
     */
    void changePosition(qint64 position);

    /**
     * Handles changes in MediaStatus. If media was loaded, plays it and emits that loading was successful.
     * @param status
     */
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

    /**
     * Emits that the player's state has changed.
     * @param state
     */
    void onMediaStateChanged(QMediaPlayer::State state);

signals:
    /**
     * Signal the position of the loaded media has changed, expressed in milliseconds.
     * @param position
     */
    void posChanged(qint64 position);

    /**
     * Signal that the given track was successfully loaded as media.
     * @param track
     */
    void mediaLoaded(std::shared_ptr<Track>& track);

    /**
     * Signal that the state of the AudioPlayer has changed.
     * @param newState
     */
    void stateChanged(QMediaPlayer::State newState);

private:
    QMediaPlayer* player_;
    std::shared_ptr<Track> currentTrack_;
};


#endif //AUDIOPLAYER_H

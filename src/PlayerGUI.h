#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include <QWidget>
#include "AudioPlayer.h"

class TrackList;

namespace Ui {
class PlayerGUI;
}

class PlayerGUI : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerGUI(QWidget *parent = nullptr);
    ~PlayerGUI() override;
    void openFile();
    void setFolder();
    void toggleTlist();
    void resetFolder();
    void mute();

private slots:
    void play();
    void pause();
    void setVolume(int volume);
    void setSliderPositionFromTrack(qint64 position);
    void setPositionFromSlider(int position);
    void next();
    void previous();

private:
    Ui::PlayerGUI *ui;
    AudioPlayer *audioPlayer;

};

#endif // PLAYERGUI_H

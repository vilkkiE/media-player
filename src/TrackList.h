#ifndef TRACKLIST_H
#define TRACKLIST_H

#include <QListWidget>
#include <memory>
#include "AudioPlayer.h"
#include "Track.h"
#include "TrackListItem.h"

namespace Ui {
class TrackList;
}

class TrackList : public QListWidget
{
    Q_OBJECT

public:
    explicit TrackList(QWidget *parent = nullptr);
    ~TrackList() override;
    void load(const QString&);
    void refresh();
    void prevTrack();
    void nextTrack();

    /**
     * If given a file location with a valid mp3 file, extracts its metadata and creates a Track object.
     * @return
     */
    static std::shared_ptr<Track> createTrack(const QString& location);
    void setPlayer(AudioPlayer* newPlayer) { player = newPlayer; }
    int findTrackIdx(const Track&) const;

private slots:
    void selectTrack(QListWidgetItem*);

private:
    Ui::TrackList *ui;
    AudioPlayer* player;
    QString folder;
    int trackIdx;
};

#endif // TRACKLIST_H

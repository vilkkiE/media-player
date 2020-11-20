#ifndef TRACKLISTITEM_H
#define TRACKLISTITEM_H

#include <QListWidgetItem>
#include "Track.h"

class TrackListItem : public QListWidgetItem {
public:
    TrackListItem(std::shared_ptr<Track>& t, QListWidget* parent);
    ~TrackListItem() override;

    /**
     * Returns the track associated with this object.
     * @return
     */
    const std::shared_ptr<Track>& getTrack() const;

private:
    std::shared_ptr<Track> track;

};

#endif // TRACKLISTITEM_H

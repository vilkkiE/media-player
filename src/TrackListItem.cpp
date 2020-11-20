#include <memory>
#include "TrackListItem.h"

TrackListItem::TrackListItem(std::shared_ptr<Track>& t, QListWidget* parent) : QListWidgetItem(parent), track(t) {
    setText(track->getTitle()+" - "+track->getArtist());
    setToolTip(track->getFileLocation());
}

TrackListItem::~TrackListItem() = default;

const std::shared_ptr<Track>& TrackListItem::getTrack() const {
    return track;
}

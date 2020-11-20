#include "Track.h"

const QString& Track::getTitle() const {
    return title_;
}

const QString& Track::getArtist() const {
    return artist_;
}

const QString& Track::getAlbum() const {
    return album_;
}

int Track::getDuration() const {
    return duration_;
}

const QString& Track::getGenre() const {
    return genre_;
}

const QString& Track::getFileLocation() const {
    return fileLocation_;
}

const QPixmap& Track::getCover() const {
    return cover_;
}

bool Track::operator==(const Track& other) const {
    return getFileLocation() == other.getFileLocation();
}

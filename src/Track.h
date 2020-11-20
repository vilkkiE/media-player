#ifndef TRACK_H
#define TRACK_H
#include <QString>
#include <utility>
#include <QPixmap>

class Track
{
public:
    Track(QString title, QString artist, QString album, int duration, QString genre, QString fileLocation, const QPixmap& cover)
    : title_(std::move(title)), artist_(std::move(artist)), album_(std::move(album)), duration_(duration), genre_(std::move(genre)), fileLocation_(std::move(fileLocation)), cover_(cover) {}

    /**
     * Return the title of the track.
     * @return
     */
    const QString& getTitle() const;

    /**
     * Returns the artist of the track.
     * @return
     */
    const QString& getArtist() const;

    /**
     * Returns the album name of the track.
     * @return
     */
    const QString& getAlbum() const;

    /**
     * Returns the track's duration.
     * @return
     */
    int getDuration() const;

    /**
     * Returns the genre of the track.
     * @return
     */
    const QString& getGenre() const;

    /**
     * Returns the local file location of the track.
     * @return
     */
    const QString& getFileLocation() const;

    /**
     * Returns the track's cover art as a QPixmap.
     * @return
     */
    const QPixmap& getCover() const;

    /**
     * Returns whether a track object is identical to another. Two tracks are identical when they have the same file location.
     * @return
     */
    bool operator==(const Track&) const;

private:
    const QString title_;
    const QString artist_;
    const QString album_;
    int duration_;
    const QString genre_;
    const QString fileLocation_;
    const QPixmap cover_;
};

#endif // TRACK_H

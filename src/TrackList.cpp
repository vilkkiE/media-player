#include "TrackList.h"
#include "ui_TrackList.h"
#include <QDir>
#include <iostream>
#include <taglib/id3v2tag.h>
#include <taglib/mpegfile.h>
#include <taglib/attachedpictureframe.h>
#include <QPixmap>

TrackList::TrackList(QWidget *parent) :
        QListWidget(parent),
        ui(new Ui::TrackList),
        player(nullptr),
        folder("/home"),
	trackIdx(-1)
{
    ui->setupUi(this);
    connect(this, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(selectTrack(QListWidgetItem*)));
}

TrackList::~TrackList()
{
    delete ui;
}

std::shared_ptr<Track> TrackList::createTrack(const QString& location) {
    // Read the file with TagLib
    TagLib::MPEG::File f(location.toUtf8().constData());
    if (f.isValid() && f.audioProperties()) {
        // Get the text metadata
        QString artist = f.tag()->artist().toCString();
        QString title = f.tag()->title().toCString();
        QString album = f.tag()->album().toCString();
        int duration = f.audioProperties()->lengthInSeconds();
        QString genre = f.tag()->genre().toCString();

        // Album art
        QPixmap cover;
        TagLib::ID3v2::Tag *tag = f.ID3v2Tag();
        static const char *idPicture = "APIC";
        TagLib::ID3v2::FrameList frames;
        TagLib::ID3v2::AttachedPictureFrame *picFrame;
        QByteArray frontCover, otherCover;

        if (tag) {
            // Picture frame
            frames = tag->frameListMap()[idPicture];

            if (!frames.isEmpty()) {
                // Loop through all the frames
                for (auto frame : frames) {
                    picFrame = (TagLib::ID3v2::AttachedPictureFrame *) frame;
                    if (picFrame->type() == TagLib::ID3v2::AttachedPictureFrame::FrontCover) {
                        frontCover = QByteArray(picFrame->picture().data(), picFrame->picture().size());
                        // Not necessary to complete the for loop when FrontCover was already extracted
                        break;
                    } else {
                        otherCover = QByteArray(picFrame->picture().data(), picFrame->picture().size());
                    }
                }
            }

            if (!frontCover.isEmpty()) {
                // Use front cover when possible (instead of other covers)
                cover = QPixmap::fromImage(QImage::fromData(frontCover));
            } else if (!otherCover.isEmpty()) {
                cover = QPixmap::fromImage(QImage::fromData(otherCover));
            }
        }

        // Create Track
        return std::make_shared<Track>(title, artist, album, duration, genre, location, cover);
    } else {
        qDebug() << location << " is not a valid audio file.";
        return nullptr;
    }
}

void TrackList::load(const QString& directory) {
    QDir dir(directory);
    QStringList files = dir.entryList(QStringList() << "*.mp3", QDir::Files);
    for (const QString& file : files) {
        std::shared_ptr<Track> t = createTrack(directory+"/"+file);
        new TrackListItem(t, this);
    }
    folder = directory;
}

void TrackList::prevTrack() {
    if (count() < 1) return; // no tracks
    int newIdx = trackIdx > 0 ? trackIdx-1 : count()-1;
    trackIdx = newIdx;
    setCurrentRow(newIdx);
    auto* i = dynamic_cast<TrackListItem*>(item(newIdx));
    player->openTrack(i->getTrack());
}

void TrackList::nextTrack() {
    if (count() < 1) return; // no tracks
    int newIdx = trackIdx < count()-1 ? trackIdx+1 : 0;
    trackIdx = newIdx;
    setCurrentRow(newIdx);
    auto* i = dynamic_cast<TrackListItem*>(item(newIdx));
    player->openTrack(i->getTrack());
}

int TrackList::findTrackIdx(const Track& t) const {
    for (int i = 0; i < count(); ++i) {
        auto* it = dynamic_cast<TrackListItem*>(item(i));
	Track t2 = *(it->getTrack());
        if (t == t2) return i;
    }
    return -1;
}

void TrackList::refresh() {
    this->clear();
    load(folder);
}

void TrackList::selectTrack(QListWidgetItem* item) {
    auto* i = dynamic_cast<TrackListItem*>(item);
    Track t = *(i->getTrack());
    trackIdx = findTrackIdx(t);
    player->openTrack(i->getTrack());
}

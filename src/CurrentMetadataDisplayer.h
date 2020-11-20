#ifndef CURRENTMETADATADISPLAYER_H
#define CURRENTMETADATADISPLAYER_H

#include <memory>
#include <QWidget>
#include "Track.h"


namespace Ui {
class CurrentMetadataDisplayer;
}

class CurrentMetadataDisplayer : public QWidget
{
    Q_OBJECT

public:
    explicit CurrentMetadataDisplayer(QWidget *parent = nullptr);
    ~CurrentMetadataDisplayer() override;

public slots:
    /**
     * Update the metadata info when a new track is loaded. Connects to AudioPlayer elsewhere.
     * @param track
     */
    void onMediaLoaded(std::shared_ptr<Track>& track);

private:
    Ui::CurrentMetadataDisplayer *ui;
};

#endif // CURRENTMETADATADISPLAYER_H

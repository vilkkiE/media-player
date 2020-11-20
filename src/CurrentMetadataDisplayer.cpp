#include "CurrentMetadataDisplayer.h"
#include "ui_CurrentMetadataDisplayer.h"
#include <QPixmap>
#include <QDir>

CurrentMetadataDisplayer::CurrentMetadataDisplayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurrentMetadataDisplayer)
{
    ui->setupUi(this);

    // Clear possible placeholder texts
    ui->titleLabel->setText("");
    ui->artistLabel->setText("");
}

CurrentMetadataDisplayer::~CurrentMetadataDisplayer()
{
    delete ui;
}

void CurrentMetadataDisplayer::onMediaLoaded(std::shared_ptr<Track> &track)
{
    // Show song artist and title
    ui->titleLabel->setText(track->getTitle());
    ui->artistLabel->setText(track->getArtist());

    // Cover image
    if (!track->getCover().isNull()) {
        // If track has a cover, use it
        ui->coverImage->setPixmap(track->getCover());
    } else {
        // Otherwise, use the template no-cover image
        ui->coverImage->setPixmap(QPixmap("../no-cover.png"));
    }
}

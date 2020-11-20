#ifndef MEDIAPLAYER_CUSTOMSLIDER_H
#define MEDIAPLAYER_CUSTOMSLIDER_H

#include <QSlider>
#include <QMouseEvent>

class CustomSlider: public QSlider {

    using QSlider::QSlider;

protected:
    /**
     * Extend the parent's method by updating the slider's position/value when clicking on it.
     * @param event
     */
    void mousePressEvent(QMouseEvent* event) override;
};


#endif //MEDIAPLAYER_CUSTOMSLIDER_H

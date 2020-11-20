#include "CustomSlider.h"

void CustomSlider::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        // Calculate the appropriate position for the slider based on where the user clicked
        setValue(minimum() + ((maximum()-minimum()) * event->x()) / width());
        event->accept();
    }

    // Call the parent's implementation
    QSlider::mousePressEvent(event);
}

#include "clickablelabel.h"
#include <QMouseEvent>



ClickableLabel::ClickableLabel(QWidget* parent)
    : QLabel(parent) {}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        // Emit the clicked signal with the x and y coordinates
        emit clicked(event->position().x(), event->position().y());
    }
    QLabel::mousePressEvent(event); // Call the base class implementation
}

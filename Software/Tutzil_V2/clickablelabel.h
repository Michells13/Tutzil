#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <Qt>

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = nullptr);
    ~ClickableLabel();

signals:
    void clicked(int x, int y);

protected:
    void mousePressEvent(QMouseEvent* event) override;
};

#endif // CLICKABLELABEL_H

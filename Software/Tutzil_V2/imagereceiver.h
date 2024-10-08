#ifndef IMAGERECEIVER_H
#define IMAGERECEIVER_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include <QImage>

class ImageReceiver : public QObject {
    Q_OBJECT

public:
    explicit ImageReceiver(QTcpSocket *socket, QObject *parent = nullptr);

signals:
    void imageReady(const QImage &image);

private slots:
    void readData();

private:
    QTcpSocket *socket;
    qint32 dataLength;
    QByteArray imageData;
};

#endif // IMAGERECEIVER_H

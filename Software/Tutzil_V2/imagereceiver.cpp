#include "ImageReceiver.h"
#include <QDataStream>
#include <QDebug>

ImageReceiver::ImageReceiver(QTcpSocket *socket, QObject *parent)
    : QObject(parent), socket(socket), dataLength(0) {
    // Conectar la señal readyRead del socket al slot readData
    connect(socket, &QTcpSocket::readyRead, this, &ImageReceiver::readData);
}

void ImageReceiver::readData() {
    // Si la longitud de los datos aún no se ha leído
    if (dataLength == 0) {
        // Comprobar si hay suficientes bytes para leer la longitud
        if (socket->bytesAvailable() < 4) {
            return;  // Esperar más datos
        }

        // Leer los primeros 4 bytes para obtener la longitud de los datos
        QByteArray lengthBuffer = socket->read(4);
        QDataStream dsLength(lengthBuffer);
        dsLength.setByteOrder(QDataStream::BigEndian);
        dsLength >> dataLength;
    }

    // Leer los datos de la imagen en fragmentos
    imageData.append(socket->read(dataLength - imageData.size()));

    // Verificar si hemos recibido todos los datos
    if (imageData.size() == dataLength) {
        // Decodificar la imagen
        QImage image;
        if (!image.loadFromData(imageData)) {
            qWarning() << "Error: No se pudo decodificar la imagen.";
            return;
        }

        // Emitir la señal con la imagen decodificada
        emit imageReady(image);

        // Resetear para la siguiente imagen
        dataLength = 0;
        imageData.clear();
    }
}

//Macros
#define Timex   //activates the timer to measuring some functions
//#define Dbug
//#define cnt       //counter of iterations.



// worker.cpp
#include "worker.h"
#include <QThread>
#include <QDebug>
#include <QMutex>
#include <QWaitCondition>
#include <atomic>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <imagereceiver.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QElapsedTimer>


// QElapsedTimer timer;
// timer.start();
// qint64 elapsedTime = timer.elapsed();
// // Print the elapsed time
// qDebug() << "Time taken:" << elapsedTime << "milliseconds";


Worker::Worker(QObject *parent) : QObject(parent), socket(nullptr), pythonProcess(nullptr), comms(false),m_stop(false) {}

Worker::~Worker() {
    if (socket) {
        socket->close();
        delete socket;
    }
    if (pythonProcess) {
        pythonProcess->close();
        delete pythonProcess;
    }
}

void Worker::doWork() {
    int i=0;  //Contador
    const qint32 MAX_PACKET_SIZE = 20 * 1024 * 1024; // 5 MB
    const qint32 MAX_PACKET_SIZE2 = (500 * 1024)/2; // 5 MB
    // Imágenes Pequeñas (baja resolución): 100 KB - 500 KB (MAX_PACKET_SIZE = 500 * 1024).
    // Imágenes Medias (resolución media): 1 MB - 5 MB (MAX_PACKET_SIZE = 5 * 1024 * 1024).
    // Imágenes Grandes (alta resolución): 10 MB - 20 MB (MAX_PACKET_SIZE = 20 * 1024 * 1024).
    bool packet_Ok=false;
    pythonProcess = new QProcess();
    connect(pythonProcess, &QProcess::readyReadStandardOutput, this, &Worker::handleProcessOutput);
    connect(pythonProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(handleProcessFinished(int, QProcess::ExitStatus)));

    QString virtualenvPath = "C:/Users/MICHE/anaconda3/envs/pyT/python.exe";
    QString scriptPath = "C:/Users/MICHE/Desktop/Github/Tutzil_V2/Vision/YV8_detect_v6_.py";


    pythonProcess->start(virtualenvPath, QStringList() << scriptPath);
    pythonProcess->waitForStarted(3000);

    emit updateTextBrowser("Starting vision module... \n");
    socket = new QTcpSocket();
    socket->connectToHost("localhost", 9999);

    if (socket->waitForConnected()) {
        if (socket->state() != QAbstractSocket::ConnectedState) {
            qWarning() << "El socket no está conectado.";
            emit finished();
        }
        socket->write("0000");
        socket->waitForBytesWritten();

        if (socket->waitForReadyRead()) {
            QByteArray response = socket->readAll();
            if (response == "0000") {
                emit updateTextBrowser("Code from server: " + response + "\nComms Ok \n");
                if (socket->state() != QAbstractSocket::ConnectedState) {
                    qWarning() << "El socket no está conectado.";
                    emit finished();
                }
                socket->write("0010");
                socket->waitForBytesWritten();

                if (socket->waitForReadyRead()) {
                    QByteArray response2 = socket->readAll();
                    if (response2 == "0010") {
                        emit updateTextBrowser("Code from server: " + response2 + "\nStarting streaming \n");


                        while(true){
                            if (readFileAndCheck("C:/Users/MICHE/Desktop/Github/Tutzil_V2/Vision/state.txt")) {
                                socket->write("0001");
                                socket->waitForBytesWritten();
                                emit finished();
                                break;
                            }
                            else{
                                if (socket->state() != QAbstractSocket::ConnectedState) {
                                    qWarning() << "El socket no está conectado.";
                                    emit finished();
                                }
                                socket->write("0100"); //Ask for a package
                                socket->waitForBytesWritten();



                                packet_Ok=false;// flag to check if packet has been recieved correclty



 //Implement here a function to recieve image and data
                                // Check if there are enough daa to read the size of the package (4 bytes)


#ifdef Timex
                                QElapsedTimer timer;
                                timer.start();
#endif


                                packet_Ok = checkPacketSize(socket, sizeof(qint32),8000);

                                // Leer el tamaño del paquete (4 bytes)
                                qint32 packetSize;
                                QDataStream in(socket);
                                in.setByteOrder(QDataStream::BigEndian);
                                in >> packetSize;

                                if (packetSize <= 0 || packetSize > MAX_PACKET_SIZE) {
                                    qWarning() << "Tamaño de paquete inválido:" << packetSize;
                                    packet_Ok=false;
                                }
                                else{
                                    packet_Ok=true;
                                }
#ifdef Dbug
                                qDebug() << "Tamaño del paquete recibido:" << packetSize;
#endif

                                // Esperar a que todos los datos estén disponibles
                                while (socket->bytesAvailable() < packetSize) {
                                    socket->waitForReadyRead(8000);
                                    if (socket->error() != QAbstractSocket::SocketError::UnknownSocketError) {
                                        qWarning() << "Error en el socket:" << socket->errorString();
                                        packet_Ok=false;
                                    }
                                    else{
                                        packet_Ok=true;
                                    }
                                }

                                // Leer los datos de la imagen
                                QByteArray imageData = socket->read(packetSize);
#ifdef Dbug
                                qDebug() << "Datos de la imagen recibidos:" << imageData.size();
#endif
                                // Decodificar la imagen
                                QImage image;
                                if (!image.loadFromData(imageData, "JPEG")) {
                                    qWarning() << "Error al cargar la imagen desde los datos.";
                                    packet_Ok=false;
                                }
                                else
                                {
                                    packet_Ok=true;
                                }


                                if (packet_Ok){
 //update green indicator (pending)
                                   // emit updateFrame(image); //if packet isn't ok, update frame wont update it and will turn the indicator red


                                }
                                else
                                {
                                    //update red indicator in  UI to show it isn't updating
                                    qWarning() << "packet not Ok";
                                }
#ifdef Timex
                                qint64 elapsedTime = timer.elapsed();
                                // Print the elapsed time
                                qDebug() << "Time to udpateFrame:" << elapsedTime << "milliseconds";
#endif
  //Json reading
#ifdef Timex
                                QElapsedTimer timer2;
                                timer2.start();
#endif

                                packet_Ok = checkPacketSize(socket, sizeof(qint32),10);

                                // Leer el tamaño del paquete de JSON (4 bytes)
                                in >> packetSize;

                                if (packetSize <= 0 || packetSize > MAX_PACKET_SIZE2) {
 #ifdef Dbug
                                    qWarning() << "Tamaño de paquete inválido para JSON:" << packetSize;
#endif
                                }

                                // Esperar a que todos los datos de JSON estén disponibles
                                if (!socket->waitForReadyRead(10) || socket->bytesAvailable() < packetSize) {
 #ifdef Dbug
                                    qWarning() << "No se recibieron suficientes datos para el JSON.";
#endif
                                }

                                // Leer los datos JSON
                                QByteArray jsonData = socket->read(packetSize);
  #ifdef Dbug
                                qDebug() << "Datos JSON recibidos:" << jsonData.size();
#endif
                                // Procesar el JSON
                                QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
                                if (!jsonDoc.isArray()) {
#ifdef Dbug
                                    qWarning() << "Error: El JSON recibido no es un array.";
#endif
                                }

                                QJsonArray allDataArray = jsonDoc.array();
#ifdef Timex
                                qint64 elapsedTime2 = timer2.elapsed();
                                // Print the elapsed time
                                qDebug() << "Time JsonRead taken:" << elapsedTime2 << "milliseconds";
#endif

                                emit updateFrame(image,allDataArray);// Frame capsules image and data, it is posible split it, check pros and cons.
                                // emit updateData(allDataArray);    // Split functions done.
                                // emit updateFrame(image);
                            }

#ifdef cnt
                            if (i%100==0){
                                QString str = QString::number(i);
                                QString str1 = QString::number(comms);

                                emit updateTextBrowser("Reading image"+str+" \n");
                                emit updateTextBrowser("Bool state"+str1+" \n");

                            }

                            i=i+1;
#endif

                            QThread::msleep(10);  // Add a short sleep to avoid tight looping


                        }
                        if (socket->state() != QAbstractSocket::ConnectedState) {
                            qWarning() << "El socket no está conectado.";
                            emit finished();
                        }
                        socket->write("0001");
                        socket->waitForBytesWritten();
                        emit updateTextBrowser("Closing comms \n");




                    } else {
                        emit updateTextBrowser("Sequence broken, responce expected: 0010 \n");
                        emit updateTextBrowser("Responce from server was: "+ response + "\n");



                    }
                } else {
                    emit updateTextBrowser("No response for 0010 \n");
                }
            } else {
                emit updateTextBrowser("Unexpected response for 0000: " + response + "\n");
            }
        } else {
            emit updateTextBrowser("No response for 0000 \n");
        }
    } else {
        emit updateTextBrowser("Failed to connect to server.... \n");
    }

    emit finished();
}




bool Worker::readFileAndCheck(const QString &filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString content = in.readAll().trimmed();
        file.close();
        return content == "False";
    } else {
        return false;
    }
}
void Worker::handleProcessOutput()
{

}

void Worker::handleProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{

}
void Worker::stopComms() {
    QMutexLocker locker(&m_mutex);
    m_stop = true;
}

bool Worker::checkPacketSize(QTcpSocket *socket, qint32 expectedSize, int timeout)
{
    // Verifica si los bytes disponibles son menores que el tamaño esperado
    if (socket->bytesAvailable() < expectedSize) {
        // Espera a que lleguen más datos con un timeout especificado
        socket->waitForReadyRead(timeout);

        // Vuelve a verificar si se han recibido suficientes datos
        if (socket->bytesAvailable() < expectedSize) {
            qWarning() << "Din't get enought data to get the packet size.";
            return false;
        }
        else
        {
            return true;
        }
    }
}

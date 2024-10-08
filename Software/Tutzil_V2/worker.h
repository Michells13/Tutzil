// worker.h
#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QTcpSocket>
#include <QProcess>
#include <QMutex>
#include <QMutexLocker>
#include <QWaitCondition>
#include <atomic>

class Worker : public QObject {
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
    ~Worker();

signals:
    void updateTextBrowser(const QString &text);
    void updateFrame(const QImage &frame, const QJsonArray &allDataArray); //Updates frames from worker thread to mainWindow thread
    void updateData(const QJsonArray &allDataArray);//Updates data from worker thread to mainWindow thread (Boundind boex, classes and Ids)
    //void updateMask()   //Pending until we deside how to handle the data transmition (Another thread maybe)
    void finished();

public slots:
    void doWork();
    void stopComms();
    bool checkPacketSize(QTcpSocket* socket, qint32 expectedSize, int timeout);



private slots:
    void handleProcessOutput();
    void handleProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);



private:
    QTcpSocket *socket;
    QProcess *pythonProcess;
    bool comms;
    std::atomic<bool> m_stop;  // Use atomic for thread-safe boolean flag m_stop;
    QMutex m_mutex;
    QWaitCondition condition;
    bool readFileAndCheck(const QString &filePath);
    void processImage(QImage );
};

#endif // WORKER_H

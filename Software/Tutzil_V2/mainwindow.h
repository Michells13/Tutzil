#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QProcess>
#include <worker.h>
#include <opencv2/core/core.hpp>
#include "clickablelabel.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

private slots:
    void on_pushButton_clicked();//Start/Run
    void on_pushButton_2_clicked();//Stop
    void handleUpdateTextBrowser(const QString &text);
    void handleUpdateFrame(const QImage &frame, const QJsonArray &allDataArray);  //Handles the frames to be updated,
     // it also contains the drawing and
     // selecting object function.

    void handleUpdateSelectedObject(const QImage &roi,const QJsonArray &mask, const QJsonArray &PE); //Will control the frames to be updated
     // in the selected object funcion.


    void handleUpdateData(const QJsonArray &allDataArray);
    void handleWorkerFinished();
    void onLabelClicked(int x, int y);
    void smallestDistance(QVector<QPoint> objectsCentroids, QPoint click);






    void on_pushButton_3_clicked();

signals:
    void normalStop(); // Signal to change state





private:
    Ui::MainWindow *ui;


    //Comms, processes and threads
    bool processActive; // Variable to control the process
    bool EmergencyStop;  // Add this line to declare EmergencyStop
    bool comms_UI;
    QProcess *m_process; // Declaración de m_process como variable miembro
    QTcpSocket *tcpSocket; // Socket for communication
    QThread *workerThread;
    Worker *worker;
    QMutex mmutex;
    void writeToFile(const QString &filePath, const QString &text);



    //Object Selection
    QPoint selectedObject;       //Selected object
    bool activateSelector;      // Flag to control the object selection function
    bool activateSelector2;      // Flag to control the object selection function 2nd part
    int  selectedId;














};
#endif // MAINWINDOW_H

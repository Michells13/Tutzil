// mainwindow.cpp
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "worker.h" // Add this line to include the Worker class
#include <QThread>  // Include the QThread class
#include <QDebug>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPainter>
#include <QVector>
#include <QLineF>
#include <algorithm>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_process(nullptr)
    , tcpSocket(nullptr)
    , workerThread(nullptr)
    , worker(nullptr)
    , EmergencyStop(false)  // Initialize EmergencyStop
    , comms_UI(false)
    , selectedObject(0,0)       //Coordinates of the selected object, if (0,0) no object has been selected
    , activateSelector(true)    //Object selector control variable
    , activateSelector2(false)   //Object selector contrl variable 2nd part
    , selectedId(99)

{


    ui->setupUi(this);
    // Step 1: Load the image  a JPG file

    ui->XYScreen->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->XYScreen->setScaledContents(true); // Esto asegura que el contenido del QLabel se escale para llenar el widget
    QString imagePath = "C:/Users/MICHE/Desktop/Github/Tutzil_V2/Tutzil_V2/xy.jpg";

    QImage frame(imagePath);
    if (frame.isNull()) {
        qDebug() << "Failed to load image:" << imagePath;
    } else {
        QPixmap pixmap = QPixmap::fromImage(frame);
        // Aquí ya no necesitas escalar manualmente la imagen
        ui->XYScreen->setPixmap(pixmap);}
    //Make labels clicables
    connect(ui->hud_body, &ClickableLabel::clicked, this, &MainWindow::onLabelClicked);
    connect(ui->imagelabel, &ClickableLabel::clicked, this, &MainWindow::onLabelClicked);
    connect(ui->XYScreen, &ClickableLabel::clicked, this, &MainWindow::onLabelClicked);




}

MainWindow::~MainWindow() {
    delete ui;
    if (workerThread) {
        workerThread->quit();
        workerThread->wait();
        delete workerThread;
    }
    if (m_process) {
        m_process->close();
        delete m_process;
        m_process = nullptr;
    }
}

void MainWindow::on_pushButton_clicked() {

    ui->textBrowser->insertPlainText("Starting Thread... \n");


    //If threaht has not been initialized then create it and launch it
    if (!workerThread){
        QString filePath = "C:/Users/MICHE/Desktop/Github/Tutzil_V2/Vision/state.txt"; // Ruta del archivo
        writeToFile(filePath, "True");

        Worker *worker = new Worker();// in the future if multiple cameras are connected we only have to increase the number of workers
        workerThread = new QThread();
        worker->moveToThread(workerThread);

        connect(workerThread, &QThread::started, worker, &Worker::doWork);
        connect(worker, &Worker::updateTextBrowser, this, &MainWindow::handleUpdateTextBrowser);
        connect(worker, &Worker::updateFrame,this,&MainWindow::handleUpdateFrame);
        connect(worker, &Worker::updateData,this, &MainWindow::handleUpdateData);
        connect(worker, &Worker::finished, this, &MainWindow::handleWorkerFinished);
        connect(worker, &Worker::finished, workerThread, &QThread::quit);
        connect(worker, &Worker::finished, worker, &Worker::deleteLater);
        connect(workerThread, &QThread::finished, workerThread, &QThread::deleteLater);
        workerThread->start();
    }
    else{


    }


}

void MainWindow::on_pushButton_2_clicked() {
    if (worker) {
        QMetaObject::invokeMethod(worker, "stop", Qt::QueuedConnection);
        worker->finished();
    }
    if (m_process) {
        m_process->close();
        delete m_process;
        m_process = nullptr;
    }

    // writeToFile
    QString filePath = "C:/Users/MICHE/Desktop/Github/Tutzil_V2/Vision/state.txt"; // Ruta del archivo
    writeToFile(filePath, "False");

    QMessageBox::information(this, "Thread", "Vision thread stopped.");

    ui->textBrowser->insertPlainText("_____________________________ \n");
    ui->textBrowser->insertPlainText("Vision module ended.... \n");
    ui->textBrowser->insertPlainText("Communication thread killed.... \n");





}




void MainWindow::handleUpdateTextBrowser(const QString &text) {
    ui->textBrowser->insertPlainText(text);
}

void MainWindow::handleUpdateFrame(const QImage &frame, const QJsonArray &allDataArray){
    // Get QLabel size
    QSize labelSize = ui->imagelabel->size();

    // Resize image to fit QLabel
    QPixmap pixmap = QPixmap::fromImage(frame).scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    // Create a QPainter to draw over QPixmap
    QPainter painter(&pixmap);
    QVector<QPoint> ObjectsCentroids;
    QVector<float>  distances;
    int minIndex = 0;  // Para almacenar la posición del valor más pequeño

    // Recorrer cada objeto JSON y extraer la información de las bounding boxes
    for (const QJsonValue& value : allDataArray) {
        QJsonObject dataVector = value.toObject();
        QJsonArray normalizedBoxes = dataVector["normalized_boxes"].toArray();
        QJsonArray trackIds = dataVector["track_ids"].toArray();
        QJsonArray classIds = dataVector["class_ids"].toArray();


        //Loop para extraer los centroides y realizar el ObjectSelection posteriormente en el drawing
        if(selectedObject.x()!=0 && selectedObject.y()!=0 && activateSelector){
            activateSelector=false; //Deactivate Selector since we have clicked a point
            activateSelector2=true;
            qDebug() << "Click";
            qDebug() << "Objects to analize"<< normalizedBoxes.size();
            int index=0;
            for(int i=0; i<normalizedBoxes.size(); i++){

             QJsonArray box = normalizedBoxes[i].toArray();

             // Extraer las coordenadas normalizadas (xmin, ymin, xmax, ymax)
             float xmin = box[0].toDouble();
             float ymin = box[1].toDouble();
             float xmax = box[2].toDouble();
             float ymax = box[3].toDouble();

             // Convertir coordenadas normalizadas a coordenadas de píxeles
             int x = static_cast<int>(xmin * pixmap.width());
             int y = static_cast<int>(ymin * pixmap.height());
             int width = static_cast<int>((xmax - xmin) * pixmap.width());
             int height = static_cast<int>((ymax - ymin) * pixmap.height());
             QPoint Centroid(((x+(x+width))/2),((y+(y+height))/2));
             qDebug() << "Objeto"<< i<< "Centroide" <<Centroid;
             ObjectsCentroids.append(Centroid);
             QLineF line(ObjectsCentroids[i], selectedObject);
             qDebug() <<"Distance: "<< line.length();
             distances.append(line.length());
             if(distances[i]< distances[minIndex]){

                 minIndex=i;

             }


         }

             qDebug() << "Index : (" << minIndex<<")" ;
             qDebug()       <<"ID: "<< trackIds[minIndex].toInteger();
             selectedId=trackIds[minIndex].toInteger();



        }
        else{

            // Dibujar cada bounding box en la imagen
            for (int i = 0; i < normalizedBoxes.size(); ++i) {
                QJsonArray box = normalizedBoxes[i].toArray();

                // Extraer las coordenadas normalizadas (xmin, ymin, xmax, ymax)
                float xmin = box[0].toDouble();
                float ymin = box[1].toDouble();
                float xmax = box[2].toDouble();
                float ymax = box[3].toDouble();

                // Convertir coordenadas normalizadas a coordenadas de píxeles
                int x = static_cast<int>(xmin * pixmap.width());
                int y = static_cast<int>(ymin * pixmap.height());
                int width = static_cast<int>((xmax - xmin) * pixmap.width());
                int height = static_cast<int>((ymax - ymin) * pixmap.height());
                // el id coincida
                if (activateSelector2 && selectedId!=99 && trackIds[i].toInteger()==selectedId ){

                    painter.setPen(QPen(Qt::green, 2)); // Configurar el color y grosor del borde
                    // Dibujar el rectángulo (bounding box)
                    painter.drawRect(x, y, width, height);
                    // Dibujar el Track ID y el Class ID
                    QString label = QString("ID: %1, Class: %2")
                                        .arg(trackIds[i].toInt())
                                        .arg(classIds[i].toInt());
                    painter.drawText(x, y - 5, label); // Dibujar el texto encima del bounding box


                }
                else{

                    painter.setPen(QPen(Qt::red, 2)); // Configurar el color y grosor del borde
                    // Dibujar el rectángulo (bounding box)
                    painter.drawRect(x, y, width, height);
                    // Dibujar el Track ID y el Class ID
                    QString label = QString("ID: %1, Class: %2")
                                        .arg(trackIds[i].toInt())
                                        .arg(classIds[i].toInt());
                    painter.drawText(x, y - 5, label); // Dibujar el texto encima del bounding box

                }




            }




        }



    }


        // Mostrar la imagen redimensionada en el QLabel
        ui->imagelabel->setPixmap(pixmap);




}

void MainWindow::handleUpdateSelectedObject(const QImage &roi, const QJsonArray &mask, const QJsonArray &PE)
{

}

void MainWindow::handleUpdateData(const QJsonArray &allDataArray)
{
    for (const QJsonValue& value : allDataArray) {
        QJsonObject dataVector = value.toObject();
        int length = dataVector["len"].toInt();
        QJsonArray trackIds = dataVector["track_ids"].toArray();
        QJsonArray classIds = dataVector["class_ids"].toArray();
        QJsonArray normalizedBoxes = dataVector["normalized_boxes"].toArray();

        qDebug() << "Length:" << length;
        qDebug() << "Track IDs:" << trackIds;
        qDebug() << "Class IDs:" << classIds;
        qDebug() << "Normalized Boxes:" << normalizedBoxes;
    }

}

void MainWindow::handleWorkerFinished() {
    ui->textBrowser->insertPlainText("Worker finished its task.\n");
    workerThread = nullptr;
}

void MainWindow::onLabelClicked(int x, int y)
{
    qDebug() << "Label clicked at: (" << x << ", " << y << ")";
    selectedObject.setX(x);
    selectedObject.setY(y);

}



void MainWindow::smallestDistance(QVector<QPoint> objectsCentroids, QPoint click)
{
    QVector <double>  distances;
    int minIndex = 0;
    for(int i=0; i < objectsCentroids.size(), i++;){
        QLineF line(objectsCentroids[i], click);
        distances.append(line.length());
        qDebug() << "Element: " << i<< " Distance: "<< line.length();



    }

}



void MainWindow::writeToFile(const QString &filePath, const QString &text) {
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << text;
        file.close();
    } else {
        QMessageBox::critical(this, "Error", "No se pudo abrir el archivo para escritura.");
    }
}




void MainWindow::on_pushButton_3_clicked()
{
    selectedObject.setX(0);
    selectedObject.setY(0);
    activateSelector=true;
    activateSelector2=false;
    selectedId=99;
    qDebug()<<"Object selector reactivated, object cleared ";

}


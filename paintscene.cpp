#include "paintscene.h"
#include <QSerialPort>
#include <QErrorMessage>

QSerialPort *serial;

void paintScene::openSerialPort()
{

    //if (!serial->isOpen())
    //{
        serial = new QSerialPort();
        //COM9 COM11 den okuyor
        serial->setPortName("COM9");
        serial->setBaudRate(QSerialPort::Baud115200);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        //serial->open(QIODevice::WriteOnly);
        serial->open(QIODevice::ReadWrite);
    //}

    //if(!serial->open(QIODevice::ReadWrite))
    //{
    //    qDebug() << (tr("error %1").arg(serial->error()));
    //    return;
    //}


}



void paintScene::closeSerialPort()
{
    serial->close();
}

paintScene::paintScene(QObject *parent) : QGraphicsScene(parent)
{
    openSerialPort();
}

paintScene::~paintScene()
{

}

void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // When you press the mouse button, draw the ellipse
    addEllipse(event->scenePos().x(),
               event->scenePos().y(),
               0,
               0,
               QPen(Qt::NoPen),
               QBrush(Qt::red));
    // Save the coordinates of the point of pressing
    previousPoint = event->scenePos();
}

void paintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // We draw the line with the previous coordinates
    addLine(previousPoint.x(),
            previousPoint.y(),
            event->scenePos().x(),
            event->scenePos().y(),
            QPen(Qt::red,10,Qt::SolidLine,Qt::RoundCap));

     int coordx = event->scenePos().x();
     int coordy = event->screenPos().y();
     qDebug() << coordx << coordy;

     //openSerialPort();

     QString coordx_s = QString::number(coordx);

     QByteArray str;
     QTextStream(&str) <<   coordx << "," << coordy;
     serial->write(str);

//     serial->waitForBytesWritten(70);
 //    serial->waitForReadyRead(70);

     //closeSerialPort();

    // Update on the previous coordinate data
    previousPoint = event->scenePos();
}

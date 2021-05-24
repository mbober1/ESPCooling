#ifndef SERIAL_H
#define SERIAL_H

#include <QtCore/QObject>
#include <QSerialPort>
#include <QDebug>
#include <QObject>

QT_BEGIN_NAMESPACE
class QSerialPort;
QT_END_NAMESPACE



/*!
*   \file 
*   \brief The file contains the serial class.
*/

/**
    @brief Serial class
*/
class Serial : public QObject
{
    Q_OBJECT

public:
    explicit Serial(QWidget *parent = nullptr);
    ~Serial();
    bool connect(const QString &name);
    void disconnect();
    QSerialPort *device;
    void readFromPort();
    

private slots:

private:
    void sendMessageToDevice(QString message);
};

#endif // SERIAL_H
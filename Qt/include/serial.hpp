#ifndef SERIAL_H
#define SERIAL_H

#include <QtCore/QObject>
#include <QSerialPort>
#include <QObject>
#include <QtSerialPort>
#include <QTextList>
#include "types.h"

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
    explicit Serial();
    ~Serial();
    bool connect(const QString &name);
    void disconnect();
    QSerialPort *device;
    void readFromPort();
    QList<QSerialPortInfo> getDevices();
    QString findKnownDevice(QList<QSerialPortInfo> devices);

public slots:
    void setCpuFanSpeed(int percentage);
    void setGpuFanSpeed(int percentage);

signals:
    void new_fan_status(Status_t status);

private:
    void sendMessageToDevice();
    Manual_mess_t manual_mess;
};

#endif // SERIAL_H

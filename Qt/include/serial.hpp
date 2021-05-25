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

public slots:
    void setCpuFanSpeed(int percentage);
    // void setGpuFanSpeed(int percentage);

signals:
    void cpuSpeedChanged(int speed);
    void gpuSpeedChanged(int speed);
    void cpuPercentageChanged(int speed);
    void gpuPercentageChanged(int speed);

private:
    void sendMessageToDevice(QString message);
};

#endif // SERIAL_H
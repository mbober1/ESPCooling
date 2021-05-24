#ifndef SERIAL_H
#define SERIAL_H

#include <QtCore/QObject>
#include <QSerialPort>
#include <QDebug>

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
class Serial
{
public:
    explicit Serial();
    ~Serial();
    bool connect(const QString &name);
    void disconnect();

private:
    QSerialPort *device;
};

#endif // SERIAL_H
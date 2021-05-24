#include "serial.hpp"


/**
 * A constructor.
 */
Serial::Serial()
{
    this->device = new QSerialPort();

    // auto gamepads = QGamepadManager::instance()->connectedGamepads();
    // if (gamepads.isEmpty()) {
    //     qDebug() << "Did not find any connected gamepads";
    //     return;
    // }

    // m_gamepad = new QGamepad(*gamepads.begin(), this);
}


/**
 * A destructor.
 */
Serial::~Serial()
{ 
    delete this->device;
}


void Serial::connect(const QString &name) {
    this->device->setPortName(name);

    if(this->device->open(QSerialPort::ReadWrite)) {
        this->device->setBaudRate(QSerialPort::Baud115200);
        this->device->setDataBits(QSerialPort::Data8);
        this->device->setParity(QSerialPort::NoParity);
        this->device->setStopBits(QSerialPort::OneStop);
        this->device->setFlowControl(QSerialPort::NoFlowControl);

        qDebug() << "port opening succes";
    } else qDebug() << "port opening error";
}
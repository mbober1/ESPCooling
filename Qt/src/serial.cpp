#include "serial.hpp"


/**
 * A constructor.
 */
Serial::Serial(QWidget *parent)
{
    this->device = new QSerialPort();
    // QMetaObject::connect(this->device, SIGNAL(readyRead()), this, SLOT(readFromPort()));
}


/**
 * A destructor.
 */
Serial::~Serial()
{ 
    delete this->device;
}


bool Serial::connect(const QString &name) {
    this->device->setPortName(name);

    if(this->device->open(QSerialPort::ReadWrite)) {
        this->device->setBaudRate(QSerialPort::Baud115200);
        this->device->setDataBits(QSerialPort::Data8);
        this->device->setParity(QSerialPort::NoParity);
        this->device->setStopBits(QSerialPort::OneStop);
        this->device->setFlowControl(QSerialPort::NoFlowControl);

        QObject::connect(this->device, &QSerialPort::readyRead, this, &Serial::readFromPort);

        return true;

    } else qDebug() << "port opening error";
    return false;
}


void Serial::disconnect() {
    this->device->close();
}


void Serial::readFromPort() {
    // qDebug() << this->device->readAll();
    static std::string buffer;

    buffer.append(this->device->readAll().toStdString());

    int separator = buffer.find("\r\n");

    while(separator != std::string::npos) {
        std::string data = buffer.substr(0, separator + 1);
        buffer.erase(0, separator+2);
        separator = buffer.find("\r\n");
        qDebug() << data.c_str();
    }
    

}


void Serial::sendMessageToDevice(QString message) {
    if(this->device->isOpen() && this->device->isWritable()) {
        this->device->write(message.toStdString().c_str());
    }
}

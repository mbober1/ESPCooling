#include "include/serial.hpp"
#include "include/types.h"

/**
 * A constructor.
 */
Serial::Serial()
{
    this->device = new QSerialPort();
    this->manual_mess = {};
    this->manual_mess.type = MANUAL;
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
    }
    return false;
}


void Serial::disconnect()
{
    this->device->close();
}


void Serial::readFromPort() {
    QByteArray buffer;
    buffer.append(this->device->readAll());
    char *raw_buffer = buffer.data();
    switch (buffer[0])
    {
      case STATUS:
      {
        uint message_size = sizeof(Status_mess_t);

        if (buffer.size() >= message_size)
        {
          Status_mess_t* frame_ptr = (Status_mess_t*)raw_buffer;
          buffer.remove(0, message_size);
          emit new_fan_status(frame_ptr->status);
        }

        break;
      }

    default:
    {
        buffer.remove(0,1);
    }

    }

}


QList<QSerialPortInfo> Serial::getDevices()
{
    return QSerialPortInfo::availablePorts();
}


QString Serial::findKnownDevice(QList<QSerialPortInfo> devices)
{
    for (int i = 0; i < devices.count(); i++)
    {
        QString manufacturer = devices.at(i).manufacturer();
        quint16 productIdentifier = devices.at(i).productIdentifier();
        quint16 vendorIdentifier = devices.at(i).vendorIdentifier();

        if( manufacturer == DEVICE_MANUFACTURER &&
            productIdentifier == DEVICE_ID &&
            vendorIdentifier == VENDOR_ID)
        {
            return devices.at(i).portName();
        }
    }
    return "";
}


void Serial::sendMessageToDevice()
{
    if(this->device->isOpen() && this->device->isWritable())
    {
        char* mess_ptr = (char*)&(this->manual_mess);
        this->device->write(mess_ptr, sizeof(Manual_mess_t));
    }
}


void Serial::setCpuFanSpeed(int percentage)
{
    this->manual_mess.profile.cpu_fan = percentage;
    this->manual_mess.profile.led.blue = percentage;
    this->sendMessageToDevice();
}


void Serial::setGpuFanSpeed(int percentage)
{
    this->manual_mess.profile.gpu_fan = percentage;
    this->manual_mess.profile.led.red = percentage;
    this->sendMessageToDevice();
}

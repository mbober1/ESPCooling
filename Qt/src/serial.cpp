#include "serial.hpp"


/**
 * A constructor.
 */
Serial::Serial(QWidget *parent)
{
    this->device = new QSerialPort();
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


void Serial::disconnect() {
    this->device->close();
}


void Serial::readFromPort() {
    static std::string buffer;

    buffer.append(this->device->readAll());

    int packetSeparator = buffer.find(";");

    while (packetSeparator != std::string::npos) {
        if(packetSeparator == 0) {
            buffer.erase(0,1);
            packetSeparator = buffer.find(";");
            if(packetSeparator == std::string::npos) break;
        }

        std::string packet = buffer.substr(0, packetSeparator);
        buffer.erase(0, packetSeparator+1);
        packetSeparator = buffer.find(";");

        char type = packet.at(0);

        switch (type)
        {
        case 'C': {  // get fan1 speed
            packet.erase(0, 1);
            emit cpuSpeedChanged(std::atoi(packet.c_str()));
            break;
        }

        case 'G': {  // get fan2 speed
            packet.erase(0, 1);
            emit gpuSpeedChanged(std::atoi(packet.c_str()));
            break;
        }

        case 'S': {  // get fan1 percentage
            packet.erase(0, 1);
            emit cpuPercentageChanged(std::atoi(packet.c_str()));
            break;
        }

        case 'T': {  // get fan2 percentage
            packet.erase(0, 1);
            emit gpuPercentageChanged(std::atoi(packet.c_str()));
            break;
        }
        
        default:
            // printf("Unkown packet! Size %d, Data: %s\n", packet.size(), packet.c_str());
            break;
        }
    }
}

QList<QSerialPortInfo> Serial::getDevices() {
    return QSerialPortInfo::availablePorts();
}

QString Serial::findKnowDevice(QList<QSerialPortInfo> devices) {
    for (size_t i = 0; i < devices.count(); i++)
    {
        if(devices.at(i).manufacturer() == "Silicon Labs" && devices.at(i).productIdentifier() == 60000 && devices.at(i).vendorIdentifier() == 4292) {
            return devices.at(i).portName();
        }
    }
    return "";
}


void Serial::sendMessageToDevice(QString message) {
    if(this->device->isOpen() && this->device->isWritable()) {
        this->device->write(message.toStdString().c_str());
    }
}


void Serial::setCpuFanSpeed(int percentage) {
    QString message("P");
    message.append(QString::number(percentage));
    message.append(";");
    this->sendMessageToDevice(message);
}


void Serial::setGpuFanSpeed(int percentage) {
    QString message("W");
    message.append(QString::number(percentage));
    message.append(";");
    this->sendMessageToDevice(message);
}

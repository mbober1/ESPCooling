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

    } else qDebug() << "Port opening error";
    return false;
}


void Serial::disconnect() {
    this->device->close();
}


void Serial::readFromPort() {
    static std::string buffer;

    buffer.append(this->device->readAll());

    int separator = buffer.find("\r\n");

    while(separator != std::string::npos) {
        std::string data = buffer.substr(0, separator + 1);
        buffer.erase(0, separator+2);
        separator = buffer.find("\r\n");

        int packetSeparator = data.find(";");

        while (packetSeparator != std::string::npos) {
            std::string packet = data.substr(0, packetSeparator);
            data.erase(0, packetSeparator+1);
            packetSeparator = data.find(";");

            char type = packet.at(0);

            switch (type)
            {
            case 'C': {
                std::string cpu = packet.substr(1, packet.size()-1);
                emit cpuSpeedChanged(std::atoi(cpu.c_str()));
                break;
            }

            case 'G': {
                std::string gpu = packet.substr(1, packet.size()-1);
                emit gpuSpeedChanged(std::atoi(gpu.c_str()));
                break;
            }

            case 'S': {
                std::string cpu = packet.substr(1, packet.size()-1);
                emit cpuPercentageChanged(std::atoi(cpu.c_str()));
                break;
            }

            case 'T': {
                std::string gpu = packet.substr(1, packet.size()-1);
                emit gpuPercentageChanged(std::atoi(gpu.c_str()));
                break;
            }
            
            default:
                break;
            }
        }
    }
}


void Serial::sendMessageToDevice(QString message) {
    if(this->device->isOpen() && this->device->isWritable()) {
        this->device->write(message.toStdString().c_str());
    }
}

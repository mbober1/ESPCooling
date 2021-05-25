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

    } else qDebug() << "Port opening error";
    return false;
}


void Serial::disconnect() {
    this->device->close();
}


void Serial::readFromPort() {
    static std::string buffer;

    buffer.append(this->device->readAll());

    // int separator = buffer.find("\r\n");

    // while(separator != std::string::npos) {
    //     std::string data = buffer.substr(0, separator + 1);
    //     buffer.erase(0, separator+2);
    //     separator = buffer.find("\r\n");

        int packetSeparator = buffer.find(";");

        while (packetSeparator != std::string::npos) {
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
                printf("Unkown packet! Size %d, Data: %s\n", packet.size(), packet.c_str());
                break;
            }
        }
    // }
}


void Serial::sendMessageToDevice(QString message) {
    if(this->device->isOpen() && this->device->isWritable()) {
        this->device->write(message.toStdString().c_str());
    }
}

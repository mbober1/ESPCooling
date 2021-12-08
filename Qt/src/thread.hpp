#ifndef THREAD_HPP
#define THREAD_HPP

#include <QThread>
#include <QDebug>
#include "include/hid_interface.hpp"

class Thread : public QThread
{
private:
    HID_Interface* device;

    void run()
    {
        qDebug()<<"From worker thread: "<<currentThreadId();
    }
};

#endif // THREAD_HPP

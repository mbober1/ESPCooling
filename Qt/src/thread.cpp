#include "include/thread.hpp"





void Thread::run()
{
  HID_Interface device(VENDOR_ID, PRODUCT_ID);

  while (!device.open())
  {
    sleep(1);
  }
  
  while (true)
  {
    qDebug() << "From worker thread: " << currentThreadId();
//    device.read();
  }

}

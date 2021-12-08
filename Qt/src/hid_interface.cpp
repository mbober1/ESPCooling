#include "include/hid_interface.hpp"


HID_Interface::HID_Interface(const unsigned short &vendor_id, const unsigned short &product_id) :
    vendor_id(vendor_id),
    product_id(product_id),
    connected(false)
{
  hid_init();
}


HID_Interface::~HID_Interface()
{
  workerThread.quit();
  workerThread.wait();

  hid_close(handle);
  hid_exit();
}


bool HID_Interface::open()
{
  this->handle = hid_open(this->vendor_id, this->product_id, NULL);

  if (nullptr == handle)
  {
    this->connected = false;
    printf("UNABLE TO CONNECT!\n");
  }
  else
  {
    this->connected = true;
      printf("CONNECTED!\n");
  }

  emit connection_status(this->connected);
  return this->connected;
}

void HID_Interface::run()
{
    workerThread.start();

    printf("run\n");
}


std::string HID_Interface::get_manufacturer_id()
{
  wchar_t buffer[MAX_STR];
    hid_get_manufacturer_string(handle, buffer, MAX_STR);
  std::wstring wresult(buffer);
  std::string result(wresult.begin(), wresult.end());
  return result;
}


std::string HID_Interface::get_product_id()
{
  wchar_t buffer[MAX_STR];
    hid_get_product_string(handle, buffer, MAX_STR);
  std::wstring wresult(buffer);
  std::string result(wresult.begin(), wresult.end());
  return result;
}


std::string HID_Interface::get_serial_number()
{
  wchar_t buffer[MAX_STR];
    hid_get_serial_number_string(handle, buffer, MAX_STR);
  std::wstring wresult(buffer);
  std::string result(wresult.begin(), wresult.end());
  return result;
}


slave_mess_t HID_Interface::read()
{
  slave_mess_t rx_buffer;
  hid_read(handle, (unsigned char *)&rx_buffer, sizeof(slave_mess_t));
  emit resultReady(rx_buffer);
  return rx_buffer;
}


bool HID_Interface::write(const master_mess_t &mess)
{
  unsigned char* tx_buffer_ptr = (unsigned char*)&mess;
  return hid_write(this->handle, tx_buffer_ptr, sizeof(master_mess_t));
}

//void Worker::run(HID_Interface &device)
//{

//    printf("dowork\n");
//    while (!device.open())
//    {
//        QThread::sleep(1);
//    }

//    while (true)
//    {
//        device.read();
//    }

//}

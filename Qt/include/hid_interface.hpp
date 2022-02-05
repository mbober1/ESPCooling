#pragma once

#include <hidapi/hidapi.h>
#include <string>
#include <QtCore>
#include "include/thread.hpp"
#include "include/data_types.hpp"

#define MAX_STR 255






class HID_Interface : public QObject
{
  Q_OBJECT
  unsigned short vendor_id;
  unsigned short product_id;
  hid_device *handle;


public:
  HID_Interface(const unsigned short &vendor_id, const unsigned short &product_id);
  ~HID_Interface();
  std::string get_manufacturer_id();
  std::string get_product_id();
  std::string get_serial_number();
  slave_mess_t read();
  bool open();

  bool connected;




public slots:
  bool write(const master_mess_t &mess);

};

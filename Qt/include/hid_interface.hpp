#pragma once

#include <hidapi/hidapi.h>
#include <string>
#include <QtCore>
#include "include/thread.hpp"

#define MAX_STR 255


typedef struct
{
  uint16_t cpu_setpoint;
  uint16_t gpu_setpoint;

} master_mess_t;


typedef struct
{
  uint16_t cpu_fan_speed;
  uint16_t gpu_fan_speed;

} slave_mess_t;



class HID_Interface : public QObject
{
  Q_OBJECT
  unsigned short vendor_id;
  unsigned short product_id;
  bool connected;
  hid_device *handle;


public:
  HID_Interface(const unsigned short &vendor_id, const unsigned short &product_id);
  ~HID_Interface();
  std::string get_manufacturer_id();
  std::string get_product_id();
  std::string get_serial_number();
  slave_mess_t read();
  bool open();



public slots:
  bool write(const master_mess_t &mess);

signals:
  void resultReady(const slave_mess_t &result);
  void connection_status(bool status);

};

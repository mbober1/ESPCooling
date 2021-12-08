#ifndef HID_INTERFACE_HPP
#define HID_INTERFACE_HPP

#include <hidapi/hidapi.h>
#include <string>
#include "src/thread.hpp"
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
    hid_device *handle;
    Thread workerThread;
    unsigned short vendor_id;
    unsigned short product_id;
    bool connected;


public:
  HID_Interface(const unsigned short &vendor_id, const unsigned short &product_id);
  ~HID_Interface();
  std::string get_manufacturer_id();
  std::string get_product_id();
  std::string get_serial_number();
  slave_mess_t read();
  bool open();
  void run();


public slots:
  bool write(const master_mess_t &mess);

signals:
    void resultReady(const slave_mess_t &result);
    void connection_status(bool status);

};



#endif // HID_INTERFACE_HPP

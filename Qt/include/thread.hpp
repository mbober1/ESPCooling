#pragma once

#include <QtCore>
#include <QtDebug>
#include "hid_interface.hpp"
#include "include/data_types.hpp"

#define VENDOR_ID 0x483
#define PRODUCT_ID 0x91D1


class Thread : public QThread
{
public:
  
  void run();

signals:
  void read_data(const slave_mess_t &result);
  void connection_status(bool status);

};

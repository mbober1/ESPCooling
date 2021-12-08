#pragma once

#include <QtCore>
#include <QtDebug>
#include "hid_interface.hpp"


#define VENDOR_ID 0x483
#define PRODUCT_ID 0x91D1

class Thread : public QThread
{
public:

  void run();
};

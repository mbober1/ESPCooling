#ifndef DATA_TYPES_HPP
#define DATA_TYPES_HPP
#include "stdint.h"

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



#endif // DATA_TYPES_HPP

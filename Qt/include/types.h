#ifndef __TYPES_H
#define __TYPES_H

#include <stdint.h>

#define PROFILES_COUNT 5
#define CRC_LEN 4UL

#define DEVICE_MANUFACTURER "STMicroelectronics"
#define DEVICE_ID 22336
#define VENDOR_ID 1155

typedef enum
{
  ACK = 1,
  MANUAL,
  CONFIG,
  STATUS,
  MAX_FRAME_TYPE
} Frame_t;

typedef struct
{
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} Colours_t;

typedef struct
{
  uint16_t frequency;
  uint16_t duty;
} Fan_Status_t;

typedef struct
{
  Colours_t led;
  uint8_t cpu_fan;
  uint8_t gpu_fan;
} Profile_t;

typedef struct
{
  Fan_Status_t cpu;
  Fan_Status_t gpu;
} Status_t;

typedef struct
{
  Profile_t profile[PROFILES_COUNT];
} Config_t;

typedef struct
{
  uint8_t type;
  Config_t config;
  uint32_t crc;
} Config_mess_t;

typedef struct
{
  uint8_t type;
  Profile_t profile;
  uint32_t crc;
} Manual_mess_t;

typedef struct
{
  uint8_t type;
  Status_t status;
  uint32_t crc;
} Status_mess_t;

typedef struct
{
  Frame_t type;
} ACK_mess_t;

#endif

#ifndef SAILINGBOAT_INCLUDE_MAESTRO_REGISTRY_H_
#define SAILINGBOAT_INCLUDE_MAESTRO_REGISTRY_H_

typedef enum {
  MAESTRO_SET_POSITION = 0x84,
  MAESTRO_SET_SPEED = 0x87,
  MAESTRO_SET_ACCELERATION = 0x89,
  MAESTRO_GET_POSITION = 0x90,
  MAESTRO_GET_MOVING = 0x93,
  MAESTRO_GET_ERROR = 0xA1,
  MAESTRO_SET_HOME = 0xA2
} MaestroRegistry;

#endif // SAILINGBOAT_INCLUDE_MAESTRO_REGISTRY_H_
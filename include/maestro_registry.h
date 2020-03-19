#ifndef SAILINGBOAT_INCLUDE_MAESTRO_REGISTRY_H_
#define SAILINGBOAT_INCLUDE_MAESTRO_REGISTRY_H_

/**
 * Maestro Registry
 */
typedef enum {
  /**
   * Set position, registry used by Maestro
   */
  MAESTRO_SET_POSITION = 0x84,
  /**
   * Set speed, registry used by Maestro
   */
  MAESTRO_SET_SPEED = 0x87,
  /**
   * Not in use
   */
  MAESTRO_SET_ACCELERATION = 0x89,
  /**
   * Not in use
   */
  MAESTRO_GET_POSITION = 0x90,
  /**
   * Not in use
   */
  MAESTRO_GET_MOVING = 0x93,
  /**
   * Not in use
   */
  MAESTRO_GET_ERROR = 0xA1,
  /**
   * Not in use
   */
  MAESTRO_SET_HOME = 0xA2
} MaestroRegistry;

#endif // SAILINGBOAT_INCLUDE_MAESTRO_REGISTRY_H_

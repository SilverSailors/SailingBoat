#ifndef SAILINGBOAT_INCLUDE_MAESTRO_H_
#define SAILINGBOAT_INCLUDE_MAESTRO_H_
#include "maestro_registry.h"

class Maestro {
 public:
  /**
   * The constructor, initializes member fields
   */
  Maestro();
  /**
   * Initializes connection to hardware
   * @return boolean value on successful initialization
   */
  bool Init();
  /**
   * Writes and sends new control signals to hardware
   * @param handle Writing handle
   * @param channel Channel to use
   * @param command Command to use
   * @param value Value for writing
   */
  void Command(int handle, unsigned char channel, MaestroRegistry command, int value);
  /**
   * Returns "file_descriptor_" member field
   * @return "file_descriptor_" value
   */
  int GetFileDescriptor();
  /**
   * Returns "lower_limit_" member field
   * @return "lower_limit_" value
   */
  int GetLowerLimit();
  /**
   * Returns "upper_limit_" member field
   * @return "upper_limit_" value
   */
  int GetUpperLimit();
 private:
  /**
   * Initialized, if Maestro is initialized
   */
  bool initialized_;
  /**
   * File descriptor, connection to hardware
   */
  int file_descriptor_;
  /**
   * Portname, for file descriptor
   */
  const char *portname_;
  /**
   * Lower limit control signal
   */
  int lower_limit_;
  /**
   * Upper limit control signal
   */
  int upper_limit_;
};

#endif // SAILINGBOAT_INCLUDE_MAESTRO_H_

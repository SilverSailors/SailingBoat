#ifndef __MAESTRO_HPP__
#define __MAESTRO_HPP__
#include "maestro_registry.hpp"

class Maestro {
 public:
  Maestro();
  bool Init();
  void Command(int handle, unsigned char channel, MaestroRegistry command, int value);
  int GetFileDescriptor();
  int GetLowerLimit();
  int GetUpperLimit();
 private:
  bool initialized_;
  int file_descriptor_;
  const char *portname_;
  int lower_limit_;
  int upper_limit_;
};

#endif //__MAESTRO_HPP__

#ifndef __MAESTRO_HPP__
#define __MAESTRO_HPP__
#include "MAESTRO_REGISTRY.hpp"

class MAESTRO {
 public:
  MAESTRO();
  bool init();
  void command(int handle, unsigned char channel, MAESTRO_REGISTRY command, int value);
  int get_file_descriptor();
  int get_lower_limit();
  int get_upper_limit();

 private:
  bool m_initialized;
  int m_file_descriptor;
  const char *m_portname;
  int m_lower_limit;
  int m_upper_limit;
};

#endif //__MAESTRO_HPP__

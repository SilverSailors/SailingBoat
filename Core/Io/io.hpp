#ifndef __IO_HPP__
#define __IO_HPP__
#include <vector>
#include <string>

class Io {
 public:
  Io();
  ~Io();
  std::vector<std::string> ReadFile(std::string filepath);
  void WriteFile(std::string data, std::string path);
};

#endif //__IO_HPP__

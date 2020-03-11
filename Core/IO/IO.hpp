#ifndef __IO_HPP__
#define __IO_HPP__
#include <vector>
#include <string>

class IO {
 public:
  IO();
  ~IO();
  std::vector<std::string> read_file(std::string filepath);
  void write_file(std::string data, std::string path);

 private:
};

#endif //__IO_HPP__

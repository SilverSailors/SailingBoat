#ifndef SAILINGBOAT_INCLUDE_IO_H_
#define SAILINGBOAT_INCLUDE_IO_H_
#include <vector>
#include <string>

class IO {
 public:
  IO();
  ~IO();
  std::vector<std::string> ReadFile(std::string filepath);
  void WriteFile(std::string data, std::string path);
};

#endif // SAILINGBOAT_INCLUDE_IO_H_

#ifndef SAILINGBOAT_INCLUDE_IO_H_
#define SAILINGBOAT_INCLUDE_IO_H_
#include <vector>
#include <string>
#include "json.hpp"

class IO {
 public:
  IO();
  ~IO();
  std::vector<std::string> ReadFile(std::string filepath);
  void WriteJsonFile(nlohmann::json data, std::string path);
  void WriteFile(std::string data, std::string path);
};

#endif // SAILINGBOAT_INCLUDE_IO_H_

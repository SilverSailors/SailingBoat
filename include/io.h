#ifndef SAILINGBOAT_INCLUDE_IO_H_
#define SAILINGBOAT_INCLUDE_IO_H_
#include <vector>
#include <string>
#include "json.hpp"

class IO {
 public:
  /**
   * The constructor
   */
  IO();
  /**
   * The destructor
   */
  ~IO();
  /**
   * Opens up and reads file specified
   * @param filepath Path to file
   * @return File's content
   */
  std::vector<std::string> ReadFile(std::string filepath);
  /**
   * Writes the data given to json
   * @param data Data to write
   * @param path Path to file
   */
  void WriteJsonFile(nlohmann::json data, std::string path);
  /**
   * Writes the data given to file
   * @param data Data to write
   * @param path Path to file
   */
  void WriteFile(std::string data, std::string path);
};

#endif // SAILINGBOAT_INCLUDE_IO_H_

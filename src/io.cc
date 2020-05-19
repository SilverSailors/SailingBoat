#include "../include/io.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

std::vector<std::string> IO::ReadFile(const std::string &filepath) {
  std::vector<std::string> file_data;

  std::ifstream instream(filepath);
  if (instream.fail()) {
    return std::vector<std::string>();
  }

  std::string text_line;
  while (std::getline(instream, text_line)) {
    file_data.push_back(text_line);
  }

  return file_data;
}

void IO::WriteFile(const nlohmann::json &data, const std::string &path) {
  std::ofstream log_info(path, std::ios::app);
  if (log_info.is_open()) {
    log_info << std::setw(4) << data << std::endl;
    log_info << std::setw(4) << data << "," << std::endl;
    log_info.close();
  }
}
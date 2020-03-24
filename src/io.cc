#include "../include/io.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "../include/DataContainers/log.h"

IO::IO() {

}

IO::~IO() {

}

std::vector<std::string> IO::ReadFile(std::string filepath) {
  std::vector<std::string> file_data;

  std::ifstream instream(filepath);
  if (instream.fail()) {
    std::cout << "Failed to open file: " << filepath << std::endl;
    return std::vector<std::string>();
  }

  std::cout << "Opened File: " << filepath << std::endl;

  std::string text_line;
  while (std::getline(instream, text_line)) {
    file_data.push_back(text_line);
  }

  return file_data;
}

void IO::WriteJsonFile(nlohmann::json data, std::string path) {
  std::ofstream log_info(path, std::ios::app);
  if (log_info.is_open()) {
    //std::cout << "SUCCESS!" << std::endl;
    log_info << std::setw(4) << data << std::endl;
    log_info.close();
  } else {
    std::cout << "FAILED TO CREATE/OPEN FILE" << std::endl;
  }
}


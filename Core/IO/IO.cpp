#include "IO.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../../Utilities/Data_Containers/LOG.hpp"

IO::IO() {

}

IO::~IO() {

}

std::vector<std::string> IO::read_file(std::string file) {
  std::vector<std::string> file_data;

  std::ifstream instream(file);
  if (instream.fail()) {
    std::cout << "Failed to open file: " << file << std::endl;
    return std::vector<std::string>();
  }

  std::cout << "Opened File: " << file << std::endl;

  std::string text_line;
  while (std::getline(instream, text_line)) {
    file_data.push_back(text_line);
  }

  return file_data;
}

void IO::write_file(std::string data, std::string path) {
  std::fstream log_info(path, std::ios::out | std::ios::app);
  if (log_info.is_open()) {
    //std::cout << "SUCCESS!" << std::endl;
    log_info << data << std::endl;
    log_info.close();
  } else {
    std::cout << "FAILED TO CREATE/OPEN FILE" << std::endl;
  }
}



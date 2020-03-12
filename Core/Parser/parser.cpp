#include "parser.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

std::vector<std::string> Parser::RemoveComments(std::vector<std::string> data) {
  int iterations = data.size();
  std::vector<std::string> parsed_data;

  for (int i = 0; i < iterations; i++) {
    if (data[i][0] != '#') {
      parsed_data.push_back(data[i]);
    }
  }

  return parsed_data;
}

std::vector<std::string> Parser::SplitString(std::string line, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(line);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

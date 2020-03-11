#ifndef __PARSER_HPP__
#define __PARSER_HPP__
#include <string>
#include <vector>

class Parser {
 public:
  std::vector<std::string> RemoveComments(std::vector<std::string> data);
  std::vector<std::string> SplitString(std::string line, char delimiter);
};

#endif //__PARSER_HPP__

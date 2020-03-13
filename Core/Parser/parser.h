#ifndef SAILINGBOAT_CORE_PARSER_PARSER_H_
#define SAILINGBOAT_CORE_PARSER_PARSER_H_
#include <string>
#include <vector>

class Parser {
 public:
  std::vector<std::string> RemoveComments(std::vector<std::string> data);
  std::vector<std::string> SplitString(std::string line, char delimiter);
};

#endif //SAILINGBOAT_CORE_PARSER_PARSER_H_

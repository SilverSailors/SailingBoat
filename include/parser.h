#ifndef SAILINGBOAT_INCLUDE_PARSER_H_
#define SAILINGBOAT_INCLUDE_PARSER_H_
#include <string>
#include <vector>

class Parser {
 public:
  /**
   * Removes comments from data vector
   * @param data Data
   * @return Parsed data without comments
   */
  std::vector<std::string> RemoveComments(std::vector<std::string> data);
  /**
   * Splits line string by given delimiter
   * @param line String line
   * @param delimiter Delimiter
   * @return Tokens vector
   */
  std::vector<std::string> SplitString(std::string line, char delimiter);
};

#endif //SAILINGBOAT_INCLUDE_PARSER_H_

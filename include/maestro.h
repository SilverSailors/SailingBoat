#ifndef SAILINGBOAT_INCLUDE_MAESTRO_H_
#define SAILINGBOAT_INCLUDE_MAESTRO_H_

class Maestro {
 public:
  /**
   * The constructor, initializes member fields
   */
  Maestro();
  /**
   * Returns "initialized_" member field value
   * @return "initialized_" object
   */
  bool GetInitialized();
  /**
   * Writes and sends new control signals to hardware
   * @param channel Channel to use
   * @param command Command to use
   * @param value Value for writing
   */
  void Command(unsigned char channel, unsigned char command, int value);
  /**
   * Returns "upper_limit_" member field
   * @return "upper_limit_" value
   */
  int GetUpperLimit();
  /**
   * Returns "lower_limit_" member field
   * @return "lower_limit_" value
   */
  int GetLowerLimit();
 private:
  /**
   * Initialized, if Maestro is initialized
   */
  bool initialized_;
  /**
   * File descriptor, connection to hardware
   */
  int file_descriptor_;
};

#endif // SAILINGBOAT_INCLUDE_MAESTRO_H_

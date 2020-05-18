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
   * @return "initialized_" value
   */
  bool GetInitialized();
  /**
   * Writes new control signals to hardware
   * @param channel Channel to use
   * @param command Command to use
   * @param value Value for writing
   */
  void Command(unsigned char channel, unsigned char command, unsigned int value);
 private:
  /**
   * If Maestro is initialized
   */
  bool initialized_;
  /**
   * Connection to hardware
   */
  int file_descriptor_;
};

#endif // SAILINGBOAT_INCLUDE_MAESTRO_H_

#ifndef SAILINGBOAT_INCLUDE_COMPASS_H_
#define SAILINGBOAT_INCLUDE_COMPASS_H_

class Compass {
 public:
  /**
   * The constructor, initializes member fields
   */
  Compass();
  /**
   * Returns "initialized_" member field value
   * @return "initialized_" object
   */
  bool GetInitialized();
  /**
   * Reads data from Compass component
   * @return Retrieved compass data
   */
  int Read();
 private:
  /**
    * Shifts bits with a left shift
    * @param high Bits to be shifted
    * @param low Endian value
    * @return Result from shift
    */
  static unsigned int Bitshift(unsigned int high, unsigned int low);
  /**
   * Boolean value on Compass component initialized or not
   */
  bool initialized_;
  /**
   * Connection to hardware
   */
  int file_descriptor_;
};

#endif //SAILINGBOAT_INCLUDE_COMPASS_H_

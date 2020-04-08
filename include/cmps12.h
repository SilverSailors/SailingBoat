#ifndef SAILINGBOAT_INCLUDE_CMPS12_H_
#define SAILINGBOAT_INCLUDE_CMPS12_H_

class CMPS12 {
 public:
  /**
   * The constructor, initializes member fields
   */
  CMPS12();
  /**
   * Returns "initialized_" member field value
   * @return "initialized_" object
   */
  bool GetInitialized();
  /**
   * Reads data from CMPS12 component
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
  int Bitshift(int high, int low);
  /**
   * Initialized, boolean value on CMPS12 component initialized or not
   */
  bool initialized_;
  /**
   * File descriptor, connection to hardware
   */
  int file_descriptor_;
};

#endif // SAILINGBOAT_INCLUDE_CMPS12_H_

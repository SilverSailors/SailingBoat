#ifndef __MA3_HPP__
#define __MA3_HPP__

class Ma3 {
 public:
  Ma3();
  bool Init(int spi_channel);
  int Read(int spi_channel);
 private:
  bool initialized_;
  int file_descriptor_;
  int channel_config_;
};

#endif //__MA3_HPP__

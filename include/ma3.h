#ifndef SAILINGBOAT_INCLUDE_MA3_H_
#define SAILINGBOAT_INCLUDE_MA3_H_

class MA3 {
 public:
  MA3();
  bool Init(int spi_channel);
  int Read(int spi_channel);
 private:
  bool initialized_;
  int file_descriptor_;
  int channel_config_;
};

#endif // SAILINGBOAT_INCLUDE_MA3_H_

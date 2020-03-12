#ifndef SAILINGBOAT_HARDWARE_MA3_MA3_H_
#define SAILINGBOAT_HARDWARE_MA3_MA3_H_

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

#endif // SAILINGBOAT_HARDWARE_MA3_MA3_H_

#ifndef __MA3_HPP__
#define __MA3_HPP__

class MA3 {
 public:
  MA3();
  bool init(int spi_channel);
  int read(int spi_channel);

 private:
  bool m_initialized;
  int m_file_descriptor;
  int m_channel_config;
};

#endif//__MA3_HPP__

#include <Arduino.h>

struct RGB
{
  uint8_t red;
  uint8_t green;
  uint8_t blue;

public:
  static std::vector<RGB> multipleFrom(std::string message);
  static RGB singleFrom(std::string message);
  
  static std::vector<RGB> multipleFrom(unsigned char *data);
  static RGB singleFrom(unsigned char *data);
};
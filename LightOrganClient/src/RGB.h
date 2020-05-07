#include <Arduino.h>

struct RGB
{
  int red;
  int green;
  int blue;

public:
  static std::vector<RGB> multipleFrom(std::string message);
  static RGB singleFrom(std::string message);
};
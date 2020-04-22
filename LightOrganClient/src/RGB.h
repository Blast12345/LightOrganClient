#include <Arduino.h>

struct RGB
{
  int red;
  int green;
  int blue;

public:
  static RGB fromMessage(std::string message);
  boolean isValid();
};
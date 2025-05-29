#pragma once

#include <Arduino.h>

struct Color
{
  uint8_t red{0};
  uint8_t green{0};
  uint8_t blue{0};

  // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
  Color(uint8_t red, uint8_t green, uint8_t blue)
      : red(red), green(green), blue(blue) {}
};
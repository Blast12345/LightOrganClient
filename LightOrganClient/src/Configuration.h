#pragma once

#include "Amperage.h"
#include "LedSegment.h"
#include "LedChain.h"
#include "Voltage.h"
#include "Secrets.h"
#include "NetworkCredentials.h"

// ESP32
constexpr unsigned long baudRate = 115200;

// LEDs
constexpr unsigned int ledPin = 13; // I'd prefer to pass this into the constructor, but FastLEDs API does not seem to make this possible.

// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
LedChain<ledPin> ledChain = LedChain<ledPin>(
    Voltage(5.0),
    Amperage(1.0), {
                       LedSegment(16), // TODO: Pass in fallback algorithm
                       LedSegment(16),
                   });
// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

// Network (see Secrets.h for WiFi credentials)
constexpr unsigned int serverPort = 9999;
const NetworkCredentials networkCredentials = {Secrets::networkSSID, Secrets::networkPassword};
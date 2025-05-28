#pragma once

#include "Amperage.h"
#include "LedChain.h"
#include "NetworkCredentials.h"
#include "Secrets.h"
#include "Voltage.h"

// TODO: Maybe have a separate set of classes for segments/chains that prepare results for the LedLibrary.

// Board
constexpr unsigned long baudRate = 115200;

// LEDs
constexpr unsigned int ledPin = 13; // I'd prefer to pass this into the constructor, but FastLEDs API does not seem to make this possible.
constexpr unsigned int ledCount = 32;

LedChain<ledPin> ledChain(
    Voltage(5.0),
    Amperage(1.0),
    ledCount);

// Network
constexpr unsigned int serverPort = 9999;
const NetworkCredentials networkCredentials = {Secrets::networkSSID, Secrets::networkPassword};

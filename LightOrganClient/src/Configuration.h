#pragma once

#include <Network.h>
#include "LOServer.h"

extern Network network;
extern LOServer server;

// Client
constexpr int ledCount = 240;
constexpr int ledPin = 13;
constexpr unsigned long baudRate = 115200;
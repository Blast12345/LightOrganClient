#include <ArduinoJson.h>
#include <WiFi.h>
#include "leds/LedChain.h"
#include "network/Network.h"

constexpr unsigned MONITOR_CONNECT_DELAY = 1000;

Network *network;
LedChain<LED_PIN> ledChain(LED_COUNT, Voltage(VOLTAGE), Amperage(AMPERAGE));
// TODO: Validate that we are getting at least 30 updates per second
constexpr unsigned long FALLBACK_TIMEOUT_MS = 10000;
volatile bool colorReceived = false;
volatile uint8_t pendingR = 0, pendingG = 0, pendingB = 0;
volatile unsigned long lastColorReceivedAt = -1;

void onMessageReceived(const String &string, const MacAddress &mac) {
    Serial.println("onMessageReceived");

    JsonDocument json;
    deserializeJson(json, string);

    // assumes it is a color
    pendingR = std::max<uint8_t>(1, json["params"]["r"]);
    pendingG = std::max<uint8_t>(1, json["params"]["g"]);
    pendingB = std::max<uint8_t>(1, json["params"]["b"]);

    colorReceived = true;
    lastColorReceivedAt = millis();
}

void setup() {
    Serial.begin(BAUD_RATE);
    delay(MONITOR_CONNECT_DELAY);
    Serial.println("Baud rate set to: " + String(BAUD_RATE));

    ledChain.setup();

    WiFi.mode(WIFI_STA);

    network = new Network(onMessageReceived);

    Serial.println("Setup complete.");
}

Color hueToColor(uint8_t hue) {
    if (hue < 85) {
        return Color(hue * 3, 255 - hue * 3, 0);
    } else if (hue < 170) {
        hue -= 85;
        return Color(255 - hue * 3, 0, hue * 3);
    } else {
        hue -= 170;
        return Color(0, hue * 3, 255 - hue * 3);
    }
}

void tickFallbackAnimation() {
    uint8_t hue = (millis() / 20) % 256;
    ledChain.setAllTo(hueToColor(hue));
}

// cppcheck-suppress unusedFunction
void loop() {
    if (colorReceived) {
        colorReceived = false;
        ledChain.setAllTo(Color(pendingR, pendingG, pendingB));
    } else if (millis() - lastColorReceivedAt > FALLBACK_TIMEOUT_MS) {
        tickFallbackAnimation();
    } else if (lastColorReceivedAt == -1) {
        tickFallbackAnimation();
    }
}

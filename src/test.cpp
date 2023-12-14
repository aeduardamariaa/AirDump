#include "BluetoothSerial.h"
#include <Arduino.h>

BluetoothSerial SerialBT;

void setup()
{
    Serial.begin(115200);
    SerialBT.begin("esp32bt");
    Serial.println("Started!");
}

void loop()
{
    byte controlSignal = 0b1010;

    SerialBT.write(controlSignal);
    delay(5000);
}
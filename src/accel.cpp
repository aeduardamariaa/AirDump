#include "accel.h"
#include <Wire.h>

void startWire(void)
{
    Wire.begin();
    delay(100);
}

void setRegisters(const uint8_t address)
{
    Wire.beginTransmission(address);       // Start communication with MPU6050 // MPU=0x68
    Wire.write(0x6B);                  // Talk to the register 6B
    Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
    Wire.endTransmission(true);        //end the transmission
}

AccelData * readAccelerometer(const uint8_t address)
{
    Wire.beginTransmission(address);
    Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(address, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
    //For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
    float AccX = (Wire.read() << 8 | Wire.read()); // 16384.0; // X-axis value
    float AccY = (Wire.read() << 8 | Wire.read()); // 16384.0; // Y-axis value
    float AccZ = (Wire.read() << 8 | Wire.read()); // 16384.0; // Z-axis value

    Serial.printf("AccX: %7.2f AccY: %7.2f AccZ: %7.2f\n", AccX, AccY, AccZ);

    static AccelData data = {AccX, AccY, AccZ};
    return &data;
}

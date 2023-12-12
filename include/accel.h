#ifndef ACCEL_H
#define ACCEL_H

#include <Arduino.h>

typedef struct
{
    float AccX;
    float AccY;
    float AccZ;
} AccelData;

void startWire(void);
void setRegisters(const uint8_t address);
AccelData * readAccelerometer(const uint8_t address);

#endif
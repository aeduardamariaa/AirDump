#ifndef ACCEL_H
#define ACCEL_H

#include <Arduino.h>
#include <Adafruit_MPU6050.h>

typedef struct
{
    float x_off_value;
    float y_off_value;
    float z_off_value;
} offset_values;

offset_values * get_offset_values(uint16_t iter_num, Adafruit_Sensor *ada_sensor);

#endif
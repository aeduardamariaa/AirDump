#ifndef ACCEL_H
#define ACCEL_H

#include <Arduino.h>
#include <Adafruit_MPU6050.h>

typedef struct
{
    float x_off_value;
    float x_sample_mean;
    float x_standard_deviation;
    float x_standard_error;

    float y_off_value;
    float y_sample_mean;
    float y_standard_deviation;
    float y_standard_error;

    float z_off_value;
    float z_sample_mean;
    float z_standard_deviation;
    float z_standard_error;
} offset_values;

offset_values * get_offset_values(uint16_t iter_num, Adafruit_Sensor *ada_sensor);

#endif
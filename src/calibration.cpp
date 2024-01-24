#include "calibration.h"

float get_standard_deviation(float *readings, float mean, uint16_t length)
{
  float sum = 0;
  for (uint16_t i = 0; i < length; i++)
  {
    sum += pow(readings[i] - mean, 2);
  }

  return sqrt(sum / (length-1));
}

offset_values *get_offset_values(uint16_t iter_num, Adafruit_Sensor *ada_sensor)
{
  Serial.println("Começando calibração dos sensores!");

  float x_readings[iter_num], y_readings[iter_num], z_readings[iter_num];

  // Finding all the read values for each axis.
  for (uint16_t i = 0; i < iter_num; i++)
  {
    sensors_event_t accel;
    ada_sensor->getEvent(&accel);

    x_readings[i] = accel.acceleration.x;
    y_readings[i] = accel.acceleration.y;
    z_readings[i] = accel.acceleration.z;
  }

  // After that, we need to find the mean value we will use for our offset.
  float x_sum = 0, y_sum = 0, z_sum = 0;
  float x_mean = 0, y_mean = 0, z_mean = 0;

  for (uint16_t i = 0; i < iter_num; i++)
  {
    x_sum += x_readings[i];
    y_sum += y_readings[i];
    z_sum += z_readings[i];
  }
  x_mean = x_sum / iter_num;
  y_mean = y_sum / iter_num;
  z_mean = z_sum / iter_num;

  // These are our values:
  offset_values *offset = (offset_values*)malloc(sizeof(offset_values));
  offset->x_off_value = x_mean;
  offset->y_off_value = y_mean;
  offset->z_off_value = z_mean;

  Serial.println("Calibração terminada!");

  return offset;
}


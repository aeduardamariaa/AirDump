#include "calibration.h"

offset_values *get_offset_values(uint16_t iter_num, Adafruit_Sensor *ada_sensor)
{
  Serial.println("Começando calibração dos sensores!");

  float x_readings[iter_num], y_readings[iter_num], z_readings[iter_num];
  int current_time = millis();

  for (uint16_t i = 0; i < iter_num; i++)
  {
    while (millis() - current_time < 10);

    current_time = millis();

    sensors_event_t accel;
    ada_sensor->getEvent(&accel);

    x_readings[i] = accel.acceleration.x;
    y_readings[i] = accel.acceleration.y;
    z_readings[i] = accel.acceleration.z;
  }

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

  Serial.println("Calibração encerrada!");

  static offset_values offset = {x_mean, y_mean, z_mean};
  return &offset;
}


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
    delay(10);

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

  // Let's correct our data so we can perform the next actions.
  for (uint16_t i = 0; i < iter_num; i++)
  {
    x_readings[i] -= offset->x_off_value;
    y_readings[i] -= offset->y_off_value;
    z_readings[i] -= offset->z_off_value;
  }

  // Let's get the sample mean for each axis after adjusted by the offset.
  float x_sample_sum = 0, y_sample_sum = 0, z_sample_sum = 0;
  for (uint16_t i = 0; i < iter_num; i++)
  {
    x_sample_sum += x_readings[i];
    y_sample_sum += y_readings[i];
    z_sample_sum += z_readings[i];
  }
  offset->x_sample_mean = x_sample_sum / iter_num;
  offset->y_sample_mean = y_sample_sum / iter_num;
  offset->z_sample_mean = z_sample_sum / iter_num;

  // Now we get the default deviation for each array.
  offset->x_standard_deviation = get_standard_deviation(x_readings, x_mean, iter_num);
  offset->y_standard_deviation = get_standard_deviation(y_readings, y_mean, iter_num);
  offset->z_standard_deviation = get_standard_deviation(z_readings, z_mean, iter_num);

  // With the standard deviations in hand, we can calculate standard errors.
  offset->x_standard_error = offset->x_standard_deviation / sqrt(iter_num);
  offset->y_standard_error = offset->y_standard_deviation / sqrt(iter_num);
  offset->z_standard_error = offset->z_standard_deviation / sqrt(iter_num);

  Serial.println("Calibração encerrada!");
  Serial.printf("Valores de offset - X: %.4f Y: %.4f Z: %.4f\n", offset->x_off_value, offset->y_off_value, offset->z_off_value);
  Serial.printf("Desvios padrão - X: %.4f Y: %.4f Z: %.4f\n", offset->x_standard_deviation, offset->y_standard_deviation, offset->z_standard_deviation);
  Serial.printf("Erros padrão - X: %.4f Y: %.4f Z: %.4f\n", offset->x_standard_error, offset->y_standard_error, offset->z_standard_error);

  return offset;
}


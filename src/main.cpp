#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include "calibration.h"

Adafruit_MPU6050 mpu;
Adafruit_Sensor *mpu_temp, *mpu_accel, *mpu_gyro;

int current_time_millis = 0;
float current_speed_ms_x = 0;
float current_speed_ms_y = 0;
float current_speed_ms_z = 0;
float current_position_m[] = {0, 0, 0};

const float STD_ERROR_MP = 1.96;
float x_upper_limit, x_lower_limit;
float y_upper_limit, y_lower_limit;
float z_upper_limit, z_lower_limit;
offset_values *offset;

void correct_readings(sensors_event_t *accel)
{
  accel->acceleration.x -= offset->x_off_value;
  accel->acceleration.y -= offset->y_off_value;
  accel->acceleration.z -= offset->z_off_value;

  if (accel->acceleration.x < x_upper_limit && accel->acceleration.x > x_lower_limit)
    accel->acceleration.x = 0;

  if (accel->acceleration.y < y_upper_limit && accel->acceleration.y > y_lower_limit)
    accel->acceleration.y = 0;

  if (accel->acceleration.z < z_upper_limit && accel->acceleration.z > z_lower_limit)
    accel->acceleration.z = 0;
}

void set_current_time()
{
  current_time_millis = millis();
}

void set_axis_speed(float *axis_speed, float acceleration, int time_millis)
{
  float time_seconds = static_cast<float>(time_millis) / 1000;
  *axis_speed += acceleration * time_seconds;
}

void set_axis_position(char axis, float speed, int time_millis)
{
  uint8_t index;

  switch (axis)
  {
    case 'x':
      index = 0;
      break;
    case 'y':
      index = 1;
      break;
    case 'z':
      index = 2;
      break;
  }

  float time_seconds = static_cast<float>(time_millis) / 1000;
  current_position_m[index] += speed * time_seconds;
}

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    while (1)
      delay(10);
  }

  mpu_accel = mpu.getAccelerometerSensor();
  mpu_accel->printSensorDetails();

  offset = get_offset_values(300, mpu_accel);
  x_upper_limit = offset->x_sample_mean + (offset->x_standard_error * STD_ERROR_MP);
  x_lower_limit = offset->x_sample_mean - (offset->x_standard_error * STD_ERROR_MP);
  y_upper_limit = offset->y_sample_mean + (offset->y_standard_error * STD_ERROR_MP);
  y_lower_limit = offset->y_sample_mean - (offset->y_standard_error * STD_ERROR_MP);
  z_upper_limit = offset->z_sample_mean + (offset->z_standard_error * STD_ERROR_MP);
  z_upper_limit = offset->z_sample_mean - (offset->z_standard_error * STD_ERROR_MP);

  current_time_millis = millis();
}

void loop()
{
  delay(2000);

  sensors_event_t accel;
  mpu_accel->getEvent(&accel);
  correct_readings(&accel);

  Serial.printf("Valores de aceleração após correção (X, Y, Z): {%.2f, %.2f, %.2f}\n", accel.acceleration.x, accel.acceleration.y, accel.acceleration.z);

  int time_passed_millis = millis() - current_time_millis;
  current_time_millis = millis();

  set_axis_speed(&current_speed_ms_x, accel.acceleration.x, time_passed_millis);
  set_axis_speed(&current_speed_ms_y, accel.acceleration.y, time_passed_millis);
  set_axis_speed(&current_speed_ms_z, accel.acceleration.z, time_passed_millis);

  set_axis_position('x', current_speed_ms_x, time_passed_millis);
  set_axis_position('y', current_speed_ms_y, time_passed_millis);
  set_axis_position('z', current_speed_ms_z, time_passed_millis);

  Serial.printf("Posição atual (X, Y, Z): {%.2f, %.2f, %.2f}\n", current_position_m[0], current_position_m[1], current_position_m[2]);
}
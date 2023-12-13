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
offset_values *offset;

void correct_readings(sensors_event_t *accel)
{
  accel->acceleration.x -= offset->x;
  accel->acceleration.y -= offset->y;
  accel->acceleration.z -= offset->z;
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

  offset_values *offset = get_offset_values(1000, mpu_accel);

  current_time_millis = millis();
}

void loop()
{
  sensors_event_t accel;
  mpu_accel->getEvent(&accel);
  correct_readings(&accel);

  int time_passed_millis = millis() - current_time_millis;
  current_time_millis = millis();

  set_axis_speed(&current_speed_ms_x, accel.acceleration.x, time_passed_millis);
  set_axis_speed(&current_speed_ms_y, accel.acceleration.y, time_passed_millis);
  set_axis_speed(&current_speed_ms_z, accel.acceleration.z, time_passed_millis);

  set_axis_position('x', current_speed_ms_x, time_passed_millis);
  set_axis_position('y', current_speed_ms_y, time_passed_millis);
  set_axis_position('z', current_speed_ms_z, time_passed_millis);

  Serial.printf("Posição atual (X, Y, Z): {%.2f, %.2f, %.2f}", current_position_m[0], current_position_m[1], current_position_m[2]);
}
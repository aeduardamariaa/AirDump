#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <BluetoothSerial.h>
#include <Emblate>
#include <stdlib.h>
#include "calibration.h"

Adafruit_MPU6050 mpu;
Adafruit_Sensor *mpu_accel;
sensors_event_t accel;

BluetoothSerial SerialBT;

int calibration_time_millis = 0;
int current_time_millis = 0;
int time_passed_millis = 0;

float averages[3] = {0, 0, 0};
offset_values *offset;
Emblate::Queue<float> x_queue, y_queue, z_queue;

void correct_readings(sensors_event_t *accel)
{
  accel->acceleration.x -= offset->x_off_value;
  accel->acceleration.y -= offset->y_off_value;
  accel->acceleration.z -= offset->z_off_value;
}

void set_current_time()
{
  current_time_millis = millis();
}

void get_average_accelerations(sensors_event_t *accel)
{
  x_queue.push(accel->acceleration.x);
  y_queue.push(accel->acceleration.y);
  z_queue.push(accel->acceleration.z);

  if (x_queue.size() >= 100)
  {
    averages[0] -= x_queue.front() / x_queue.size();
    averages[1] -= y_queue.front() / y_queue.size();
    averages[2] -= z_queue.front() / z_queue.size();

    x_queue.pop();
    y_queue.pop();
    z_queue.pop();
  }

  averages[0] += x_queue.back() / x_queue.size();
  averages[1] += y_queue.back() / y_queue.size();
  averages[2] += z_queue.back() / z_queue.size();
}

void send_bluetooth_data(float* accelerations, int time_passed_millis)
{
  byte data[16];
  long l;

  for (uint8_t i = 0; i < 3; i++)
  {
    for (uint8_t j = 0; j < sizeof(float); j++)
    {
      // Demonic cast to surround problems with bitwise operations on
      // floating point type. Will be re-cast on Python.
      l = * (long *) &(accelerations[i]);
      data[i*4 + j] = (l >> (24 - j * 8)) & 0xFF;
    }
  }

  for (uint8_t i = 0; i < 4; i++)
  {
    l = * (long *) &time_passed_millis;
    data[i+12] = (l >> (24 - i * 8)) & 0xFF;
  }

  SerialBT.write(data, 16);
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

  SerialBT.begin("esp32btcuuuuu");

  mpu_accel = mpu.getAccelerometerSensor();
  mpu_accel->printSensorDetails();

  offset = get_offset_values(300, mpu_accel);
  current_time_millis = millis();
}

void loop()
{
  // if (millis() - calibration_time_millis >= 100)
  // {
  //   offset = get_offset_values(10, mpu_accel);
  //   calibration_time_millis = millis();
  // }

  mpu_accel->getEvent(&accel);
  correct_readings(&accel);
  get_average_accelerations(&accel);

  time_passed_millis = millis() - current_time_millis;
  set_current_time();
  send_bluetooth_data(averages, time_passed_millis);

  Serial.printf("Aceleração: {%.4f, %.4f, %.4f}\n", averages[0], averages[1], averages[2]);
}
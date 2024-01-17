#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <BluetoothSerial.h>
#include <Emblate>
#include "calibration.h"

Adafruit_MPU6050 mpu;
Adafruit_Sensor *mpu_accel;

BluetoothSerial SerialBT;

int current_time_millis = 0;
int count = 0;

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

void manage_queues(sensors_event_t *accel)
{
  x_queue.push(accel->acceleration.x);
  y_queue.push(accel->acceleration.y);
  z_queue.push(accel->acceleration.z);

  if (x_queue.size() >= 100)
  {
    x_queue.pop();
    y_queue.pop();
    z_queue.pop();
  }
}

float* get_average_accelerations()
{
  float x_sum = 0, y_sum = 0, z_sum = 0;

  // TODO: create iterator for queues and substitute here
  for (uint8_t i = 0; i < x_queue.size(); i++)
  {
    x_sum += x_queue[i];
    y_sum += y_queue[i];
    z_sum += z_queue[i];
  }

  float *averages = (float*) malloc(sizeof(float) * 3);
  averages[0] = x_sum / x_queue.size();
  averages[1] = y_sum / y_queue.size();
  averages[2] = z_sum / z_queue.size();

  return averages;
}

void send_bluetooth_data(float* accelerations, int time_passed_millis)
{
  byte data[sizeof(float) * 3 + sizeof(int)];
  long l;

  for (uint8_t i = 0; i < 3; i++)
  {
    for (uint8_t j = 0; j < sizeof(float); j++)
    {
      l = * (long *) &(accelerations[i]); // demonic cast to surround floating point bit problems
      data[i*4 + j] = (l >> (24 - j * 8)) & 0xFF;
    }
  }

  for (uint8_t i = 0; i < 4; i++)
  {
    l = * (long *) &time_passed_millis;
    data[i + sizeof(float) * 3] = (l >> (24 - i * 8)) & 0xFF;
  }

  SerialBT.write(data, sizeof(float) * 3 + sizeof(int));
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
  sensors_event_t accel;
  int time_passed_millis;

  mpu_accel->getEvent(&accel);
  correct_readings(&accel);

  manage_queues(&accel);
  float* average_accelerations = get_average_accelerations();

  time_passed_millis = millis() - current_time_millis;
  send_bluetooth_data(average_accelerations, time_passed_millis);
  count++;

  current_time_millis = millis();

  Serial.printf("Aceleração: {%.4f, %.4f, %.4f}\n", accel.acceleration.x, accel.acceleration.y, accel.acceleration.z);
}
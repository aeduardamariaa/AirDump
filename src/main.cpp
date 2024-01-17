#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include "calibration.h"
#include <BluetoothSerial.h>

Adafruit_MPU6050 mpu;
Adafruit_Sensor *mpu_temp, *mpu_accel, *mpu_gyro;

BluetoothSerial SerialBT;

int current_time_millis = 0;
int print_time_millis = 0;
int count = 0;

offset_values *offset;

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

void send_bluetooth_data(sensors_event_t *accel, int time_passed_millis)
{
  byte data[16];
  long l;

  for (uint8_t i = 0; i < 4; i++) {
    l = * (long *) &(accel->acceleration.x); // demonic cast to surround floating point bit problems
    data[i] = (l >> (24 - i * 8)) & 0xFF;
  }

  for (uint8_t i = 0; i < 4; i++) {
    l = * (long *) &(accel->acceleration.y);
    data[i+4] = (l >> (24 - i * 8)) & 0xFF;
  }

  for (uint8_t i = 0; i < 4; i++) {
    l = * (long *) &(accel->acceleration.z);
    data[i+8] = (l >> (24 - i * 8)) & 0xFF;
  }

  for (uint8_t i = 0; i < 4; i++) {
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
  if (millis() - current_time_millis >= 100)
  {
    sensors_event_t accel;
    int time_passed_millis;

    mpu_accel->getEvent(&accel);
    correct_readings(&accel);

    time_passed_millis = millis() - current_time_millis;
    send_bluetooth_data(&accel, time_passed_millis);
    count++;

    current_time_millis = millis();

    Serial.printf("Aceleração: {%.4f, %.4f, %.4f}\n", accel.acceleration.x, accel.acceleration.y, accel.acceleration.z);
  }
}
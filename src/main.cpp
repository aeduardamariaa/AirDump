#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include "ArduinoBLE.h"
#include "calibration.h"
#include <BluetoothSerial.h>

Adafruit_MPU6050 mpu;
Adafruit_Sensor *mpu_temp, *mpu_accel, *mpu_gyro;

BluetoothSerial SerialBT;

int current_time_millis = 0;
int print_time_millis = 0;

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

void send_bluetooth_data(sensors_event_t *accel)
{
  uint8_t accel_x_int = static_cast<uint8_t>(accel->acceleration.x);
  uint8_t accel_y_int = static_cast<uint8_t>(accel->acceleration.y);
  uint8_t accel_z_int = static_cast<uint8_t>(accel->acceleration.z);

  byte data[3];
  data[0] = accel_x_int;
  data[1] = accel_y_int;
  data[2] = accel_z_int;

  SerialBT.write(data, 3);
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

  // SerialBT.begin("esp32btcuuuuu");

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

  time_passed_millis = millis() - current_time_millis;
  current_time_millis = millis();

  // send_bluetooth_data(&accel);

  if (millis() - print_time_millis >= 5000)
  {
    print_time_millis = millis();
    Serial.println("[VALORES]");
    Serial.printf("Valores de aceleração após correção (X, Y, Z): {%.2f, %.2f, %.2f}\n", accel.acceleration.x, accel.acceleration.y, accel.acceleration.z);
    Serial.printf("Sizeof do time_passed_millis: %i", sizeof(time_passed_millis));
  }
}
#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Wire.h>
#include "accel.h"

/* Reading constants */
const int READ_TIME = 300;

/* Hardware variables */
byte addresses[2];

void scanI2c()
{
  byte address, resultCode, foundDevices;

  for (address = 0; address < 128; address++)
  {
    Wire.beginTransmission(address);
    resultCode = Wire.endTransmission();

    if (resultCode == 0)
    {
      Serial.print ("Dispositivo I2c detectado no endereço: ");
      Serial.println(address, HEX);
      addresses[foundDevices] = address;
      foundDevices++;

      delay(500);
    }
    delay(READ_TIME);
  }

  if (foundDevices > 0)
  {
    Serial.print("Foi encontrado um total de: ");
    Serial.print(foundDevices);
    Serial.println(" dispositivos");
  }
  else
    Serial.println("Nenhum dispositivo foi encontrado !!!");
}

void printAccelerometer(AccelData *data)
{
  Serial.printf("Leitura do acelerômetro: ");
  Serial.print("X ");
  Serial.print(data->AccX);
  Serial.print(" | Y ");
  Serial.print(data->AccY);
  Serial.print(" | Z ");
  Serial.println(data->AccZ);
}

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  // startWire();
  // setRegisters(accel_01);
  // setRegisters(accel_02);
}

void loop()
{
  // AccelData *data_01, *data_02;
  // data_01 = readAccelerometer(accel_01);
  // data_02 = readAccelerometer(accel_02);

  Wire.beginTransmission(addresses[0]);
  Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(addresses[0], 6, true); // Read 6 registers total, each axis value is stored in 2 registers
    //For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
  float AccX = (Wire.read() << 8 | Wire.read()); // 16384.0; // X-axis value
  float AccY = (Wire.read() << 8 | Wire.read()); // 16384.0; // Y-axis value
  float AccZ = (Wire.read() << 8 | Wire.read()); // 16384.0; // Z-axis value

  Serial.printf("AccX: %7.2f AccY: %7.2f AccZ: %7.2f\n", AccX, AccY, AccZ);

  // printAccelerometer(data_01);
  // printAccelerometer(data_02);

  delay(1000);
}
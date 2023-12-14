// #include <Adafruit_MPU6050.h>

// Adafruit_MPU6050 mpu;
// Adafruit_Sensor *mpu_temp, *mpu_accel, *mpu_gyro;

// void setup()
// {
//   Serial.begin(115200);
//   while (!Serial)
//     delay(10);

//   if (!mpu.begin())
//   {
//     Serial.println("Failed to find MPU6050 chip");
//     while (1)
//       delay(10);
//   }

//   mpu_accel = mpu.getAccelerometerSensor();
//   mpu_accel->printSensorDetails();

//   mpu_gyro = mpu.getGyroSensor();
//   mpu_gyro->printSensorDetails();
// }

// void loop()
// {
//   sensors_event_t accel;
//   sensors_event_t gyro;

//   mpu_accel->getEvent(&accel);
//   mpu_gyro->getEvent(&gyro);

//   Serial.print("\t\tAccel X: ");
//   Serial.print(accel.acceleration.x);
//   Serial.print(" \tY: ");
//   Serial.print(accel.acceleration.y);
//   Serial.print(" \tZ: ");
//   Serial.print(accel.acceleration.z);
//   Serial.println(" m/s^2 ");

//   delay(100);
// }
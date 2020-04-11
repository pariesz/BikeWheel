#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>

#define SERIAL_TX_BUFFER_SIZE 256
#define SERIAL_RX_BUFFER_SIZE 256

#define HALL_PIN 3
#define BT_VCC 5

static MPU6050 mpu = MPU6050(MPU6050_DEFAULT_ADDRESS);

void setup() {
    // Turn on bluetooth
    pinMode(BT_VCC, OUTPUT);
    digitalWrite(BT_VCC, HIGH);

    // Setup Hall Sensor
    pinMode(HALL_PIN, INPUT); // input from the OH137

    // Setup MPU-6050
    mpu.initialize();
    mpu.setI2CMasterModeEnabled(0);
    mpu.setI2CBypassEnabled(1);
    mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_2000);
    mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);

    // Offsets calibrated using MPU6050Calibration.ino
    mpu.setXAccelOffset(-2426);
    mpu.setYAccelOffset(1993);
    mpu.setZAccelOffset(5225);

    mpu.setXGyroOffset(149);
    mpu.setYGyroOffset(60);
    mpu.setZGyroOffset(59);
    
    Serial.begin(57600);
}

void loop() {
    static uint32_t us = micros(); 
  
    int16_t motion6[6];
    
    mpu.getMotion6(&motion6[0], &motion6[1], &motion6[2], &motion6[3], &motion6[4], &motion6[5]);
    
    if(motion6[0] == 0 && motion6[1] == 0 && motion6[2] == 0) {
      return;
    }

    // Time difference (in microseconds)
    auto diff = micros() - us;
    us = micros();
    Serial.print(diff);

    // OH137 (Hall-Effect sensor) Value
    int hall = digitalRead(HALL_PIN);
    Serial.print('\t');
    Serial.print(hall == HIGH ? 1 : 0);

    // MPU-6050 values
    Serial.print('\t');
    Serial.print(motion6[0]);
    Serial.print('\t');
    Serial.print(motion6[1]);
    Serial.print('\t');
    Serial.print(motion6[2]);
    Serial.print('\t');
    Serial.print(motion6[3]);
    Serial.print('\t');
    Serial.print(motion6[4]);
    Serial.print('\t');
    Serial.println(motion6[5]);

    delay(5);
}

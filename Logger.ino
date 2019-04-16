#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>

#define HALL_PIN 3
#define SERIAL_TX_BUFFER_SIZE 64
#define SERIAL_RX_BUFFER_SIZE 64

static MPU6050 mpu = MPU6050(MPU6050_DEFAULT_ADDRESS);

void setup() {
    Serial.begin(57600);
    while (!Serial);

    pinMode(HALL_PIN, INPUT); // input from the OH137

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
}

void loop() {
    int hall = digitalRead(HALL_PIN); // read OH137 Value

    int16_t motion6[6];

    mpu.getMotion6(&motion6[0], &motion6[1], &motion6[2], &motion6[3], &motion6[4], &motion6[6]);

    Serial.print(hall == HIGH ? 1 : 0);
    Serial.print(',');
    Serial.print(motion6[0]);
    Serial.print(',');
    Serial.print(motion6[1]);
    Serial.print(',');
    Serial.print(motion6[2]);
    Serial.print(',');
    Serial.print(motion6[3]);
    Serial.print(',');
    Serial.print(motion6[4]);
    Serial.print(',');
    Serial.println(motion6[5]);
}

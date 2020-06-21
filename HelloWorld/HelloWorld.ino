#include <Adafruit_DotStar.h>
#include <I2Cdev.h>
#include "Wire.h"
#include <MPU6050.h>
#include <SoftwareSerial.h>

#define MPU_X_INDEX 0
#define MPU_Y_INDEX 1
#define MPU_Z_INDEX 2
#define STX 0x02 // ASCII start of text
#define ETX 0x03 // ASCII end of text
#define NUL 0x00 // ASCII end of text

Adafruit_DotStar leds = Adafruit_DotStar(144, 11, 13, DOTSTAR_BGR);

// Get offsets calibrated using ../MPU6050 Calibration/MPU6050Calibration.ino
int16_t offsets[] = {
    -1288, 979, 1242, // accl x, y, z
       39, -17,  164  // gyro x, y, z
};

MPU6050 mpu;

HardwareSerial &hc06 = Serial1;
//SoftwareSerial hc06(0, 1);

void setup() {
    Serial.begin(9600); // USB is 12 Mbit/sec
    hc06.begin(9600);
    led_setup();
    mpu_setup();
    //hall_setup();

    //Serial.println("connected");
}

void loop() {
    delay(1000);  // do not print too fast!
    //i2cscan_loop();
    led_loop();
    mpu_loop();
    //hc06_loop();
    //hall_loop();
    bluetooth_loop();
}

void bluetooth_loop() {
    while (Serial.available()) {
        leds.setPixelColor(0, 0xFF0000);
        Serial.write(Serial.read());
    }

    while (hc06.available()) {
        leds.setPixelColor(0, 0x00FF00);
        Serial.write(hc06.read());
    }

    leds.show();
    leds.clear();
}

void led_setup() {
    leds.setBrightness(20);
    leds.begin();
    leds.show();
}

int pixelIndex = 0;
void led_loop() {
    leds.clear();
    leds.setPixelColor(pixelIndex++, 0xFF0000);
    leds.show();
    if (pixelIndex >= 144) pixelIndex = 0;
}

void mpu_setup() {
    Wire.begin(); // join I2C bus (I2Cdev library doesn't do this automatically)

    TWBR = ((F_CPU / 400000L) - 16) / 2; // Switch to 400KHz I2C
    mpu.initialize();

    Serial.print(F("test mpu connection: "));
    Serial.println(mpu.testConnection() ? F("success") : F("failed"));

    mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_2000);
    mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);
    mpu.setI2CBypassEnabled(1);
    mpu.setFIFOEnabled(0);
    mpu.setDMPEnabled(0);
    mpu.setIntEnabled(0);

    mpu.setXAccelOffset(offsets[0]);
    mpu.setYAccelOffset(offsets[1]);
    mpu.setZAccelOffset(offsets[2]);

    mpu.setXGyroOffset(offsets[3]);
    mpu.setYGyroOffset(offsets[4]);
    mpu.setZGyroOffset(offsets[5]);
}

void mpu_loop() {
    int16_t acc[3], gyro[3];

    mpu.getMotion6(
        &acc[MPU_X_INDEX],
        &acc[MPU_Y_INDEX],
        &acc[MPU_Z_INDEX],
        &gyro[MPU_X_INDEX],
        &gyro[MPU_Y_INDEX],
        &gyro[MPU_Z_INDEX]);

    Serial.print("acc(");
    Serial.print(acc[0]);
    Serial.print("\t, ");
    Serial.print(acc[1]);
    Serial.print("\t, ");
    Serial.print(acc[2]);
    Serial.println(")");
}

/*
void hall_setup() {
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
}

void hall_loop() {
    for (int j = 2; j <= 5; j++) {
        digitalWrite(j+4, digitalRead(j));
    }
}

void hc06_loop() {
    // Write data from HC06 to Serial Monitor
    while (hc06.available()) {
        Serial.write(hc06.read());
    }

    // Write from Serial Monitor to HC06
    while (Serial.available()) {
        hc06.write(Serial.read());
    }
}

void i2cscan_loop() {
    byte error, address; //variable for error and I2C address
    int nDevices;

    Serial.println("Scanning...");

    nDevices = 0;
    for (address = 1; address < 127; address++) {
        // The i2c_scanner uses the return value of the Write.endTransmisstion to see if a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0) {
            Serial.print("I2C device found at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.print(address, HEX);
            nDevices++;

        } else if (error == 4) {
            Serial.print("Unknown error at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.println(address, HEX);
        }
    }
    if (nDevices == 0)
        Serial.println("No I2C devices found\n");
    else
        Serial.println("done\n");

    delay(5000); // wait 5 seconds for the next I2C scan
}
*/
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "./Vector.h"
#include "./Mpu2.h"

#define DEBUG

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

#ifdef DEBUG 
#define LOG(message) Serial.println(F(message))
#else
#define LOG(message)
#endif



/* =========================================================================
    NOTE: In addition to connection 3.3v, GND, SDA, and SCL, this sketch
    depends on the MPU-6050's INT pin being connected to the Arduino's
    external interrupt #0 pin. On the Arduino Uno and Mega 2560, this is
    digital I/O pin 2.

    For the Galileo Gen1/2 Boards, there is no INT pin support. Therefore
    the INT pin does not need to be connected, but you should work on getting
    the timing of the program right, so that there is no buffer overflow.
    * ========================================================================= */

#define OUTPUT_READABLE_YAWPITCHROLL

// Unccomment if you are using an Arduino-Style Board
#define ARDUINO_BOARD

// Uncomment if you are using a Galileo Gen1 / 2 Board
// #define GALILEO_BOARD

#define LED_PIN 13      // (Galileo/Arduino is 13)

namespace Mpu2 {
    static MPU6050 mpu;
    static bool blinkState = false;

    // MPU control/status vars
    static bool dmpReady = false;  // set true if DMP init was successful
    static uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
    static uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
    static uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
    static uint16_t fifoCount;     // count of all bytes currently in FIFO
    static uint8_t fifoBuffer[64]; // FIFO storage buffer

    // orientation/motion vars
    static VectorFloat gravity;    // [x, y, z]            gravity vector
    static Quaternion q;           // [w, x, y, z]         quaternion container
    static float euler[3];         // [psi, theta, phi]    Euler angle container
    static float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

    // ================================================================
    // ===               INTERRUPT DETECTION ROUTINE                ===
    // ================================================================

    // This function is not required when using the Galileo 
    volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high

    void dmpDataReady() {
        mpuInterrupt = true;
    }

    // ================================================================
    // ===                      INITIAL SETUP                       ===
    // ================================================================

    void init(Vector3<int16_t>& acel_offset, Vector3<int16_t>& gyro_offset) {

        // join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();

        /* Switch to 400KHz I2C */
        //TWBR = ((F_CPU / 400000L) - 16) / 2;
        TWBR = 24;
        //Wire.setClock(100000); 

#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
#endif

        // initialize device
#ifdef DEBUG 
        Serial.println(F("Initializing I2C devices..."));
#endif
        mpu.initialize();

        // verify connection
#ifdef DEBUG 
        Serial.print(F("Testing device connections: "));
        Serial.println(mpu.testConnection() ? F("successful") : F("failed"));
#endif

        // load and configure the DMP
        LOG("Initializing DMP...");
        devStatus = mpu.dmpInitialize();

        // Offsets calibrated using MPU6050Calibration.ino
        mpu.setXAccelOffset(acel_offset.x);
        mpu.setYAccelOffset(acel_offset.y);
        mpu.setZAccelOffset(acel_offset.z);
        mpu.setXGyroOffset(gyro_offset.x);
        mpu.setYGyroOffset(gyro_offset.y);
        mpu.setZGyroOffset(gyro_offset.z);

        // make sure it worked (returns 0 if so)
        if (devStatus == 0) {
            // turn on the DMP, now that it's ready
            LOG("Enabling DMP...");
            mpu.setDMPEnabled(true);

            // enable Arduino interrupt detection
            LOG("Enabling interrupt detection (Arduino external interrupt 0)...");
            attachInterrupt(0, dmpDataReady, RISING);
            mpuIntStatus = mpu.getIntStatus();

            // set our DMP Ready flag so the main loop() function knows it's okay to use it
            LOG("DMP ready! Waiting for first interrupt...");
            dmpReady = true;

            // get expected DMP packet size for later comparison
            packetSize = mpu.dmpGetFIFOPacketSize();
        }
        else {
            // ERROR!
            // 1 = initial memory load failed
            // 2 = DMP configuration updates failed
            // (if it's going to break, usually the code will be 1)
            Serial.print(F("DMP Initialization failed (code "));
            Serial.print(devStatus);
            Serial.println(F(")"));
        }

        // configure LED for output
        pinMode(LED_PIN, OUTPUT);
    }



    // ================================================================
    // ===                    MAIN PROGRAM LOOP                     ===
    // ================================================================

    void update() {
        // if programming failed, don't try to do anything
        if (!dmpReady) return;

        // wait for MPU interrupt or extra packet(s) available

#ifdef ARDUINO_BOARD
        while (!mpuInterrupt && fifoCount < packetSize) {}
#endif
#ifdef GALILEO_BOARD
        delay(10);
#endif

        // reset interrupt flag and get INT_STATUS byte
        mpuInterrupt = false;
        mpuIntStatus = mpu.getIntStatus();

        // get current FIFO count
        fifoCount = mpu.getFIFOCount();

        // check for overflow (this should never happen unless our code is too inefficient)
        if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
            // reset so we can continue cleanly
            mpu.resetFIFO();
            LOG("FIFO overflow!");

            // otherwise, check for DMP data ready interrupt (this should happen frequently)
        }
        else if (mpuIntStatus & 0x02) {
            // wait for correct available data length, should be a VERY short wait
            while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

            // read a packet from FIFO
            mpu.getFIFOBytes(fifoBuffer, packetSize);

            // track FIFO count here in case there is > 1 packet available
            // (this lets us immediately read more without waiting for an interrupt)
            fifoCount -= packetSize;


#ifdef OUTPUT_READABLE_YAWPITCHROLL
            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            Serial.print("ypr\t");
            Serial.print(ypr[0] * 180 / M_PI);
            Serial.print("\t");
            Serial.print(ypr[1] * 180 / M_PI);
            Serial.print("\t");
            Serial.println(ypr[2] * 180 / M_PI);
#endif

            // blink LED to indicate activity
            blinkState = !blinkState;
            digitalWrite(LED_PIN, blinkState);
        }
    }
}
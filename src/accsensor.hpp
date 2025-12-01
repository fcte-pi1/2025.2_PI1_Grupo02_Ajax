// juliettcharlieindiaindiahotelnovember. 
// accsensor.hpp handles the mpu6050 sensor using adafruit's library

#ifndef ACCSENSOR_HPP
#define ACCSENSOR_HPP

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

namespace accsensor{
    Adafruit_MPU6050 mpu;
    float rotation{ };

    void setupmpu(void) {
        // Try to initialize!
        if (!mpu.begin()) {
            Serial.println("Failed to find MPU6050 chip");
        }

        mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
        mpu.setGyroRange(MPU6050_RANGE_2000_DEG);
        mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

        Serial.println("[INFO] MPU inicializado com sucesso.");

        delay(100);
    }

    void read(){
        /* Get new sensor events with the readings */
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);

        if (abs(g.gyro.z) > 0.008) {
            rotation += g.gyro.z;
        }
    }

    void reset() {
        rotation = 0.f;
    }
}

#endif
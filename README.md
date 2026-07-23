**HARDWARE**

ESP32-S3

MPU6050

**LIBARY**

Wire.h

**PINOUT**

VCC to 3.3v

GND to GND

SDA to GPIO 8

SCL to GPIO 9

PS

*Don't move the sensor while it calibrating, it calculate the average gyro drift so it can be used to get the actual angle.

*Here the gyroscope using a complementary filter for sensor fusion, feel free to change it to kalman filter using libary to get more stable gyroscpe.

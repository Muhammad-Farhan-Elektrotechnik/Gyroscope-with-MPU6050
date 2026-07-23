**HARDWARE**

ESP32-S3

MPU6050

**LIBARY**

Wire.h

PS

*Don't move the sensore while it calibrating, it calculate the average gyrodrift so it can be used to get the actual angle.

*Here the gyroscope using a complementary filter for sensor fusion, feel free to change it to kallman filter using libary to get more stable gyroscpe.

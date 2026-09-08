# Introductiion
There are different type of IMU, in this case MPU6050 will be used. Inside MPU6050 there are built in sensors like accelerometer and gyrometer. These 2 sensors can work together and act like a gyrometer with help of sensor fusion. The raw data will have noise, therefore a filter is needed to minimize uncertainty. In this case complementary filter will be more specified, but of course there are more type of filters, like kalmann filter. In this repository will also be focused to the communication protocol used namely I2C.


## Hardware
* ESP32-S3
* MPU6050
* Resistor
* Jumper Wire
  
### PINOUT
ESP32-S3 | MPU6050
-------- | -------
3.3v     | VCC
GND      | GND
SDA (I2C)     | GPIO 8
SCL (I2C)     | GPIO 9

More About I2C
------------------------------------
I2C (stands for Inter-Integrated Circuit) is a communication protocol with only 2 wires SDA (Serial Data), SCL (Serial Clock) but unlike other communication protocol like UART, I2C could have more masters and multiple slaves.

> [!IMPORTANT]
> Because I2C chips use open-drain outputs, they can only pull the lines down to ground. Without pull-up resistors connected to Vcc
> the SDA and SCL lines would float indefinitely after being pulled low, meaning the bus would never return to a logic HIGH state and communication would not be able to start.
<img width="616" height="292" alt="image" src="https://github.com/user-attachments/assets/7af87b79-08a3-47ff-a2c1-ca58d3faed79" />

>[!NOTE]
> MPU6050 has built in pull up resistors

<img width="168" height="82" alt="image" src="https://github.com/user-attachments/assets/51e5cd15-a83e-4da6-9bf0-1557f60bf57b" />


But how do the master identified each slaves with only 2 wires? Each of the slaves have their own unique address, these addresses will be used to identify them after the master sends a start condition. Think its like a teacher called one of the students to go upfront and talk to them. When the slaves already identified, the master could write or read data from them but after that, the master have to sends a stop condition in order other master to communicate with that slave. Because of that I2C is not fast as SPI.

More About Sensor Fusion and Complementary Filter
-----------------------------------------------------------
Sensor fusion is combining data from different sensors to get more accurate and reliable information. In many cases the data will have noise and produce an uncertain data, therefore a filter is used. 
Complementary filter formula

$$\text{Angle} = \alpha \cdot (\text{Angle} + \text{GyroData} \cdot dt) + (1 - \alpha) \cdot \text{AccelAngle}$$

where K usually set as 0.98. Because K is a konstant and the program can't filter out noises in extreme condition.



>[!IMPORTANT]
>Don't move the sensor while it calibrating, it calculate the average gyro drift so it can be used to get the actual angle.

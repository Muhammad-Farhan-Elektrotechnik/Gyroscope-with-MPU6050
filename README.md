# Introductiion
There are different type of IMU, in this case MPU6050 will be used. Inside MPU6050 there are built in sensors like accelerometer and gyrometer. These 2 sensors can work together and act like a gyrometer with help of sensor fusion. The raw data will have noise, therefore a filter is needed to minimize uncertainty. In this case complementary filter will be more specified, but of course there are more type of filters, like kalmann filter. In this repository will also be focused to the communication protocol used namely I2C.


## Hardware
* Arduino uno R3
* MPU6050
* Jumper Wire
  
### PINOUT
Arduino uno R3 | MPU6050
-------- | -------
3.3v     | VCC
GND      | GND
A4    | SDA (I2C) 
A5   | SCL (I2C) 

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

Here are the image of how does SDA and SCL signal looks like.

<img width="1246" height="383" alt="image" src="https://github.com/user-attachments/assets/fa5a256f-8fc3-4c22-a41d-1ff6289e46c4" />
both SDA and SCL starts or idling at HIGH (1).

-------------------------------------------------------------------------------------------------------------------------------------------------------
1. It will entering start condition when SDA pulled down to LOW (0) and SCL still at HIGH (1).
<img width="195" height="329" alt="image" src="https://github.com/user-attachments/assets/6260cd8e-3295-4ce0-a32f-a9329bac4c9f" />

-------------------------------------------------------------------------------------------------------------------------------------------------------
2. After entering start conditon, it'll be required 7 bits long unique address.
<img width="337" height="382" alt="image" src="https://github.com/user-attachments/assets/ea1b6cd0-e7c5-49a0-9da0-3384034c6c65" />

-------------------------------------------------------------------------------------------------------------------------------------------------------
3. Then the master decide if it want to write or read, with LOW (0) for write and HIGH (1) for read.
      <img width="337" height="382" alt="image" src="https://github.com/user-attachments/assets/46866a73-fb21-41df-8dde-bd06a4bbdbf0" />
-------------------------------------------------------------------------------------------------------------------------------------------------------
4. Everytime slave addressed and data bytes sended will be followed by ACK/NACK bit (ackknowledge/not ackknowledge) LOW (0) for ACK and HIGH (1) for NACK. ACK means that the bus is used by the slave or the data recieved, otherwise NACK will recall I2C back to HIGH (1).
      <img width="49" height="332" alt="image" src="https://github.com/user-attachments/assets/044a725e-bb15-4ced-abe8-a3fc4192332c" />
-------------------------------------------------------------------------------------------------------------------------------------------------------
5. Here is data byte (followed by ACK bit), where the data will be send or recieved according to read or write.
      <img width="434" height="368" alt="image" src="https://github.com/user-attachments/assets/41f08d5b-2008-41c5-8f5f-f73c71c39b4a" />
>[!NOTE]
>data byte is not specifically to write or read data, but it can also addresses another slave and read or write it in the next data byte.
-------------------------------------------------------------------------------------------------------------------------------------------------------
6. SDA only changes when SCL at LOW (0)
      <img width="985" height="278" alt="image" src="https://github.com/user-attachments/assets/e77c1b33-d9d9-4a8e-b556-4ceb955ca3f5" />
-------------------------------------------------------------------------------------------------------------------------------------------------------
7. Otherwise it'll be at a stop condition
<img width="109" height="285" alt="image" src="https://github.com/user-attachments/assets/0f63b26c-69d5-47eb-8406-c228b7a9df82" />

>[!TIP]
>Highly reccomend to check out the video that explained it [here](https://youtu.be/CAvawEcxoPU?si=tvXQgaJvQCcI6Zlu)

-------------------------------------------------------------------------------------------------------------------------------------------------------

More About Sensor Fusion and Complementary Filter
-----------------------------------------------------------
Sensor fusion is combining data from different sensors to get more accurate and reliable information. In many cases the data will have noise and produce an uncertain data, therefore a filter is used. 
Complementary filter formula

$$\text{Angle} = \alpha \cdot (\text{Angle} + \text{GyroData} \cdot dt) + (1 - \alpha) \cdot \text{AccelAngle}$$

where $$\alpha$$ usually set as 0.98. Because $$\alpha$$ is a konstant and the program can't filter out noises in extreme condition.



>[!IMPORTANT]
>Don't move the sensor while it calibrating, it calculate the average gyro drift so it can be used to get the actual angle.

DOCUMENTATION
---------------
<img width="354" height="335" alt="image" src="https://github.com/user-attachments/assets/56f1e0f3-5883-4f1d-a1f9-7db7c67e45a6" />


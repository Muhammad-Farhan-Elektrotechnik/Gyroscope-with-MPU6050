#include <Wire.h> 


const int MPU_ADDR = 0x68;


int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;


float gyroXoffset = 0, gyroYoffset = 0, gyroZoffset = 0;


float pitch = 0.0, roll = 0.0;


unsigned long prevTime;
float dt;

void setup() {
  Wire.begin();
  Serial.begin(9600);

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  delay(1000);
  prevTime=millis();
  calibrateGyro();
}

void loop() {
  unsigned long currentTime = millis();
  dt = (currentTime - prevTime) / 1000.0;
  prevTime = currentTime;


  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  
  if(Wire.requestFrom(MPU_ADDR, 14, true)==14){

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  Wire.read(); Wire.read(); 
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();
  } else{
    Serial.println("Reading error!");
  }
 
  float gyroXrate = (GyX - gyroXoffset) / 131.0;
  float gyroYrate = (GyY - gyroYoffset) / 131.0;


  float accelRoll = atan2(AcY, AcZ) * 180 / PI;
  float accelPitch  = atan2(-AcX, AcZ) * 180 / PI;


  pitch = 0.98 * (pitch + gyroYrate * dt) + 0.02 * accelPitch;
  roll  = 0.98 * (roll + gyroXrate * dt) + 0.02 * accelRoll;


  
  Serial.print("Pitch: ");  Serial.println(pitch);
  Serial.print("Roll: "); Serial.println(roll);

  delay(10);
}

void calibrateGyro() {
  const float samples = 2000.0;
  long gx = 0, gy = 0, gz = 0;
Serial.println("Calibrating...dont move");
  for (int i = 0; i < samples; i++) {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x43);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 6, true);

    int16_t GyX = Wire.read() << 8 | Wire.read();
    int16_t GyY = Wire.read() << 8 | Wire.read();
    int16_t GyZ = Wire.read() << 8 | Wire.read();

    gx += GyX;
    gy += GyY;
    gz += GyZ;
  }

  gyroXoffset = gx / samples;
  gyroYoffset = gy / samples;
  gyroZoffset = gz / samples;
Serial.println("Calibrated!");
  
}
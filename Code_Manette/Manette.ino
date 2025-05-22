// Joystick 1
#define VRx1 4
#define VRy1 3
#define SW1  2

// Joystick 2
#define VRx2 9
#define VRy2 8
#define SW2  7

#include <Wire.h>//https://www.arduino.cc/en/reference/wire
#include <Adafruit_MPU6050.h>//https://github.com/adafruit/Adafruit_MPU6050
#include <Adafruit_Sensor.h>//https://github.com/adafruit/Adafruit_Sensor

//Objects
Adafruit_MPU6050 mpu;


void setup() {
  Serial.begin(115200);

  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);

  Serial.println(F("Initialize System"));
 if (!mpu.begin(0x68)) { // Change address if needed
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  // Lecture joystick 1
  int x1 = analogRead(VRx1);
  int y1 = analogRead(VRy1);
  bool pressed1 = digitalRead(SW1) == LOW;

  // Lecture joystick 2
  int x2 = analogRead(VRx2);
  int y2 = analogRead(VRy2);
  bool pressed2 = digitalRead(SW2) == LOW;

  // Affichage
  Serial.print("Joy1 -> X:");
  Serial.print(x1);
  Serial.print(" Y:");
  Serial.print(y1);
  Serial.print(" Btn:");
  Serial.print(pressed1 ? "Appuyé" : "Relâché");

  Serial.print(" || Joy2 -> X:");
  Serial.print(x2);
  Serial.print(" Y:");
  Serial.print(y2);
  Serial.print(" Btn:");
  Serial.println(pressed2 ? "Appuyé" : "Relâché");

  readMPU();

  delay(200);


}

void readMPU( ) { /* function readMPU */
  ////Read acceleromter data
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println("°C");
}
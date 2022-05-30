#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  #include "Wire.h"
#endif

WiFiMulti wifiMulti;
MPU6050 mpu;
TaskHandle_t Task1;

// Wifi
String dt[4];
char command;
char command_send;
String server_time;

// SD Card
#define SD_CS 5
String dataMessage;

// LED biru ESP32
const int ledPin = 2;
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
int dutyCycle = 0;

// MPU control/status vars
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

float pitch;
float roll;
float inc_angle;

bool start = false; // Kondisi menghitung nilai puncak (iya atau tidak)

// Peak calc
float inc_angle_peak;

// PID Calibration
int pidCal_http;
int pidCal_send;
float axOff;
float ayOff;
float azOff;
float gxOff;
float gyOff;
float gzOff;

// Sub Calibration (accWorld & Angle)
int subCal;
int subCal_http;
int subCal_send;
int count;
double pitch_offset = 0;
double roll_offset = 0;

void setup() {
  Serial.begin(115200);

  wifiMulti.addAP("Hanif Maliki", "hanifmlk");
//  wifiMulti.addAP("Hanip", "bismillah");

  IMU_Setup();

  // LED biru ESP32
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ledPin, ledChannel);

  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */
  delay(500);
}

void Task1code( void * pvParameters ) {
  for(;;){
    komunikasi_http(); // Command menggunakan GUI Wifi
  }
}

void loop() {
//  command = Serial.read(); // Command menggunakan serial monitor

  if(command=='q') start = true; // Start menghitung puncak & fuzzy
  if(command=='a') start = false; // Stop menghitung puncak & fuzzy
  if(command=='w') peak_reset(); // Reset nilai puncak & fuzzy
  if(command=='t') sub_calibration(); // Kalibrasi nilai akhir dengan pengurangan rata2
  if(command=='g') pid_calibration(); // Kalibrasi nilai raw acc & gyro dengan PID
  if(command=='y') calibration_reset(); // Reset hasil sub_calibration

//  if(command=='c') pga_dr1 += 0.0001; // Mencoba fuzzy logic
//  if(command=='v') pga_dr1 += 0.001;
//  if(command=='b') pga_dr1 += 0.01;
//  if(command=='n') pga_dr1 += 0.1;

  IMU_Calc();

  if (start==true) {peak_calc();}

//  print_Data();
}

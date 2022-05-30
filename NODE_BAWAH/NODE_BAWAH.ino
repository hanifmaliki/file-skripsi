#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include "FS.h"
#include "SD.h"
#include <SPI.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  #include "Wire.h"
#endif

WiFiMulti wifiMulti;
MPU6050 mpu;
TaskHandle_t Task1;

// Wifi
String dt[5];
char command;
char command_send;
String server_time;
float top_angle_peak;

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
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 gyro;       // [x, y, z]            gyroscope sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

float accX;
float accY;
float accZ;
float accRealX;
float accRealY;
float accRealZ;
float accWorldX;
float accWorldY;
float accWorldZ;
float pitch;
float roll;
float ground_acc;
float inc_angle;

// for displacement & drift ratio
float inc_angle_rad;
float h = 284; // tinggi dinding (cm)
float displacement;
float drift_ratio;

bool start = false; // Kondisi menghitung nilai puncak & fuzzy (iya atau tidak)

// Peak calc
float pga;
float inc_angle_peak;
float displacement_peak;
float drift_ratio_peak;

// Fuzzy Logic
float pga_dr1;
float pga_dr1_lama;
float x,a,b,c,d;
float sig[5];
float z0,z1,z2,z3,z4;
float score;

// PID Calibration
int pidCal;
// Sub Calibration (accWorld & Angle)
int subCal;
int count;
double accWorldX_offset = 0;
double accWorldY_offset = 0;
double accWorldZ_offset = 0;
double pitch_offset = 0;
double roll_offset = 0;

void setup() {
  Serial.begin(115200);

  wifiMulti.addAP("Hanif Maliki", "hanifmlk");
//  wifiMulti.addAP("Hanip", "bismillah");

  SD_Setup();

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
    if(command=='a') logSDCard(); // Simpan data di SD Card
  }
}

void loop() {
//  command = Serial.read(); // Command menggunakan serial monitor

  if(command=='q') start = true; // Start menghitung puncak & fuzzy
  if(command=='a') start = false; // Stop menghitung puncak & fuzzy
  if(command=='w') {peak_reset(); fuzzy_reset();} // Reset nilai puncak & fuzzy
  if(command=='e') sub_calibration(); // Kalibrasi nilai akhir dengan pengurangan rata2
  if(command=='d') pid_calibration(); // Kalibrasi nilai raw acc & gyro dengan PID
  if(command=='r') calibration_reset(); // Reset hasil sub_calibration

//  if(command=='v') pga_dr1 += 0.0001;
//  if(command=='b') pga_dr1 += 0.001;
//  if(command=='n') pga_dr1 += 0.01;
//  if(command=='m') pga_dr1 += 0.1;
//
//  if(command=='h') pga_dr1 -= 0.0001;
//  if(command=='j') pga_dr1 -= 0.001;
//  if(command=='k') pga_dr1 -= 0.01;
//  if(command=='l') pga_dr1 -= 0.1;

  IMU_Calc();

  if (start==true) {peak_calc(); fuzzy_start();}

//  print_Data();

//  if (pga_dr1!=pga_dr1_lama){
//    Serial.print(pga_dr1,4);
//    Serial.print("\t");
//    Serial.println(score);
//  }
//  pga_dr1_lama = pga_dr1;
}

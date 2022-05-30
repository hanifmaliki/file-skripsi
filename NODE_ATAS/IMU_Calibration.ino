void pid_calibration(void)
{
  mpu.CalibrateAccel(20);
  mpu.CalibrateGyro(20);
  
  axOff=mpu.getXAccelOffset();
  ayOff=mpu.getYAccelOffset();
  azOff=mpu.getZAccelOffset();
  gxOff=mpu.getXGyroOffset();
  gyOff=mpu.getYGyroOffset();
  gzOff=mpu.getZGyroOffset();
  
  pidCal_http = 1;
}

void sub_calibration(void)
{
  subCal = 1;

  pitch_offset = 0;
  roll_offset = 0;

  count = 0;
  unsigned long time_cal = millis();

  while((millis()-time_cal) <= 3000) // lama kalibrasi dalam 3s
  {
    IMU_Calc();

    Serial.print(pitch);
    Serial.print("\t");
    Serial.print(roll);
    Serial.print("\t");
    Serial.print(count);
    Serial.println("\tKALIBRASI");
  }
  subCal = 0;

  pitch_offset = pitch_offset/count;
  roll_offset = roll_offset/count;
  
  Serial.print(pitch_offset);
  Serial.print("\t");
  Serial.print(roll_offset);
  Serial.print("\t");
  Serial.print(count);
  Serial.println("\tKALIBRASI SELESAI");
}

void calibration_reset(void)
{
  pitch_offset = 0;
  roll_offset = 0;
}

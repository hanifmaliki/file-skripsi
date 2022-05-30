void pid_calibration(void)
{
  pidCal = 1;
  mpu.CalibrateAccel(20);
  mpu.CalibrateGyro(20);
  logSDCard();
  pidCal = 0;
}

void sub_calibration(void)
{
  subCal = 1;

  accWorldX_offset = 0;
  accWorldY_offset = 0;
  accWorldZ_offset = 0;
  pitch_offset = 0;
  roll_offset = 0;

  count = 0;
  unsigned long time_cal = millis();

  while((millis()-time_cal) <= 3000) // lama kalibrasi dalam 3s
  {
    IMU_Calc();

    Serial.print(accWorldX);
    Serial.print("\t");
    Serial.print(accWorldY);
    Serial.print("\t");
    Serial.print(accWorldZ);
    Serial.print("\t");
    Serial.print(pitch);
    Serial.print("\t");
    Serial.print(roll);
    Serial.print("\t");
    Serial.print(count);
    Serial.println("\tKALIBRASI");
  }
  subCal = 0;

  accWorldX_offset = accWorldX_offset/count;
  accWorldY_offset = accWorldY_offset/count;
  accWorldZ_offset = accWorldZ_offset/count;
  pitch_offset = pitch_offset/count;
  roll_offset = roll_offset/count;

  Serial.print(accWorldX_offset);
  Serial.print("\t");
  Serial.print(accWorldY_offset);
  Serial.print("\t");
  Serial.print(accWorldZ_offset);
  Serial.print("\t");
  Serial.print(pitch_offset);
  Serial.print("\t");
  Serial.print(roll_offset);
  Serial.print("\t");
  Serial.print(count);
  Serial.println("\tKALIBRASI SELESAI");
}

void calibration_reset(void)
{
  accWorldX_offset = 0;
  accWorldY_offset = 0;
  accWorldZ_offset = 0;
  pitch_offset = 0;
  roll_offset = 0;
}

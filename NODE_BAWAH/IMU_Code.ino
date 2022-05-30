void IMU_Setup(void)
{
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin();
    Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true);
  #endif

  // initialize device
  Serial.println(F("Initializing I2C devices..."));
  mpu.initialize();

  // verify connection
  Serial.println(F("Testing device connections..."));
  Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

  // load and configure the DMP
  Serial.println(F("Initializing DMP..."));
  devStatus = mpu.dmpInitialize();

  // supply your own gyro offsets here, scaled for min sensitivity
  mpu.setXGyroOffset(118);
  mpu.setYGyroOffset(-5);
  mpu.setZGyroOffset(-17);
  mpu.setXAccelOffset(0);
  mpu.setYAccelOffset(0);
  mpu.setZAccelOffset(0);

  // make sure it worked (returns 0 if so)
  if (devStatus == 0) {
    // Calibration Time: generate offsets and calibrate our MPU6050
    mpu.CalibrateAccel(20);
    mpu.CalibrateGyro(20);
    mpu.PrintActiveOffsets();
    // turn on the DMP, now that it's ready
    Serial.println(F("Enabling DMP..."));
    mpu.setDMPEnabled(true);
  }
  else {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));
  }
}

void IMU_Calc(void)
{
  // read a packet from FIFO
  if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) { // Get the Latest packet
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetAccel(&aa, fifoBuffer);
    mpu.dmpGetGyro(&gyro, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
    mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    accX = float(aa.x)/8192;
    accY = float(aa.y)/8192;
    accZ = float(aa.z)/8192;
    accRealX = float(aaReal.x)/8192;
    accRealY = float(aaReal.y)/8192;
    accRealZ = float(aaReal.z)/8192;
    accWorldX = float(aaWorld.x)/8192;
    accWorldY = float(aaWorld.y)/8192;
    accWorldZ = float(aaWorld.z)/8192;
    pitch = -ypr[1]*180/M_PI; // AngleY
    roll = ypr[2]*180/M_PI; // AngleX

    if (subCal==0) {
      accWorldX -= accWorldX_offset;
      accWorldY -= accWorldY_offset;
      accWorldZ -= accWorldZ_offset;
      pitch -= pitch_offset; // AngleY
      roll -= roll_offset; // AngleX
    }
    if (subCal==1) {
      accWorldX_offset += accWorldX;
      accWorldY_offset += accWorldY;
      accWorldZ_offset += accWorldZ;
      pitch_offset += pitch;
      roll_offset += roll;
      count++;
    }

    ground_acc = accWorldZ;
    inc_angle = roll;

    inc_angle_rad = inc_angle/(180/M_PI);
    displacement = sqrt(pow(h,2)-pow(h*cos(inc_angle_rad),2)); // memakai roll
      if (inc_angle_rad<0) displacement=displacement*(-1);
    drift_ratio = displacement/h*100;

    dutyCycle = 10; // terang LED biru 0-255
    ledcWrite(ledChannel, dutyCycle);

    print_Data();
  }
  else {
    if (dutyCycle>0) dutyCycle--;
    ledcWrite(ledChannel, dutyCycle);
  }
}

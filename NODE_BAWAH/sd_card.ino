void SD_Setup(void)
{
  // Initialize SD card
  SD.begin(SD_CS);
  if(!SD.begin(SD_CS)) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();
  if(cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }
  Serial.println("Initializing SD card...");
  if (!SD.begin(SD_CS)) {
    Serial.println("ERROR - SD card initialization failed!");
    return; // init failed
  }

  File file = SD.open("/data.txt");
  if(!file) {
    Serial.println("File doens't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/data.txt", "Data Logging--- \r\n");
  }
  else {Serial.println("File already exists");}
  file.close();

  File file2 = SD.open("/calib.txt");
  if(!file2) {
    Serial.println("File doens't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/calib.txt", "Offset Calibration--- \r\n");
  }
  else {Serial.println("File already exists");}
  file2.close();
}

void logSDCard() {
  if (pidCal==0) {
    dataMessage = server_time + "\tPGA=" + String(pga,4) + "g\tBotAngle=" + String(inc_angle_peak,3)
                + "°\tTopAngle=" + String(top_angle_peak,3) + "°\tH=" + String(h) + " cm\tDisplacement=" + String(displacement_peak)
                + " cm\tDrift=" + String(drift_ratio_peak,3) + "%\tPGA at DR 1%=" + String(pga_dr1,4) +"g\tScore=" + String(score) + "\r\n";
  }
  if (pidCal==1) {
    dataMessage = server_time + "\tBOT CALIBRATION\tAccOffsetX=" + String(mpu.getXAccelOffset()) + "\tAccOffsetY=" + String(mpu.getYAccelOffset())
                + "\tAccOffsetZ=" + String(mpu.getZAccelOffset()) + "\tGyroOffsetX=" + String(mpu.getXGyroOffset())
                + "\tGyroOffsetY=" + String(mpu.getYGyroOffset()) + "\tGyroOffsetZ=" + String(mpu.getZGyroOffset()) + "\r\n";
  }
  Serial.print("Save data: ");
  Serial.println(dataMessage);
  if (pidCal==0) appendFile(SD, "/data.txt", dataMessage.c_str());
  if (pidCal==1) appendFile(SD, "/calib.txt", dataMessage.c_str());
}

void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print(message)) {Serial.println("File written");}
    else {Serial.println("Write failed");}
  file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if(!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if(file.print(message)) {Serial.println("Message appended");}
    else {Serial.println("Append failed");}
  file.close();
}

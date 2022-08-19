/*

  IMU

*/

long imuTimer     = 0;
int imuThreshold  = 250 / CLOCK_DIVIDER;

void initializeIMU() {
  Serial1.printf("Initializing IMU: ");
  
  pixels.setPixelColor(1, pixels.Color(0, 255, 0));
  pixels.show();

  delay(250 / CLOCK_DIVIDER);

  int mpuStatus = mpu.begin();

  if (mpuStatus != 0) {
    Serial1.printf("Failed! Error code: ");
    Serial1.println(mpuStatus);
    while(1);
  }
  Serial1.printf("Complete \r\n");

  Serial1.printf("Configuring IMU: ");
  delay(250 / CLOCK_DIVIDER);
  mpu.calcOffsets(true, true);
  delay(250 / CLOCK_DIVIDER);
  Serial1.printf("Complete \r\n");  
}

// Read IMU
void readIMU() {
  if (millis() - imuTimer > imuThreshold) {
    switchMCUState(fast);
    mpu.update();
    currTemp = mpu.getTemp();
    currAngle = mpu.getAngleZ();
    switchMCUState(slow);

//    Serial1.printf("==== IMU UPDATE ==== \r\n");
//    Serial1.printf("Temperature: ");
//    Serial1.println(currTemp);
//    Serial1.printf("Angle: ");
//    Serial1.println(currAngle);
//    Serial1.printf("==================== \r\n");
//    Serial1.println();

    imuTimer = millis();
  }
}

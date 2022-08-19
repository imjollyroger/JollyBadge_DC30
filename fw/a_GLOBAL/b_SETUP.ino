/*

  SETUP

  Notes:
    - Even though it's not implemented yet, we need something to handle slower cpu timers

*/

void setup() {
  GCLK->GENDIV.reg = GCLK_GENDIV_DIV(1) | GCLK_GENDIV_ID(0);
  
  Serial1.begin(115200);
  delay(10);
  Serial1.printf("Intializing JollyBadge_DC30... \r\n");
  
  Wire.begin();

  // Initialize Light Ring
  initializePixels();

  // Setup NFC
  initializeNFC();

  // delay(500);
  
  // Setup IMU
  // initializeIMU();

  // Set current state
  initializeGameState();

  // Slow clock speed
  switchMCUState(slow);
}

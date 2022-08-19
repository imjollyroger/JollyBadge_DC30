/*

  LOOP

*/

void loop() {
  readNFC();
  // readIMU();

  if (!pauseChecks) {
    checkForPuzzleSolve();
    performCurrentGameState();
  }
  
  performAnimationIfNecessary();
}

/*
  Puzzle:     Spin
  Objective:  Using the IMU get the rotation of the device. Use the lights to
              guide the user into making 3 full rotations of the device.

  Note:       Shouldn't matter which direction the user rotates
*/

void performSpinPuzzle() {
  // Show the waiting animation
  setCurrentAnimationState(none);
  
  // Set the angle target for the puzzle
  if (targetAngle == 0.0) {
    targetAngle = 360.0 * 3.0;
  }

  // Get some base values
  float segmentSize = 360.0 / (float)PIXEL_NUM;
  int currRotations = currAngle / 360;
  float fixedValue = currAngle - (currRotations * 360.0);

  // Set LEDs for current progress
  for (int i = 0; i < PIXEL_NUM; i++) {
    int r = 0, g = 0, b = 0;

    if (fixedValue > (i * segmentSize)) {
      if (currRotations == 0) {
        r = 255;
      } else if (currRotations == 1) {
        r = 255;
        g = 255;
      } else if (currRotations == 2) {
        g = 255;
      }
    } else {
      if (currRotations == 1) {
        r = 255;
      } else if (currRotations == 2) {
        r = 255;
        g = 255;
      }
    }

    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
  
  showPixels();

  // Check for win
  if (currAngle >= targetAngle) {
    // playSuccessAnimation();
    nextState();
  }
}

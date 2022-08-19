/*
  Puzzle:     Temperature
  Objective:  Using the IMU temperature, attempt to get it 3 more degrees above.
              Colored lights will help guide the way.
*/
void performTemperaturePuzzle() {
  // Show the waiting animation
  setCurrentAnimationState(none);
  
  // Set the temperature target for the puzzle
  if (targetTemp == 0.0) {
    targetTemp = currTemp + 3.0;
  }

  // Set lights based on temperature
  int r, g, b;
  float tempDiff = targetTemp - currTemp;

  if (tempDiff >= 2.0) {
    r = 255; g = 0; b = 0;
  } else if (tempDiff >= 0.5) {
    r = 255; g = 255; b = 0;
  } else if (tempDiff > 0.0) {
    r = 0; g = 255; b = 0;
  } else if (tempDiff <= 0.0) {
    r = 0; g = 0; b = 255;
  }

  for (int i = 0; i < PIXEL_NUM; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
  
  showPixels();

  // Check for win
  if (tempDiff <= 0.0) {
    // playSuccessAnimation();
    nextState();
  }
}

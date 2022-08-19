/*

  Puzzle:     Binary Puzzle
  Objective:  Show a text string as binary

*/

long binaryTimer = 0;
int binaryThreshold = 0;
String binaryText = "36.11960, -115.16782";
int binarySteps = 0;
int binaryOffset = 0;
bool binaryUp = true;
bool binaryPause = false;

void performBinaryPuzzle() {
  if (millis() - binaryTimer > binaryThreshold) {
    if (!didWriteHint) {
      String s = "Beep boop beep... where is this?";
      currentHint = s;
      writeNFC(s);
      didWriteHint = true;
    }

    if (binaryPause) {
      pixels.clear();
      showPixels();

      binaryThreshold = 500 / CLOCK_DIVIDER;
      binaryPause = false;
      binaryTimer = millis();

      return;
    }

    if (binaryOffset == binaryText.length()) {
      binaryOffset = 0;
      return;
    }

    binaryThreshold = 50 / CLOCK_DIVIDER;

    // Convert character
    // Set colors
    //Serial1.print("PIXELS[");
    //Serial1.print(binaryOffset);
    //Serial1.print("]: ");

    int offsetTracker = 0;
    for (int i = PIXEL_NUM; i > 0; i--) {
      byte bytes = bitRead(binaryText.charAt(binaryOffset), i - 1);

      if (int(bytes) == 0) {
        //Serial1.print("0");
        pixels.setPixelColor(pixelOffset(offsetTracker), pixels.Color(0, 0, 0));
      } else if (int(bytes) == 1) {
        //Serial1.print("1");
        pixels.setPixelColor(pixelOffset(offsetTracker), pixels.Color(255, 255, 255));
      }

      offsetTracker++;
    }

    //Serial1.println();

    if (binarySteps == PIXEL_BRIGHTNESS) {
      binaryUp = false;
    }

    // Set brightness and show
    binarySteps = binaryUp ? binarySteps + 1 : binarySteps - 1;
    pixels.setBrightness(binarySteps);
    showPixels();

    // If we're animated a full loop move on to next character
    if (binarySteps == 0) {
      binaryOffset++;
      binaryPause = true;
      binaryUp = true;
    }

    binaryTimer = millis();
  }
}

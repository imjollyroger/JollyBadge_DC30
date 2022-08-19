/*

  MORSE CODE

*/

long morseTimer = 0;
int morseThreshold = 0;

int morseUnitLength = 200;
int morseDotLength = 1 * morseUnitLength;
int morseDashLength = 3 * morseUnitLength;
int morseInnerLength = 1 * morseUnitLength;
int morseSpaceLength = 3 * morseUnitLength;
int morseSlashLength = 7 * morseUnitLength;

String morseText = ".... .- -.-. -.- / - .... . / .--. .-.. .- -. . - -.-.--"; // HACK THE PLANET!
int morseOffset = 0;
bool morsePause = false;

void performMorsePuzzle() {
  if (millis() - morseTimer > morseThreshold) {
    if (!didWriteHint) {
      String s = "Blinky blinky!";
      currentHint = s;
      writeNFC(s);
      didWriteHint = true;
    }
    
    if (morsePause) {
      pixels.clear();
      showPixels();

      morseThreshold = morseInnerLength / CLOCK_DIVIDER;
      morsePause = false;
      morseTimer = millis();

      return;
    }

    if (morseOffset == morseText.length()) {
      morseOffset = 0;
      return;
    }

    char morseChar = morseText.charAt(morseOffset);
    bool skipShow = false;
    if (morseChar == '.') {
      morseThreshold = morseDotLength / CLOCK_DIVIDER;
    }
    if (morseChar == '-') {
      morseThreshold = morseDashLength / CLOCK_DIVIDER;
    }
    if (morseChar == ' ') {
      morseThreshold = morseSpaceLength / CLOCK_DIVIDER;
      skipShow = true;
    }
    if (morseChar == '/') {
      morseThreshold = morseSlashLength / CLOCK_DIVIDER;
      skipShow = true;
    }

    if (!skipShow) {
      for (int i = 0; i < PIXEL_NUM; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 255, 255));
      }
    } else {
      pixels.clear();
    }

    showPixels();

    morseOffset++;
    morsePause = true;
    morseTimer = millis();
  }
}

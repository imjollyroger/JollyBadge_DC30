/*

  Animations

*/

AnimationState currentAnimationState = none;

void initializePixels() {
  pixels.begin();
  pixels.clear();
  pixels.setBrightness(PIXEL_BRIGHTNESS);
  pixels.show();
}

void showPixels() {
  switchMCUState(fast);
  pixels.show();  
  switchMCUState(slow);
}

int pixelOffset(int index) {
  return ((index + 1) + PIXEL_OFFSET) <= PIXEL_NUM ? index + PIXEL_OFFSET : (index + PIXEL_OFFSET) - PIXEL_NUM;
}

void setCurrentAnimationState(AnimationState state) {
  if (currentAnimationState == state) {
    return;
  }

  delay(25 / CLOCK_DIVIDER);

  currentAnimationState = state;
}

void performAnimationIfNecessary() {
  switch (currentAnimationState) {
    case (none): {
      pauseState = false;
      pauseChecks = false;
      break;  
    }
    case (pulse): {
      pulseColor(pixels.Color(255, 255, 255));
      break;  
    }
    case (success): {
      pauseState = true;
      flashColor(pixels.Color(0, 255, 0));
      break;  
    }
    case (failure): {
      pauseState = true;
      flashColor(pixels.Color(255, 0, 0));
      break;  
    }
    case (aComplete): {
      pulseColor(pixels.Color(0, 255, 0));
      break;  
    }
    case (bling): {
      pauseState = true;
      showBlinkyAnimation();
      break;  
    }
  }
}

int pulseTimer = 0;
int pulseThreshold = 50 / CLOCK_DIVIDER;
int pulseSteps = 0;
bool pulseUp = true;
void pulseColor(uint32_t color) {
  if (millis() - pulseTimer > pulseThreshold) {
    for (int i = 0; i < PIXEL_NUM; i++) {
      pixels.setPixelColor(i, color);
    }  

    if (pulseSteps == PIXEL_BRIGHTNESS) {
      pulseUp = false;
    }

    pulseSteps = pulseUp ? pulseSteps + 1 : pulseSteps  - 1;

    pixels.setBrightness(pulseSteps);
    showPixels();

    if (pulseSteps == 0) {
      pulseUp = true;
      currentAnimationState = none;
    }
  
    pulseTimer = millis();
  }
}

int flashTimer = 0;
int flashThreshold = 50 / CLOCK_DIVIDER;
int flashCount = 10;
int flashStep = 0;
void flashColor(uint32_t color) {
  if (millis() - flashTimer > flashThreshold) {   
    flashStep++;
    
    pixels.setBrightness((flashStep & 1) == 0 ? PIXEL_BRIGHTNESS : 0);
    
    for (int i = 0; i < PIXEL_NUM; i++) {
      pixels.setPixelColor(i, color);
    }

    showPixels();

    if (flashStep == flashCount) {
      flashStep = 0;
      currentAnimationState = none;
    }
    
    flashTimer = millis();
  }
}

long blinkyTimer = 0;
long blinkyThreshold = 500 / CLOCK_DIVIDER;
void showBlinkyAnimation() {
  if (millis() - blinkyTimer > blinkyThreshold) {
    for (int i = 0; i < PIXEL_NUM; i++) {
      int r = rand() % 255;
      int g = r > 175 ? rand() % 100 : rand() % 255 + 100;
      int b = g > 175 ? rand() % 100 : rand() % 255 + 200;
      pixels.setPixelColor(i, pixels.Color(r, g, b));
    }

    showPixels();
    
    blinkyTimer = millis();
  }  
}

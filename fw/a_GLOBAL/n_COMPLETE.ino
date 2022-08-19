/*
  
  Puzzle:     Complete
  
*/

long completeTimer     = 0;
int completeThreshold  = 1000 / CLOCK_DIVIDER;

void performCompletePuzzle() {
  if (millis() - completeTimer > completeThreshold) {
    if (!didWriteHint) {
      String s = "Time to find Jolly! DM @IMJOLLYROGER to claim your elixir of victory!";
      currentHint = s;
      writeNFC(s);
      didWriteHint = true;
    }

    // Show the waiting animation
    setCurrentAnimationState(aComplete);
    
    completeTimer = millis();
  }
}

long finalTimer     = 0;
int finalThreshold  = 1000 / CLOCK_DIVIDER;

void performFinalPuzzle() {
  if (millis() - finalTimer > finalThreshold) {
    if (!didWriteHint) {
      String s = "You've completed it all! Congrats! Send RESET to start over!";
      currentHint = s;
      writeNFC(s);
      didWriteHint = true;
    }

    // Show the waiting animation
    setCurrentAnimationState(bling);
    
    finalTimer = millis();
  }
}

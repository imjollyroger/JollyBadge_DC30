/*
  
  Puzzle:     Start Puzzle
  Objective:  Find the NFC, read it, go to the URL and enter the flag
  
*/

long startPuzzleTimer     = 0;
int startPuzzleThreshold  = 1000 / CLOCK_DIVIDER;

void performNFCPuzzle() {  
  if (millis() - startPuzzleTimer > startPuzzleThreshold) {
    // Write puzzle to NFC (base64 string)
    if (!didWriteHint) {
      String s = "You found challenge 1! Write back: HOM3C0MING";
      // String s = "HOM3C0MING";
      currentHint = s;
      writeNFC(s);
      didWriteHint = true;
    }

    // Show the waiting animation
    setCurrentAnimationState(pulse);

    startPuzzleTimer = millis();
  }
}

/*

  Puzzle:     Data Dump Puzzle
  Objective:  Dump the firmware and perform strings on the binary

*/

String dumpPuzzleHint = "Well well well, look at you! Dumping the firmware. Challenge solved (assuming you've completed the others to this point). Submit the flag: CRASH OVERRIDE. Now... dig a little deeper, what else here is hiding something?";

long dumpTimer     = 0;
int dumpThreshold  = 1000 / CLOCK_DIVIDER;

void performDumpPuzzle() {
  if (millis() - dumpTimer > dumpThreshold) {
    if (!didWriteHint) {
      Serial1.println("writing serial hint");
      String s = "You've had delicious serial. Maybe now you should take a dump.";
      currentHint = s;
      writeNFC(s);
      didWriteHint = true;
    }

    // Show the waiting animation
    setCurrentAnimationState(pulse);

    dumpTimer = millis();
  }

}

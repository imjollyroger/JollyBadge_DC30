/*

  Puzzle:     Crypto Puzzle
  Objective:  Offer up a crypto puzzle signed with a key hidden in the instructions website

*/

String jwt = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJjb25mZXJlbmNlIjoiREVGIENPTiIsImxvY2F0aW9uIjoiQ0FFU0FSUyBGT1JVTSIsInN1Ym1pdF9mbGFnIjoiRklOREpPTExZUk9HRVIiLCJmaW5hbF9vYmplY3RpdmUiOiJGSU5EIEBJTUpPTExZUk9HRVIgRk9SIEZJTkFMIEZMQUcgQU5EIFRPIENMQUlNIFlPVVIgRUxJWElSIE9GIFZJQ1RPUlkhIiwiaWF0IjoxNjYwMTc2MDAwfQ.I3gGbtDhmBiZIKCbeaoF7ggAB7An2TUdmMjl1MljZaw";

long cryptoTimer     = 0;
int cryptoThreshold  = 1000 / CLOCK_DIVIDER;

void performCryptoPuzzle() {
  if (millis() - cryptoTimer > cryptoThreshold) {
    if (!didWriteHint) {
      String s = "What else is hiding in that dump?";
      currentHint = s;
      writeNFC(s);
      didWriteHint = true;
    }

    // Show the waiting animation
    setCurrentAnimationState(pulse);
    
    cryptoTimer = millis();
  }
}

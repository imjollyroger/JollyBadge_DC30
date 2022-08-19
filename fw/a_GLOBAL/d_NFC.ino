/*

  NFC

*/

long nfcTimer       = 0;
int nfcThreshold    = 1000 / CLOCK_DIVIDER;

void initializeNFC() {
  Serial1.printf("Initializing RFID: ");

  pixels.setPixelColor(0, pixels.Color(0, 255, 0));
  
  pixels.show();

  delay(125 / CLOCK_DIVIDER);

  int nfcCheck = st25dv.begin(GPO_PIN, LPD_PIN, &WireNFC);
  if (nfcCheck == 0) {
    Serial1.printf("Done! \r\n");
  } else {
    Serial1.printf("Failed! Error code: ");
    Serial1.println(nfcCheck);
    while(1);
  }

  writeNFC("");
}

void writeNFC(String s) {
//  Serial1.printf("Writing string: ");
//  Serial1.println(s);
//  Serial1.println();

  switchMCUState(fast);
  int writeNFC = st25dv.writeText(s.c_str());
  switchMCUState(slow);
  
  if (writeNFC == 0) {
    //Serial1.printf("Done! \r\n");
    currentText = s;
  } else {
    //Serial1.printf("FaIlEd! \r\n");
  }
}

void readNFC() {
  if (millis() - nfcTimer > nfcThreshold) {
    //Serial1.printf("Reading NFC: ");

    String s;

    switchMCUState(fast);
    int readNFC = st25dv.readText(&s);
    switchMCUState(slow);

    if (readNFC == 0) {
      //Serial1.println(s.c_str());
      currentText = s;
    } else {
      //Serial1.printf("FAILED! Error: ");
      //Serial1.println(readNFC);
    }
    
    nfcTimer = millis();
  }
}

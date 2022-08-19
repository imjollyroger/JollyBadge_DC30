/*

  Puzzle:     Serial Puzzle
  Objective:  Find the RX / TX UART lines and answer prompts until success


  Prompts: -



*/

long serialTimer = 0;
int serialThreshold = 500 / CLOCK_DIVIDER;
int correctAnswers = 0;
bool didDisplay = false;

void performSerialPuzzle() {
  if (millis() - serialTimer > serialThreshold) {
    if (!didWriteHint) {
      String s = "Nom! Nothing better than a delicious bowl of serial!";
      currentHint = s;
      writeNFC(s);
      didWriteHint = true;

      return;
    }

    // Show the waiting animation
    setCurrentAnimationState(pulse);

    Serial1.println("You found serial! The flag to submit is the name of the smiley-face-and-crossbones DEF CON mascot.");

//    if (!didDisplay) {
//      switch (correctAnswers) {
//        case (0): {
//            // serial question 1
//            Serial1.println("Congratulations, you found some delcious serial! To earn this flag though, you must answer three questions (this time back through serial).");
//            Serial1.println("");
//            Serial1.println("First Question: In what year was the first DEF CON?");
//            Serial1.println("A: 1990");
//            Serial1.println("B: 1993"); //
//            Serial1.println("C: 1997");
//            Serial1.println("D: 2000");
//            didDisplay = true;
//            break;
//          }
//        case (1): {
//            // serial question 2
//            Serial1.println("Second Question: In 1999, Cult of the Dead Cow released what software package at DEF CON?");
//            Serial1.println("A: NetBus");
//            Serial1.println("B: Sub7");
//            Serial1.println("C: Back Orifice"); //
//            didDisplay = true;
//            break;
//          }
//        case (2): {
//            // serial question 3
//            Serial1.println("Third Question: What color badge grants you access to all further DEF CONs?");
//            Serial1.println("A: Black"); //
//            Serial1.println("B: Red");
//            Serial1.println("C: White");
//            Serial1.println("D: Yellow");
//            didDisplay = true;
//            break;
//          }
//        case (3): {
//            Serial1.println("Congrats! You correctly solved all 3 questions! The flag to submit is the name of the smiley-face-and-crossbones DEF CON mascot.");
//            didDisplay = true;
//            return;
//            break;
//          }
//      }
//
//      Serial1.flush();
//    }
//
//    int sByte = Serial1.read();
//    Serial1.printf("Here is the byte that was read: ");
//    Serial1.println(sByte);
//
//    if (sByte == -1) {
//      return;
//    }
//
//    switch (correctAnswers) {
//      case (0): {
//          // B or B
//          if (sByte == 66 || sByte == 98) {
//            didDisplay = false;
//            correctAnswers++;
//          } else {
//            // Play fail animation
//            // Clear console
//            Serial1.printf("Received byte: ");
//            Serial1.println(sByte);
//            didDisplay = false;
//          }
//          break;
//        }
//      case (1): {
//          // C or C
//          if (sByte == 67 || sByte == 99) {
//            didDisplay = false;
//            correctAnswers++;
//          } else {
//            // Play fail animation
//            // Clear console
//            Serial1.printf("Received byte: ");
//            Serial1.println(sByte);
//            didDisplay = false;
//          }
//          break;
//        }
//      case (2): {
//          // A or a
//          if (sByte == 65 || sByte == 97) {
//            correctAnswers++;
//            didDisplay = false;
//          } else {
//            // Play fail animation
//            // Clear console
//            Serial1.printf("Received byte: ");
//            Serial1.println(sByte);
//            didDisplay = false;
//          }
//          break;
//        }
//    }

    serialTimer = millis();
  }


}

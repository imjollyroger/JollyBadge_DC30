/*

  STATE

*/

GameState currentState = initializing;
GameState previousState = initializing;

void initializeGameState() {
  if (!EEPROM.isValid()) {
    Serial1.printf("EEPROM is empty, new game to begin. \r\n");
    nextState();
  } else {
    Serial1.printf("Restoring game state from EEPROM. \r\n");
    GameState storedState = (GameState)EEPROM.read(0);
    setGameState(storedState);
  }
}

void setTemporaryGameState(GameState nextState) {
  // Serial1.printf("Setting temporary game state to: %d \r\n", nextState);

  previousState = currentState;
  currentState = nextState;
}

void setGameState(GameState nextState) {
  Serial1.printf("Setting game state to: %d \r\n", nextState);

  previousState = currentState;
  currentState = nextState;
  EEPROM.write(0, nextState);
  EEPROM.commit();

  delay(10);
}

bool isCompleted() {
  if (EEPROM.read(1) == 1) {
    return true;
  } else {
    return false;
  }
}

void setComplete() {
  EEPROM.write(1, 1);
  EEPROM.commit();
}

void nextState() {
  GameState nextState = (GameState)(currentState + 1);
  setGameState(nextState);
}

void checkForPuzzleSolve() {
  String uCurrentText = currentText;
  uCurrentText.toUpperCase();
  
  String uCurrentHint = currentHint;
  uCurrentHint.toUpperCase();

  if (uCurrentText == "RESET") {
    pauseState = false;
    currentText = "";
    EEPROM.write(1, 0);
    EEPROM.commit();
    currentState = initializing;
    nextState();
    return;
  }
  
  if (pauseState) {
    // Serial1.println("STATE IS PAUSED.");
    return; 
  }
  
  String solution = "";
  switch (currentState) {
    case (pNFC): {
      solution = "HOM3C0MING";
      break;  
    }
    case (pMorseCode): {
      solution = "HACK THE PLANET!";
      break; 
    }
    case (pBinary): {
      solution = "CAESARS FORUM";
      break;
    }
    case (pSerial): {
      solution = "JACK";
      break;  
    }
    case (pDataDump): {
      solution = "CRASH OVERRIDE";
      break;
    }
    case (pCrypto): {
      solution = "FINDJOLLYROGER";
      break;  
    }
    case (complete): {
      solution = "42069";
      break;  
    }
  }

  String uSolution = solution;
  uSolution.toUpperCase();

  if (isCompleted()) {
    setCurrentAnimationState(bling);
    return;
  }

  if (uCurrentText != uSolution && 
      uCurrentText != uCurrentHint &&
      uCurrentHint != "") {
    Serial1.printf("Solution check failed. Current Text: ");
    Serial1.print(currentText);
    Serial1.printf(", Solution: ");
    Serial1.print(solution);
    Serial1.printf(", Hint: ");
    Serial1.println(currentHint);
    didWriteHint = false;
    setCurrentAnimationState(failure);
    return;
  }

  if (uCurrentText == uSolution) {
    Serial1.println("SUCCESS!");

    didWriteHint = false;
    
    if (currentState == complete) {
      setCurrentAnimationState(bling);
      setComplete();
    } else {
      currentHint = "";
      
      setCurrentAnimationState(success);
      
      nextState();  
    }
    
    return;
  }
}

void performCurrentGameState() {
  if (pauseState) {
    Serial1.println("STATE PAUSED");
    return;  
  }
  
  switch (currentState) {
    case (pNFC): {
      performNFCPuzzle();
      break;  
    }
    case (pMorseCode): {
      performMorsePuzzle();
      break;  
    }
    case (pBinary): {
      performBinaryPuzzle();
      break;  
    }
    case (pSerial): {
      performSerialPuzzle();
      break;  
    }
    case (pDataDump): {
      performDumpPuzzle();
      break;  
    }
    case (pCrypto): {
      performCryptoPuzzle();
      break;  
    }
    case (complete): {
      performCompletePuzzle();
      break;  
    }
    case (finalBling): {
      performFinalPuzzle();
      break;
    }
  }
}

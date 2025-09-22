enum State { IDLE, FAHREN, LINKS, RECHTS, STOP };
State state = IDLE;

void loop() {
  readSensors();

  switch(state) {
    case IDLE:
      stopMotors();
      if (startButtonPressed()) state = FAHREN;
      break;

    case FAHREN:
      driveForward();
      if (frontSensor < 20) {   // Hindernis <20cm
        state = LINKS;
      }
      break;

    case LINKS:
      turnLeft();
      delay(500);               // feste Zeit
      state = RECHTS;
      break;

    case RECHTS:
      turnRight();
      delay(500);               // feste Zeit
      state = STOP;
      break;

    case STOP:
      stopMotors();
      break;
  }
}

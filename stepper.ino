//=================================================================
//  Start Stepper Motor
//=================================================================

  void stepper_start() {

    // Setup Stepper Pins
    pinMode(stepper_ena, OUTPUT);
    pinMode(stepper_stp, OUTPUT);
    pinMode(stepper_dir, OUTPUT);

    // Disable Driver
    digitalWrite(stepper_ena, HIGH);

    // Press Button To Start
    terminal.println(" -> Stepper Motor Started");

  }

  void stepper_power_on() {
    
    // Power Up Motor
    digitalWrite(stepper_ena, LOW);

  }

  void stepper_power_off() {

    // Power Off Motor
    digitalWrite(stepper_ena, HIGH);

  }

  void stepper_direction_forward() {
    digitalWrite(stepper_dir, HIGH);
  }

  void stepper_direction_backward() {
    digitalWrite(stepper_dir, LOW);
  }

//=================================================================
//  Move Motor Counted Steps
//=================================================================

  void stepper_move_steps(unsigned long Steps, StepperMotorDirection Direction, unsigned int StepMicroSeconds) {

    // Select Direction
    if(Direction == FORWARD) {
      stepper_direction_forward();
    } else {
      stepper_direction_backward();
    }

    // Power The Motor
    digitalWrite(stepper_ena, LOW);

    // Counted Loop
    for(unsigned long i=0; i<Steps; i++) {

      // Move Single Step
      stepper_move_single_step(StepMicroSeconds);

    }

    // Power Off The Motor
    digitalWrite(stepper_ena, HIGH);

  }

//=================================================================
//  Move Motor Undefinit Until Hall Detection
//=================================================================

  void stepper_move_till_hall(StepperMotorDirection Direction, unsigned int StepMicroSeconds) {

    // Select Direction
    if(Direction == FORWARD) {
      stepper_direction_forward();
    } else {
      stepper_direction_backward();
    }

    // Power The Motor
    digitalWrite(stepper_ena, LOW);

    // Continous Till Hall Detection
    while(1) {

      // Read Magnet Sensor
      magnet_det = digitalRead(sensor_hal);

      // If Magnet Detected & Not Equals Previous State
      if(magnet_det != magnet_prv) {
        
        // Take Snap Shot From The state
        magnet_prv = magnet_det;

        // If The State Was Detected As LOW
        if(magnet_det == LOW) {
          return;
        }

      }

      // Move Single Step
      stepper_move_single_step(StepMicroSeconds);

    }

    // Power Off The Motor
    digitalWrite(stepper_ena, HIGH);

  }

//=================================================================
//  Move Motor Single Step
//=================================================================

  void stepper_move_clear_balls(Button *btn, unsigned int StepMicroSeconds) {

    // Display A Message
    lcd_Print_Center("Press Clear", "Button To Start");

    // Wait Till Button Is Released
    while(!btn->pressed());

    // Display A Message
    lcd_Print_Center("Hoper Ball Clear", "Routine Starting");

    // Wait For 100mS
    delay(3000);

    // Display A Message
    lcd_Print_Center("Press Button", "Again To Stop");

    // Select Direction
    stepper_direction_forward();

    // Power The Motor
    digitalWrite(stepper_ena, LOW);

    // Continous Till Hall Detection
    while(1) {

      if(btn->pressed()) {
        break;
      }

      // Move Single Step
      stepper_move_single_step(StepMicroSeconds);

    }

    // Power Off The Motor
    digitalWrite(stepper_ena, HIGH);

    // Clear Display
    lcd_Clear();

  }

//=================================================================
//  Move Motor Single Step
//=================================================================

  void stepper_move_single_step(unsigned int StepMicroSeconds) {

    digitalWrite(stepper_stp, !digitalRead(stepper_stp));
    delayMicroseconds(StepMicroSeconds);

  }

//=================================================================
//  Move Motor Single Step
//=================================================================
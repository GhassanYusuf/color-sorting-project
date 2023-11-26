//-----------------------------------------------------------------

  void hall_start() {

    // Setup Hall Effect Pins
    pinMode(sensor_hal, INPUT);

    // Attach To Interrupt
    // attachInterrupt(digitalPinToInterrupt(sensor_hal), hall_state_change, FALLING);
    
    // Press Button To Start
    terminal.println(" -> Hall Effect Started");

  }

//-----------------------------------------------------------------

  void hall_state_change() {

    // If We Are Driving Motor In Reverse Ignore Changes
    if(digitalRead(stepper_dir) == LOW) {
      return;
    }

    // Read Magnet Sensor
    magnet_det = digitalRead(sensor_hal);

    // If Magnet Detected & Not Equals Previous State
    if(magnet_det != magnet_prv) {
      
      // Take Snap Shot From The state
      magnet_prv = magnet_det;
      
    }

  }

//=================================================================
//  END OF FUNCTIONS
//=================================================================
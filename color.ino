
  void color_reading() {
    
    // Reading Red
    ColorSensor.Red.value   = ColorSensor.getRedPW();
    delay(200);
    
    // Reading Green
    ColorSensor.Green.value = ColorSensor.getGreenPW();
    delay(200);

    // Reading Blue
    ColorSensor.Blue.value  = ColorSensor.getBluePW();
    delay(200);

    // Display Data
    terminal.println("Red = " + String(ColorSensor.Red.value) + " , Green = " + String(ColorSensor.Green.value) + " , Blue = " + String(ColorSensor.Blue.value));
    delay(200);

  }
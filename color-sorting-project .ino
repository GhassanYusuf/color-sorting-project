//================================================
//  Include Header
//================================================

  // Include Header
  #include "header.h"

//================================================
//  Setup Loop
//================================================

  void setup() {
    
    // Start Serial Terminal
    terminal.begin(9600);

    // Begin LCD
    lcd_Init();

    // Clear LCD
    lcd_Clear();

    // Starting Color Sensor
    ColorSensor.begin();

    // Turn Off The DropBall Device
    DropBall.turnOff();

    // Ball Slide Attach Pin
    BallSlide.setMin(0);        // The Servo Min Position Is Going To Be 15
    BallSlide.setMax(180);      // The Servo Max Position In Goint To Be 148
    BallSlide.setInit(90);      // The Servo Initial Position
    BallSlide.begin();          // Starting The Servo Activity
    BallSlide.goInit();         // Go To Initial Position

  }

//================================================
//  Main Program
//================================================

  void loop() {

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

//================================================
//  END Program
//================================================
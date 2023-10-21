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

    // Turn On Light
    lcd_Light();

    // Write Welcome Message
    lcd_Welcome_Message();

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



  }

//================================================
//  END Program
//================================================
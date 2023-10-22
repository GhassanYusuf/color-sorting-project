//================================================
//  Header Start
//================================================

  // Defenition : Serial Port
  #define   terminal              Serial

//================================================
//  LCD Control
//================================================

  // Library Import
  #include  <Wire.h> 
  #include  <LiquidCrystal_I2C.h>

  // Set The LCD address To 0x27 For A 16 Chars And 2 Line Display
  LiquidCrystal_I2C lcd(0x27, 16, 2);

//================================================
//  Motor Control
//================================================

  // Pin Defenition
  #define   motor_balslide_pin    2
  #define   motor_dropball_pin    3

//------------------------------------------------

  // Library Import
  #include  <Relay.h>

  // Control Drop Ball Motor
  Relay     DropBall(motor_dropball_pin, false);

//------------------------------------------------

  // Library Import
  #include  <NewServo.h>

  // Positions Structure
  struct Position {
    uint8_t position;
    uint8_t colors; 
  };

  // Positions
  #define   servo_positions               4
  #define   servo_position_resolution     180/servo_positions

  // Array Of Positions
  Position  position[servo_positions];

  // Control Ball Slide
  NewServo  BallSlide(motor_balslide_pin);

//================================================
//  Color Sensor
//================================================

  // Libraries
  #include  "tcs230.h"

  // Color Sensor Pins
  #define   sensor_color_s0       4
  #define   sensor_color_s1       5
  #define   sensor_color_s2       6
  #define   sensor_color_s3       7
  #define   sensor_color_ot       8

  // Object Sensor
  tcs230    ColorSensor(sensor_color_s0, sensor_color_s1, sensor_color_s2, sensor_color_s3, sensor_color_ot);

//================================================
//  Header End
//================================================
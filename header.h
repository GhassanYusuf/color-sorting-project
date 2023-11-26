//-----------------------------------------------------------------
//  Header Top - Files & Libraries
//-----------------------------------------------------------------

  // Include Pins Files
  #include "pins.h"
  
  // Storing And Reading
  #include <EEPROM.h>
  
  // Button Library
  #include <Button.h>

  // Servo Library
  #include <NewServo.h>

  // LCD Display Library
  #include <Wire.h> 
  #include <LiquidCrystal_I2C.h>

//-----------------------------------------------------------------
//  Definitions
//-----------------------------------------------------------------

  #define   _NULL         ""
  #define   _BLACK        'B'
  #define   _WHITE        'W'
  #define   _ORANGE       'O'
  #define   _GREEN        'G'
  #define   _NOTREC       'N'
  #define   _SNGSEP       print_seperator('1', 65)
  #define   _DBLSEP       print_seperator('=', 65)

  #define   _NUMCOL       3

//-----------------------------------------------------------------
//  ENUM Litrals
//-----------------------------------------------------------------

  // Stepper Directions
  enum  StepperMotorDirection   { FORWARD = 0, BACKWARD = 1 };

//-----------------------------------------------------------------
//  Objects
//-----------------------------------------------------------------

  // Button Object
  Button button_start(btn_start);
  Button button_clear(btn_clear);
  
  // LCD Screen Object
  LiquidCrystal_I2C lcd(0x27, 16, 2);

  // Servo Motor Object
  NewServo Slide(servo_pin);

//-----------------------------------------------------------------
//  Data Structures
//-----------------------------------------------------------------

  // Minimum And Maximum - Sub Structure
  struct Range {
    int16_t Value;                // 32 Bit Integer Data
    int16_t Min;                  // 16 Bit Integer Data
    int16_t Max;                  // 16 Bit Integer Data
  };

  // Color Data Structure
  struct ColorDataStructure {
    char    Color;                // Dataset Color Litral - 
    uint8_t Position;             // Servo Direction To Dump
    Range   Red;                  // Contains Current Value, Minimum, Maximum
    Range   Green;                // Contains Current Value, Minimum, Maximum
    Range   Blue;                 // Contains Current Value, Minimum, Maximum
  };

  const int structSize = sizeof(ColorDataStructure);

//-----------------------------------------------------------------
//  Variables
//-----------------------------------------------------------------

  // Hall Effect Sensor Variables
  bool magnet_prv   = false;
  bool magnet_det   = false;

  // Based On Number Of Colors
  int32_t Average[_NUMCOL];
  int16_t Value[_NUMCOL];
  uint8_t Count[_NUMCOL];

  // Make Ball Colors
  ColorDataStructure Ball[_NUMCOL];

  // Temporary Color Data Buffer
  ColorDataStructure TempColorData;

//=================================================================
//  SETUP
//=================================================================
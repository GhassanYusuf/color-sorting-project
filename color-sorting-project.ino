//=================================================================
//  SETUP
//=================================================================

  #include "header.h"

//=================================================================
//  SETUP
//=================================================================

  void setup() {

  //----------------------------------
    // Setting Up Communication Speed
    terminal.begin(115200);
    terminal.println();
    terminal.println();
    terminal.println(" -> Serial Started");
  //----------------------------------
    // Start Stepper Motor
    stepper_start();
  //----------------------------------
    // Start Up LCD
    lcd_startup();
  //----------------------------------
    // Start Buttons
    buttons_start();
  //----------------------------------
    // Starting Color Sensor
    color_sensor_start();
  //----------------------------------
    // Set Colors Data
    color_set_data_init();
  //----------------------------------
    // Start Slide Test
    slide_start();
  //----------------------------------
    // Start Hall Effect
    hall_start();
  //----------------------------------

  }

//=================================================================
//  RUNNING CODE
//=================================================================

  void loop() {
    
    // LCD Display
    lcd_Print_Center("Press Start", ">>> Button <<<");

    // Press Button To Start
    terminal.println(" -> Press Button To Start");

    // Wait Fill Button Is Pressed
    while(!button_start.pressed());

    // Clear Counter
    for(int x=0; x<_NUMCOL; x++) {
      Count[x] = 0;
      Value[x] = 0;
    }

    // Print On LCD
    lcd_Print_Sorting(_NUMCOL);

    // Set Forward Direction
    stepper_direction_forward();

    // Power Up The Motor
    stepper_power_on();

    // Reading Loop
    while(1) {

      // Read Magnet Sensor
      magnet_det = digitalRead(sensor_hal);

      // If Magnet Detected & Not Equals Previous State
      if(magnet_det != magnet_prv) {
        
        // Take Snap Shot From The state
        magnet_prv = magnet_det;

        // If The State Was Detected As LOW
        if(magnet_det == LOW) {

          // Read And Detect
          read_and_detect(3);

          // // Exit Loop End Of Process
          // if(findDataSet(Ball, _BLACK).Count == 2) {
          //   break;
          // }

          // Printing On LCD
          lcd_Print_Sorting(_NUMCOL);

        }

      }

      // Stepping The Motor
      digitalWrite(stepper_stp, !digitalRead(stepper_stp));
      delayMicroseconds(300);

    }

    // Release Motor
    digitalWrite(stepper_ena, HIGH);

    // Print Report
    terminal.println(" -> Process Ended No Balls Left");
    terminal.println(" -> " + BallCountReport());

    // Print On LCD
    lcd_Print_Center("<<<< Finished >>>>", BallCountReport());

    // Wait For Some Time
    delay(3000);

    // Print New Lines
    terminal.println();
    terminal.println();

  }

//=================================================================
//  END
//=================================================================
//-----------------------------------------------------------------
//  Set Ball Colors Dataset
//-----------------------------------------------------------------

  void color_set_data_init() {

    // Black
    Ball[0].Color      = _BLACK;
    color_reset_min_max(Ball[0]);

    // Orange
    Ball[1].Color      = _ORANGE;
    color_reset_min_max(Ball[1]);

    // White
    Ball[2].Color      = _WHITE;
    color_reset_min_max(Ball[2]);

    // Green
    Ball[3].Color      = _GREEN;
    color_reset_min_max(Ball[3]);

    // Not Recognized
    Ball[4].Color      = _NOTREC;
    color_reset_min_max(Ball[4]);

    // Calibrate Using Colors
    color_set_calibration();

    // Ball Colors Data Set Started
    terminal.println(" -> Ball Colors Data Set Cleared");

  }

//-----------------------------------------------------------------
//  Read Mapped Colors Data
//-----------------------------------------------------------------

  void color_read(ColorDataStructure &dataset) {

    // Read Red Pulse Width
    dataset.Red.Value   = getRedPW();
    dataset.Red.Min     = min(dataset.Red.Min, dataset.Red.Value);
    dataset.Red.Max     = max(dataset.Red.Max, dataset.Red.Value);

    // Delay to stabilize sensor
    delay(200);

    // Read Green Pulse Width
    dataset.Green.Value = getGreenPW();
    dataset.Green.Min   = min(dataset.Green.Min, dataset.Green.Value);
    dataset.Green.Max   = max(dataset.Green.Max, dataset.Green.Value);

    // Delay to stabilize sensor
    delay(200);

    // Read Blue Pulse Width
    dataset.Blue.Value  = getBluePW();
    dataset.Blue.Min    = min(dataset.Blue.Min, dataset.Blue.Value);
    dataset.Blue.Max    = max(dataset.Blue.Max, dataset.Blue.Value);

    // Delay to stabilize sensor
    delay(200);

  }

//-----------------------------------------------------------------
//  Read Raw Data --> For Debug Purposes
//-----------------------------------------------------------------

  void color_raw_data(ColorDataStructure &dataset) {

    // Reseting Min Max
    color_reset_min_max(dataset);

    // Loop For Colors
    while(1) {

      // Read Red Pulse Width
      color_read(dataset);

      // Methode To Get Min & Max
      print_color_set(_NULL, _NULL, &dataset);

    }

  }

//-----------------------------------------------------------------
//  Color Sensor
//-----------------------------------------------------------------

  void color_reset_min_max(ColorDataStructure &dataset) {

    // Red
    dataset.Red.Value   = 0;
    dataset.Red.Min     = 32767;
    dataset.Red.Max     = -32768;

    // Green
    dataset.Green.Value = 0;
    dataset.Green.Min   = 32767;
    dataset.Green.Max   = -32768;
    
    // Blue
    dataset.Blue.Value  = 0;
    dataset.Blue.Min    = 32767;
    dataset.Blue.Max    = -32768;

  }

//-----------------------------------------------------------------
//  Color Calibration
//-----------------------------------------------------------------

  void color_set_calibration() {

    // Power Up The Motor
    stepper_power_on();

    // Movment Direction
    stepper_direction_forward();

    // Print Calibration Start
    print_seperator('=', 65);

    // Color Calibration Loop
    while(1) {

      // Power Up The Motor
      stepper_power_on();

      // Reseting Min Max
      color_reset_min_max(TempColorData);

      // If Not On Spot
      if(digitalRead(sensor_hal) != LOW) { stepper_move_till_hall(FORWARD, 400); }

      // Reading On Center
      for(int i=0; i<3; i++) { color_read(TempColorData); }

      // Mave Forward After Detection
      stepper_move_steps(800, BACKWARD, 400);

      // Reading On End Edge
      for(int i=0; i<3; i++) { color_read(TempColorData); }

      // Mave Forward After Detection
      stepper_move_steps(800, FORWARD, 400);

      // Reading On End Edge
      for(int i=0; i<3; i++) { color_read(TempColorData); }

      // New Line
      terminal.println();

      // Methode To Get Min & Max
      print_color_set("CURRENT", _NULL, &TempColorData);

      // New Line
      terminal.println();

      // Drop The Ball
      stepper_move_till_hall(FORWARD, 400);

      // Ask A Question
      String x = Question("What Color Was That Ball ( W, O, G, B ) ?");

      if(x == "W" || x == "w") {

        uint8_t num = findDataSetID(Ball, _WHITE);

        Ball[num].Red.Min    = updateMin(Ball[num].Red.Min, TempColorData.Red.Min);
        Ball[num].Red.Max    = updateMax(Ball[num].Red.Max, TempColorData.Red.Max);
        Ball[num].Green.Min  = updateMin(Ball[num].Green.Min, TempColorData.Green.Min);
        Ball[num].Green.Max  = updateMax(Ball[num].Green.Max, TempColorData.Green.Max);
        Ball[num].Blue.Min   = updateMin(Ball[num].Blue.Min, TempColorData.Blue.Min);
        Ball[num].Blue.Max   = updateMax(Ball[num].Blue.Max, TempColorData.Blue.Max);
        
        // print_color_set(Ball[num].Title, _NULL, &Ball[num]);
        print_all_datasets(Ball);

      } else if(x == "O" || x == "o") {

        uint8_t num = findDataSetID(Ball, _ORANGE);

        Ball[num].Red.Min    = updateMin(Ball[num].Red.Min, TempColorData.Red.Min);
        Ball[num].Red.Max    = updateMax(Ball[num].Red.Max, TempColorData.Red.Max);
        Ball[num].Green.Min  = updateMin(Ball[num].Green.Min, TempColorData.Green.Min);
        Ball[num].Green.Max  = updateMax(Ball[num].Green.Max, TempColorData.Green.Max);
        Ball[num].Blue.Min   = updateMin(Ball[num].Blue.Min, TempColorData.Blue.Min);
        Ball[num].Blue.Max   = updateMax(Ball[num].Blue.Max, TempColorData.Blue.Max);

        // print_color_set(Ball[num].Title, _NULL, &Ball[num]);
        print_all_datasets(Ball);

      } else if(x == "G" || x == "g") {
        
        uint8_t num = findDataSetID(Ball, _GREEN);

        Ball[num].Red.Min    = updateMin(Ball[num].Red.Min, TempColorData.Red.Min);
        Ball[num].Red.Max    = updateMax(Ball[num].Red.Max, TempColorData.Red.Max);
        Ball[num].Green.Min  = updateMin(Ball[num].Green.Min, TempColorData.Green.Min);
        Ball[num].Green.Max  = updateMax(Ball[num].Green.Max, TempColorData.Green.Max);
        Ball[num].Blue.Min   = updateMin(Ball[num].Blue.Min, TempColorData.Blue.Min);
        Ball[num].Blue.Max   = updateMax(Ball[num].Blue.Max, TempColorData.Blue.Max);

        // print_color_set(Ball[num].Title, _NULL, &Ball[num]);
        print_all_datasets(Ball);

      } else if(x == "B" || x == "b") {

        uint8_t num = findDataSetID(Ball, _BLACK);

        Ball[num].Red.Min    = updateMin(Ball[num].Red.Min, TempColorData.Red.Min);
        Ball[num].Red.Max    = updateMax(Ball[num].Red.Max, TempColorData.Red.Max);
        Ball[num].Green.Min  = updateMin(Ball[num].Green.Min, TempColorData.Green.Min);
        Ball[num].Green.Max  = updateMax(Ball[num].Green.Max, TempColorData.Green.Max);
        Ball[num].Blue.Min   = updateMin(Ball[num].Blue.Min, TempColorData.Blue.Min);
        Ball[num].Blue.Max   = updateMax(Ball[num].Blue.Max, TempColorData.Blue.Max);

        // print_color_set(Ball[num].Title, _NULL, &Ball[num]);
        print_all_datasets(Ball);

      } else if(x == "E" || x == "e") {

        // Power Off The Motor
        stepper_power_off();
        return;

      }

      // Clear Min Max
      color_reset_min_max(TempColorData);

    }

  }
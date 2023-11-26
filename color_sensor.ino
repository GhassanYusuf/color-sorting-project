//=================================================================
//  Color Sensor
//=================================================================

  void color_sensor_start() {

    // Set S0 - S3 as outputs
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);

    // Set Pulse Width scaling to 20%
    digitalWrite(S0,HIGH);
    digitalWrite(S1,LOW);

    // Set Sensor output as input
    pinMode(sensorOut, INPUT);

    // Warming Up Message
    terminal.print(" -> Warming Up Sensor ");

    // Warm UP Sensor
    for(int i=0; i<5; i++) {
      color_read(TempColorData);
      terminal.print(" .");
    }

    // New Line
    terminal.println();

    // Press Button To Start
    terminal.println(" -> Color Sensor Started");

  }

//-----------------------------------------------------------------
//  Read & Detect
//-----------------------------------------------------------------

  void read_and_detect(uint8_t readings) {

    // Initiate Time Of This Process
    unsigned long timecal = millis();

    // Reading Time
    color_reset_min_max(TempColorData);

    // Counted Loop
    for(int i=0; i<readings; i++) {

      // Reading Colors
      color_read(TempColorData);

      // Reading Average Colors
      TempColorData.Red.Value   += TempColorData.Red.Value;
      TempColorData.Green.Value += TempColorData.Green.Value;
      TempColorData.Blue.Value  += TempColorData.Blue.Value;

      // Mave Forward After Detection
      stepper_move_steps(1125, FORWARD, 400);

      // Mave Forward After Detection
      stepper_move_steps(1125, BACKWARD, 400);

    }

    // Calculating Averages
    TempColorData.Red.Value   = TempColorData.Red.Value/readings;
    TempColorData.Green.Value = TempColorData.Green.Value/readings;
    TempColorData.Blue.Value  = TempColorData.Blue.Value/readings;

    // Print output to Serial Monitor
    terminal.print(" -> ( Red = ");
    terminal.print(TempColorData.Red.Value);
    terminal.print(", Green = ");
    terminal.print(TempColorData.Green.Value);
    terminal.print(", Blue = ");
    terminal.print(TempColorData.Blue.Value);
    terminal.print(" ) ===>>> ");

    // Detect Color
    identifyColor(&TempColorData);

    // Print Time
    terminal.println(" -> Time Take " + String(millis() - timecal));

  }

//-----------------------------------------------------------------
//  Function to read Red Pulse Widths
//-----------------------------------------------------------------

  int getRedPW() {
    // Set sensor to read Red only
    digitalWrite(S2,LOW);
    digitalWrite(S3,LOW);
    // Define integer to represent Pulse Width
    int PW;
    // Read the output Pulse Width
    PW = pulseIn(sensorOut, LOW);
    // Return the value
    return PW;
  }

//-----------------------------------------------------------------
//  Function to read Green Pulse Widths
//-----------------------------------------------------------------

  int getGreenPW() {
    // Set sensor to read Green only
    digitalWrite(S2,HIGH);
    digitalWrite(S3,HIGH);
    // Define integer to represent Pulse Width
    int PW;
    // Read the output Pulse Width
    PW = pulseIn(sensorOut, LOW);
    // Return the value
    return PW;
  }

//-----------------------------------------------------------------
//  Function to read Blue Pulse Widths
//-----------------------------------------------------------------

  int getBluePW() {
    // Set sensor to read Blue only
    digitalWrite(S2,LOW);
    digitalWrite(S3,HIGH);
    // Define integer to represent Pulse Width
    int PW;
    // Read the output Pulse Width
    PW = pulseIn(sensorOut, LOW);
    // Return the value
    return PW;
  }

//-----------------------------------------------------------------
//  Print Color Data Set
//-----------------------------------------------------------------

  void print_color_set(String prefix, String suffix, ColorDataStructure *dataset) {
    
    if(prefix != _NULL) {
      terminal.print("[ " + prefix + " ] -> ");
    }

    terminal.print("Red ( Min = " + String(dataset->Red.Min) + ", Max = " + String(dataset->Red.Max) + " ) - ");
    terminal.print("Green ( Min = " + String(dataset->Green.Min) + ", Max = " + String(dataset->Green.Max) + " ) - ");
    terminal.print("Blue ( Min = " + String(dataset->Blue.Min) + ", Max = " + String(dataset->Blue.Max) + " )");

    if(suffix != _NULL) {
      terminal.print(" ===> " + suffix);
    }

    terminal.println();

  }

//-----------------------------------------------------------------
//  Update Min
//-----------------------------------------------------------------

  int updateMin(int Old, int New) {
    if(Old != 0 && Old > New) {
      return New;
    }
  }

//-----------------------------------------------------------------
//  Update Max
//-----------------------------------------------------------------

  int updateMax(int Old, int New) {
    if(Old != 0 && Old < New) {
      return New;
    }
  }

//-----------------------------------------------------------------
//  Find Data Set
//-----------------------------------------------------------------

  int findDataSetID(ColorDataStructure *dataset, char KeyWord) {

    // Search Withing Color Dataset
    for(int i=0; i<size_t(&dataset); i++) {
      if(dataset[i].Color == KeyWord) {
        return i;
      }
    }

    // Return Empty Data Set If We Dont Find It
    return 0;

  }

//-----------------------------------------------------------------
//  Find Data Set
//-----------------------------------------------------------------

  ColorDataStructure findDataSet(ColorDataStructure *dataset, char KeyWord) {

    // Search Withing Color Dataset
    for(int i=0; i<size_t(&dataset); i++) {
      if(dataset[i].Color == KeyWord) {
        return dataset[i];
      }
    }

    // Return Empty Data Set If We Dont Find It
    return ColorDataStructure();

  }

//-----------------------------------------------------------------
//  Find Data Set And Update Min And Max For Colors
//-----------------------------------------------------------------

  ColorDataStructure findAndUpdateDataSet(ColorDataStructure *dataset, char KeyWord) {

    // Get The Data Set Data In New Variable
    ColorDataStructure NewVariable = findDataSet(dataset, KeyWord);

    // Update Min's & Max's
    NewVariable.Red.Min    = updateMin(NewVariable.Red.Min, TempColorData.Red.Min);
    NewVariable.Red.Max    = updateMax(NewVariable.Red.Max, TempColorData.Red.Max);
    NewVariable.Green.Min  = updateMin(NewVariable.Green.Min, TempColorData.Green.Min);
    NewVariable.Green.Max  = updateMax(NewVariable.Green.Max, TempColorData.Green.Max);
    NewVariable.Blue.Min   = updateMin(NewVariable.Blue.Min, TempColorData.Blue.Min);
    NewVariable.Blue.Max   = updateMax(NewVariable.Blue.Max, TempColorData.Blue.Max);

    // Return The DataSet
    return NewVariable;

  }

//=================================================================
//  END OF FUNCTIONS
//=================================================================
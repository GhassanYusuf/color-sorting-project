//=================================================================
//  QUESTION
//=================================================================

  String Question(String Message) {

    terminal.print("Q: " + Message + " ?" + "\n" + "A: ");

    while(!terminal.available());

    String x = terminal.readStringUntil('\n');

    while(terminal.available()) terminal.read();

    x.trim();

    terminal.println(x);

    terminal.println();

    return x;

  }

//-----------------------------------------------------------------
//  Starting Buttons
//-----------------------------------------------------------------

  void buttons_start() {
    
    // Buttons
    button_start.begin();
    button_clear.begin();

    // Press Button To Start
    terminal.println(" -> Buttons Function Started");

  }

//-----------------------------------------------------------------
//  Print Seperator
//-----------------------------------------------------------------

  void print_seperator(char seperator, uint16_t length) {

    // Print The Seperator
    for(int i=0; i<length; i++) {
      terminal.print(seperator);
    }

    // Print New Line
    terminal.println();

  }

//-----------------------------------------------------------------
//  Print Title
//-----------------------------------------------------------------

  void print_title(String Title, char topSep, char botSep, uint8_t length) {

    print_seperator(topSep, length);
    terminal.print("\t");
    terminal.println(Title);
    print_seperator(botSep, length);

  }

//-----------------------------------------------------------------
//  Print Datasets
//-----------------------------------------------------------------

  void print_all_datasets(ColorDataStructure *datasets) {

    // Print Header
    print_title("All Datasets", '=', '-', 65);

    // Loop Through Data Sets
    for (int i=0; i<5; i++) {
      print_color_set(String(datasets[i].Color), _NULL, &datasets[i]);
    }

    // Terminator
    print_seperator('=', 65);

  }

//-----------------------------------------------------------------
//  Print Datasets
//-----------------------------------------------------------------

  char identifyColor(ColorDataStructure *dataset) {

    for(int i=0; i<5; i++) {

      if(dataset->Red.Value >= Ball[i].Red.Min && dataset->Red.Value <= Ball[i].Red.Max && dataset->Green.Value >= Ball[i].Green.Min && dataset->Green.Value <= Ball[i].Green.Max && dataset->Blue.Value >= Ball[i].Blue.Min && dataset->Green.Value <= Ball[i].Blue.Max) {

        Slide.move(Ball[i].Position);
        return Ball[i].Color;

      } else {
        
        return "UNKNOWN";

      }

    }

  }

//-----------------------------------------------------------------
//  Print Datasets
//-----------------------------------------------------------------

  String BallCountReport() {

    // Building A Buffer
    String buffer;

    // Loop Through Colors
    for(int z=0; z<_NUMCOL; z++) {
      buffer += Ball[z].Color;
      buffer += ":";
      buffer += Count[z];
      if(z < _NUMCOL) {
        buffer += ", "; 
      }
    }

    // Return Report
    return buffer;

  }

//=================================================================
//  END
//=================================================================
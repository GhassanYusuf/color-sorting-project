//=================================================================
//  Servo Start
//=================================================================

  void slide_start() {

    // By Setting The Bounderies Of Servo Movment, The Servo Will Not Move Out Of This Bounderies
    Slide.setMin(15);     // The Servo Min Position Is Going To Be 15
    Slide.setMax(165);    // The Servo Max Position In Goint To Be 148
    Slide.setInit(90);    // The Servo Initial Position

    // Starting The Servo Activity
    Slide.begin();

    // Go To Initial Position
    Slide.goInit();
    
    // Press Button To Start
    terminal.println(" -> Slide Servo Started");

  }

//-----------------------------------------------------------------
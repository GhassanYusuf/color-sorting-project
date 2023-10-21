//================================================
//  Initialization
//================================================

  void lcd_Init() {
    lcd.init();
  }

//================================================
//  Clear
//================================================

  void lcd_Clear() {
    lcd.clear();
  }

//================================================
//  LCD Light
//================================================

  void lcd_Light() {
    lcd.backlight();
  }

//================================================
//  LCD Dark
//================================================

  void lcd_Dark() {
    lcd.noBacklight();
  }

//================================================
//  LCD Print
//================================================

  void lcd_Print(String line1, String line2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print(line2);
  }

//------------------------------------------------

  void lcd_Print_Center(String line1, String line2) {

    int spaceL1 = (16-line1.length())/2;
    int spaceL2 = (16-line2.length())/2;

    lcd.clear();
    lcd.setCursor(spaceL1, 0);
    lcd.print(line1);
    lcd.setCursor(spaceL2, 1);
    lcd.print(line2);
    
  }

//================================================
//  LCD Blink
//================================================

  void lcd_Blink(uint8_t BlinkTimes, unsigned int BlinkDelay) {
    for(int i=0; i<BlinkTimes; i++) {
      lcd.noBacklight();
      delay(BlinkDelay/2);
      lcd.backlight();
      delay(BlinkDelay/2);
    }
  }

//================================================
//  LCD Blink
//================================================

  void lcd_Welcome_Message() {
    lcd_Print_Center("Welcome To", "Sorting Machine");
    delay(3000);
    lcd_Print_Center("Project (B)", "UTB University");
    delay(1000);
    lcd_Blink(4, 500);
    delay(1000);
    lcd_Print("Done By", "1. Talal");
    delay(2000);
    lcd_Print("Done By", "2. Mohammed");
    delay(2000);
    lcd_Print("Done By", "3. Ali");
    delay(2000);
    lcd_Print_Center("Starting >>>", "");
    delay(2000);
  }

//================================================
//  END
//================================================
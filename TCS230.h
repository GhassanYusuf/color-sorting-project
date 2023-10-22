
  class tcs230 {

    private:

      // Pins
      uint8_t   _pin_s0 = 0;
      uint8_t   _pin_s1 = 0;
      uint8_t   _pin_s2 = 0;
      uint8_t   _pin_s3 = 0;
      uint8_t   _pin_ot = 0;

      // Boundaries
      struct Boundaries {
        int value;
        int min;
        int max;
      };

    public:

      // Boundries
      Boundaries  Red, Green, Blue;

      // 1st Constructor
      tcs230() {}

      // 2nd Constructor
      tcs230(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t ot) {

        // Setup Pins Of The Module
        setPins(s0, s1, s2, s3, ot);

      }

      // Setting Up Pins
      void setPins(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t ot) {

        // Assigning Pins
        _pin_s0 = s0;
        _pin_s1 = s1;
        _pin_s2 = s2;
        _pin_s3 = s3;
        _pin_ot = ot;

      }

      // Starting The Pin Directions
      void begin() {

        // Setting Pins Mode
	      pinMode(_pin_s0, OUTPUT);
	      pinMode(_pin_s1, OUTPUT);
	      pinMode(_pin_s2, OUTPUT);
	      pinMode(_pin_s3, OUTPUT);
	      pinMode(_pin_ot, INPUT);

      }

      // Reading Red
      int getRedPW() {

        // Set sensor to read Red only
        digitalWrite(_pin_s2, LOW);
        digitalWrite(_pin_s3, LOW);

        // Read the output Pulse Width
        int PW = pulseIn(_pin_ot, LOW);

        // Return the value
        return PW;

      }

      // Reading Green
      int getGreenPW() {

        // Set sensor to read Red only
        digitalWrite(_pin_s2, HIGH);
        digitalWrite(_pin_s3, HIGH);

        // Read the output Pulse Width
        int PW = pulseIn(_pin_ot, LOW);

        // Return the value
        return PW;

      }

      // Reading Blue
      int getBluePW() {

        // Set sensor to read Red only
        digitalWrite(_pin_s2, LOW);
        digitalWrite(_pin_s3, HIGH);

        // Read the output Pulse Width
        int PW = pulseIn(_pin_ot, LOW);

        // Return the value
        return PW;

      }

  };
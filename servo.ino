
  void set_positions() {
    for(int i=0; i<servo_positions; i++) {
      position[i].position = i * servo_position_resolution;
    }
  }
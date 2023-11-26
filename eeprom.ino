

// Store the data in EEPROM
void storeDataInEEPROM(ColorDataStructure data[], int dataSize) {
  int address = 0;

  for (int i = 0; i < dataSize; i++) {
    EEPROM.put(address, data[i]);
    address += structSize;
  }

}

// Read the data from EEPROM
void readDataFromEEPROM(ColorDataStructure data[], int dataSize) {
  int address = 0;

  for (int i = 0; i < dataSize; i++) {
    EEPROM.get(address, data[i]);
    address += structSize;
  }
}
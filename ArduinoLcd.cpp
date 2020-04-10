// Originalna implementacija se temeljila na "time" libraryju
// i CPU ciklusima ali tome nemamo pristup u tinkercadu
void Lcd::_delayMicroseconds(float microseconds) {
  const unsigned long start = millis();
  while (millis() < start + pow(microseconds, -3));
}

void Lcd::writeData(uint8_t data, uint8_t registerSelect) {
  // LOW = instruction registry, HIGH = data registry
  Wire.beginTransmission(0x20); // Započni prijenos na slave
  Wire.write(registerSelect);
  Wire.write(data);
  Wire.endTransmission();
}

/* public */

// Inicijalizira display
void Lcd::begin() {
  
  // Priključuje Arduino I2C sabirnici kao master uređaj
  Wire.begin();
  
  /**
   * HD44780U driver nudi 3 opcije display-a:
   *    1: 5X8 točaka u jednoj liniji
   *    2: 5X10 točaka u jednoj liniji
   *    3: 5X8 točaka u dvije linije
   *    
   * Mi na labosima uvijek koristimo 5x8 na dvije linije tako da se nećemo zamarat s drugim opcijama
   * Zato i konstruktor ne prima broj redova i stupaca
  */

  // Inicijalizacija LCD-a -> Str. 45, Figure 23 - Pratimo graf i šaljemo podatke prema njemu
  _delayMicroseconds(50000); // Wait for more than 40ms after Vcc rises to 2.7V
  
  writeData(0b0000110000, LOW);
  _delayMicroseconds(5000); // Wait for more than 4.1ms
  
  writeData(0b0000110000, LOW);
  _delayMicroseconds(150); // Wait for more than 100us
  
  writeData(0b0000110000, LOW);

  // Inicijalizacija je ovdje gotova, sada se postavlja mod (5x8 na dvije linije)
  writeData(DISPLAYFUNC_TWOLINE_5X8DOTS, LOW);

  // Ukljucuje display
  mDisplayControl = DISPLAYCTRL_DISPLAYON;
  writeData(DISPLAY_CONTROL | mDisplayControl, LOW);
  
  clear();
}

void Lcd::clear() {
  writeData(CLEAR_DISPLAY, LOW);
  delayMicroseconds(200);
}

void Lcd::home() {
  writeData(RETURN_HOME, LOW);
}

void Lcd::setCursor(uint8_t row, uint8_t column) {
  // HD44780 datasheet -> str. 12, Figure 6
  row = row % 2 == 0 ? 0x00 : 0x40;
  writeData(SET_DDRAM_ADDRESS | row + column % 16, 0);
}

void Lcd::print(const char *str) {
  for (int i = 0; i < strlen(str); ++i) {
    writeData((uint8_t) str[i], 1);
  }
}

void Lcd::blink() {
  mDisplayControl |= DISPLAYCTRL_CURSORBLINK | DISPLAYCTRL_DISPLAYON;
  writeData(DISPLAY_CONTROL | mDisplayControl, LOW);
}

void Lcd::noBlink() {
  mDisplayControl &= ~DISPLAYCTRL_CURSORBLINK;
  writeData(DISPLAY_CONTROL | mDisplayControl, LOW);
}

void Lcd::createChar() {
  // HD44780U Datasheet -> str. 30, 31
}

void Lcd::write(uint8_t data) {
  writeData(data, 1);
}

#ifndef ArduinoLcd
#define ArduinoLcd

// Instrukcije za LCD
#define CLEAR_DISPLAY         0b0000000001
#define RETURN_HOME           0b0000000010
#define ENTRYMODE_SET         0b0000000100
#define DISPLAY_CONTROL       0b0000001000
#define CURSOR_DISPLAY_SHIFT  0b0000010000
#define FUNCTION_SET          0b0000100000
#define SET_CGRAM_ADDRESS     0b0001000000
#define SET_DDRAM_ADDRESS     0b0010000000
#define READ_BF_AND_ADDRESS   0b0100000000
#define WRITE_DATA_TO_ADDRESS 0b1000000000
#define READ_DATA_FROM_RAM    0b1100000000

// DISPLAY_CONTROL flagovi
// Objasnjenja -> Str 26, sekcija Display On/Off control
// Poredak -> Str 28, Figure 11
#define DISPLAYCTRL_DISPLAYON   0b0000000100
#define DISPLAYCTRL_CURSORON    0b0000000010
#define DISPLAYCTRL_CURSORBLINK 0b0000000001

// FUNCTION_SET flagovi -> Str 28, Figure 11
// Objasnjenja -> Str 29, Table 8
#define DISPLAYFUNC_ONELINE_5X8DOTS   0b0000110000
#define DISPLAYFUNC_ONELINE_5X10DOTS  0b0000110100
#define DISPLAYFUNC_TWOLINE_5X8DOTS   0b0000111000

// Definicija klase
class Lcd {
  private: 
    uint8_t mRegisterSelectPin;
    uint8_t mReadWritePin;
    uint8_t mEnablePin;
    uint8_t mDataPins[8];
    uint8_t mDisplayControl;
    void _delayMicroseconds(float microseconds);
    void sendEnablePulse();
    void writeData(uint8_t data, uint8_t mode);

  public: 
    void begin();
    void clear();
    void home();
    void setCursor(uint8_t row, uint8_t column);
    void print(const char *str);
    void blink();
    void noBlink();
    void createChar();
    void write(uint8_t data);
};
#endif

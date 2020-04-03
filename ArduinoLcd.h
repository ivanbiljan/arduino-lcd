#include <Print.h>

#ifndef ArduinoLcd
#define ArduinoLcd

// Instrukcije
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

// Pin Mode
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULL 2

// Write State
#define HAJ 1
#define LOU 0

class Lcd: public Print {
  private: 
    uint8_t mRegisterSelectPin;
    uint8_t mReadWritePin;
    uint8_t mEnablePin;
    uint8_t mDataPins[8];
    void _pinMode(uint8_t pin, int isOut);
    void _digitalWrite(uint8_t pin, int state);
    void _delayMicroseconds(float microseconds);
    void sendEnablePulse();
    void writeData(uint8_t data);

  public: 
    Lcd(uint8_t registerSelect, uint8_t readWrite, uint8_t enable, uint8_t dataPins[8]);
    void clear();
    void home();
    void setCursor();
    void print();
    void blink();
    void noBlink();
    void createChar();
};

#endif

#include "Wire.h"
#include "Arduino.h"
#include "ArduinoLcd.h"
#include <math.h>

/**
 * The i2c bit pattern data is actually in the following order:

        Backlight   -> bit 3
        E           -> bit 2
        RW          -> bit 1
        RS          -> bit 0
        D7          -> bit 7
        D6          -> bit 6
        D5          -> bit 5
        D4          -> bit 4
*/

/*void delayMicroseconds(unsigned int mseconds) {
    clock_t goal = ((CLOCKS_PER_SEC * mseconds) * pow(10, -6)) + clock();
    while (goal > clock());
}*/

Lcd::Lcd(uint8_t registerSelect, uint8_t readWrite, uint8_t enable, uint8_t dataPins[8]) {
  mRegisterSelectPin = registerSelect;
  mReadWritePin = readWrite;
  mEnablePin = enable;

  for (auto i = 0; i < sizeof(dataPins) / sizeof(uint8_t); ++i) {
    mDataPins[i] = dataPins[i];
  }
}


/* private: */
void _pinMode(uint8_t pin, int mode) {
  // DDR - IN / OUT
  // PORT - IN = PULLUP
  // PIN  - READ STATE
  
  if (pin >= 0 && pin <= 7) {
    DDRD |= pin - 1;
    if (mode == INPUT_PULL) {
      PORTD |= (1 << pin);
    } 
  }
  
  if (pin >= 8 && pin <= 13) {
    DDRB |= (1 << pin - 8);
    if (pin == INPUT_PULL) {
      PORTB |= (1 << pin - 8);
    }
  }
}

void _digitalWrite(int pin, int state) {
  switch (state) {
    case HAJ:
        if (pin >= 2 && pin <= 7) {
          PORTD |= (1 << pin);
        } else if (pin >= 8 && pin <= 13) {
          PORTB |= (1 << pin - 8);
        }
      break;
    case LOU:
        if (pin >= 2 && pin <= 7) {
          PORTD &= ~(1 << pin);
        } else if (pin >= 8 && pin <= 13) {
          PORTB &= ~(1 << pin - 8);
        }
      break;
  }
}

void _delayMicroseconds(float microseconds) {
  const unsigned long start = millis();
  while (millis() < start + pow(microseconds, -3));
}

void sendEnablePulse() {
  digitalWrite(mEnablePin, HAJ);
  _delayMicroseconds(450);
  digitalWrite(mEnablePin, LOU);
  _delayMicroseconds(5);
}

void writeData(uint8_t data) {
  for (auto i = 0; i < sizeof(mDataPins) / sizeof(uint8_t); ++i) {
    int state = LOU;
    
    // Ako je bit pristuan state = HAJ
    if (data & (1 << i) {
      state = HAJ;
    }
    _digitalWrite(mDataPins[i], state);
  }

  sendEnablePulse();
}

/* public */
void Lcd:clear() {
  
}

void Ld:home() {
  
}

void Lcd:setCursor() {
  
}

void Lcd:print() {
  
}

void Lcd:blink() {
  
}

void Lcd:noBlink() {
  
}

void Lcd:createChar() {
  
}

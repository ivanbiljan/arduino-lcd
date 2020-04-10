#include <Wire.h>

const int registerSelectPin = 2;
const int enablePin = 3;
const uint8_t pins[8] = {8, 9, 10, 11, 4, 5, 6, 7};

void setup() {
  pinMode(registerSelectPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  for (int i = 0; i < 8; ++i) {
    pinMode(pins[i], OUTPUT);
  }
  
  // Povezati Arduino na I2C sabirnicu kao slave uređaj
  // s adresom 0x20
  Wire.begin(0x20);
  Wire.onReceive(receiveEvent);
}

void loop() {
  
}

void _pinMode(uint8_t pin, int mode) {
  // DDR - IN / OUT
  // PORT - IN = PULLUP
  // PIN  - READ STATE (DIGITAL READ)
  
  // Prema slici iz biljeznica, Bank D su pinovi 0-7
  if (pin >= 0 && pin <= 7) {
    DDRD |= pin;
    if (mode == INPUT_PULLUP) {
      PORTD |= (1 << pin);
    } 
  }
  
  // Bank B su pinovi 8-13
  if (pin >= 8 && pin <= 13) {
    DDRB |= (1 << pin - 8);
    if (pin == INPUT_PULLUP) {
      PORTB |= (1 << pin - 8);
    }
  }
}

void _digitalWrite(uint8_t pin, uint8_t state) {
  switch (state) {
    case HIGH:
        if (pin >= 0 && pin <= 7) {
          PORTD |= (1 << pin);
        } else if (pin >= 8 && pin <= 13) {
          PORTB |= (1 << pin - 8);
        }
      break;
    case LOW:
        if (pin >= 0 && pin <= 7) {
          PORTD &= ~(1 << pin);
        } else if (pin >= 8 && pin <= 13) {
          PORTB &= ~(1 << pin - 8);
        }
      break;
  }
}

void receiveEvent(int num) {
  if (!Wire.available()) {
    return;
  }
  
  // Podatke ocekujemo sljedecim redoslijedom: 
  // 1: RS pin
  // 2: Stanje (čita li se instrukcijski ili podatkovni registar)
  // 3: Podatak
  // 4: Enable pin
  
  uint8_t rsState = Wire.read();
  uint8_t data = Wire.read();
  
  digitalWrite(registerSelectPin, rsState);
  for (int i = 0; i < 8; ++i) {
    digitalWrite(pins[i], data & (1 << i));
  }
  
  digitalWrite(enablePin, HIGH);
  delayMicroseconds(1);
  digitalWrite(enablePin, LOW);
  delayMicroseconds(100);
}

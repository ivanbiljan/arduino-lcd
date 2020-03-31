#include <Arduino.h>
#include "Wire.h"
#include "ArduinoLcd.h"
#include <time.h>

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

unsigned char _address, _rows, _cols;

// Strana 9 - Table 1
// Saljemo 4-bitne podatke zato sto je simulacija na tinkercadu 4-bitna
/*void sendInstruction(BYTE data) {
  Wire.beginTransmission(_address);
  Wire.write((data & 0b11110000) | BACKLIGHT_BIT);
  Wire.endTransmission();

  sendEnable();
  delayMicroseconds(1);

  Wire.beginTransmission();
  Wire.write(((data << 4) & 0b11110000));
  Wire.endTransmission();

  sendEnable(1);
  delayMicroseconds(74);
}

void sendEnable(int disableFlag = 0) {
  Wire.beginTransmission(_address);
  Wire.write(disableFlag ? ~ENABLE_BIT : ENABLE_BIT);
  Wire.endTransmission();
}*/

void send_4bit_data(BYTE data) {
  // Slanje uz enable bit
  Wire.beginTransmission(_address);
  Wire.write(data | ENABLE_BIT);
  Wire.endTransmission(); 

  // Delay
  delayMicroseconds(1);

  // Bez enable bita, kraj prijenosa
  Wire.beginTransmission(_address);
  Wire.write(data & ~ENABLE_BIT);
  Wire.endTransmission();

  // Procesuiranje naredbe
  delayMicroseconds(74);
}

void send_byte(BYTE data) {
  send_4bit_data(data & 0b11110000)
  send_4bit_data((data << 4) & 0b11110000);
}

void lcd_init(unsigned char address, unsigned char rows, unsigned char cols) {
    _address = address;
    _rows = rows;
    _cols = cols;

    Wire.begin();

    // https://www.sparkfun.com/datasheets/LCD/HD44780.pdf - strana 46, prati se graf
    // Cekanje na Vcc
    delayMicroseconds(80000);

    // Prvo slanje
    sendInstruction(0b0000110000);
    delayMicroseconds(50000);

    // Drugo slanje
    sendInstruction(0b0000110000);
    delayMicroseconds(200);

    // Treci put
    sendInstruction(0b0000110000);

    // Postavlja u 4. bitni mod
    sendInstruction(0b0000100000);

    // Inicijalizacija backlighta
}

void delayMicroseconds(unsigned int mseconds) {
    clock_t goal = ((CLOCKS_PER_SEC * mseconds) * pow(10, -6)) + clock();
    while (goal > clock());
}

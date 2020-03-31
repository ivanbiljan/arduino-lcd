#ifndef ArduinoLcd
#define ArduinoLcd

// Instrukcije
#define CLEAR_DISPLAY         0b0000000001;
#define RETURN_HOME           0b0000000010;
#define ENTRYMODE_SET         0b0000000100;
#define DISPLAY_CONTROL       0b0000001000;
#define CURSOR_DISPLAY_SHIFT  0b0000010000;
#define FUNCTION_SET          0b0000100000;
#define SET_CGRAM_ADDRESS     0b0001000000;
#define SET_DDRAM_ADDRESS     0b0010000000;
#define READ_BF_AND_ADDRESS   0b0100000000;
#define WRITE_DATA_TO_ADDRESS 0b1000000000;
#define READ_DATA_FROM_RAM    0b1100000000;

// Bitovi
#define BACKLIGHT_BIT 0b00001000;
#define ENABLE_BIT    0b00000100;
#define READWRITE_BIT 0b00000010;
#define REGSELECT_BIT 0b00000001;

// Tipovi
typedef unsigned char BYTE;

// LCD
void lcd_init(BYTE, BYTE, BYTE);
void lcd_clear();
void lcd_home();
void lcd_set_cursor();
void lcd_print();
void lcd_blink();
void lcd_noblink();
void lcd_create_char();

// MISC
void delayMicroseconds(unsigned int microseconds);
#endif

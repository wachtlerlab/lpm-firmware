/*************************************************** 
  This is a library for our Adafruit 24-channel PWM/LED driver

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/1429

  These drivers uses SPI to communicate, 3 pins are required to  
  interface: Data, Clock and Latch. The boards are chainable

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/


#include <Adafruit_TLC5947.h>

Adafruit_TLC5947::Adafruit_TLC5947(uint8_t n, uint8_t c, uint8_t d, uint8_t l) {
  numdrivers = n;
  _clk = c;
  _dat = d;
  _lat = l;

  pwmbuffer = (uint16_t *)calloc(2, 24*n);
}

void Adafruit_TLC5947::write(void) {
  digitalWrite(_lat, LOW);
  // 24 channels per TLC5974
  for (int8_t c=24*numdrivers - 1; c >= 0 ; c--) {
    // 12 bits per channel, send MSB first
    for (int8_t b=11; b>=0; b--) {
      digitalWrite(_clk, LOW);
      
      if (pwmbuffer[c] & (1 << b))  
        digitalWrite(_dat, HIGH);
      else
        digitalWrite(_dat, LOW);

      digitalWrite(_clk, HIGH);
    }
  }
  digitalWrite(_clk, LOW);
  
  digitalWrite(_lat, HIGH);  
  digitalWrite(_lat, LOW);
}



void Adafruit_TLC5947::setPWM(uint8_t chan, uint16_t pwm) {
  if (pwm > 4095) pwm = 4095;
  if (chan > 24*numdrivers) return;
  pwmbuffer[chan] = pwm;  
}


uint16_t Adafruit_TLC5947::getPWM(uint8_t chan) {
  return pwmbuffer[chan];
}

void Adafruit_TLC5947::setLED(uint8_t lednum, uint16_t r, uint16_t g, uint16_t b) {
  setPWM(lednum*3, r);
  setPWM(lednum*3+1, g);
  setPWM(lednum*3+2, b);
}


boolean Adafruit_TLC5947::begin() {
  if (!pwmbuffer) return false;

  pinMode(_clk, OUTPUT);
  pinMode(_dat, OUTPUT);
  pinMode(_lat, OUTPUT);
  digitalWrite(_lat, LOW);

  return true;
}

uint8_t Adafruit_TLC5947::number_of_pins() const {
  return numdrivers*24;
}


void Adafruit_TLC5947::reset() {
  memset(pwmbuffer, 0, sizeof(uint16_t)*24*numdrivers);
}


uint16_t* Adafruit_TLC5947::getPWMBuffer() {
  return pwmbuffer;
}

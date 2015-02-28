#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

int led = 6;
int brightness = 0;
int fadeAmount = 5;

struct LED {
    LED(uint8_t pin, int br) : pin(pin), brightness(br) {}

    void setup() {
        pinMode(pin, OUTPUT);
    }

    void write() {
        analogWrite(pin, brightness);
    }

    uint8_t pin;
    int brightness;


};

struct Pulsor {
    Pulsor(const LED &l, int step=5, int max_br = 255, int min_br = 0)
            : led(l), min_br(min_br), max_br(max_br), step(step) { }

    void pulse() {
        int &brightness = led.brightness;

        analogWrite(led.pin, led.brightness);

        brightness += step;
        if (brightness >= max_br) {
            brightness = max_br;
            step *= -1;
        } else if (brightness <= min_br) {
            brightness = min_br;
            step *= -1;
        }
    }

    int min_br;
    int max_br;
    int step;

    LED led;
};

LED blue(6, 0);
LED green(3, 125);
LED red(5, 250);

LED all(9, 255);

Pulsor p_blue(blue, 1, 100);
Pulsor p_green(green, 2);
Pulsor p_red(red, 3);

void setup() {                
    blue.setup();
    green.setup();
    red.setup();

    all.setup();
}

void loop() {

    p_red.pulse();
    p_blue.pulse();
    p_green.pulse();

    all.write();

    // wait for 30 milliseconds to see the dimming effect
    delay(30);
}

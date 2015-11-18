#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <Adafruit_TLC5947.h>
#include <nikon.h>


Adafruit_TLC5947 io(1, 5, 4, 6);

void setup() {
    io.begin();
    pinMode(13, OUTPUT);
}

//pwm 10,4096
//reset
//info
//shoot

struct command {
    const char *command_id;
    void (*func)(const String &args);
};

static void handle_pwm(const String &args) {
    int pos = args.indexOf(',');
    String pin_str = args.substring(0, pos);
    String pwm_str = args.substring(pos + 1);

    int pin = pin_str.toInt();
    int pwm = pwm_str.toInt();

    io.setPWM(pin, pwm);
    io.write();

    Serial.print("parsed pin val: ");
    Serial.println(pin);

    Serial.print("parsed pwm val: ");
    Serial.println(pwm);
}

static void handle_reset(const String &args) {
    io.reset();
    io.write();
}

static void handle_shoot(const String &args) {
    //take picture using nikon camera
    NikonRemote remote(13);
    remote.click();
}

static void handle_info(const String &args) {

    uint16_t *pwmBuffer = io.getPWMBuffer();
    for(int i=0; i< io.number_of_pins(); i++ ) {
        Serial.print("Pin: ");
        Serial.print(i);
        Serial.print("  -  PWM: ");
        Serial.println(pwmBuffer[i]);
    }
}

command known_cmds[] = {
        {"pwm", handle_pwm},
        {"reset", handle_reset},
        {"info", handle_info},
        {"shoot", handle_shoot},
        {NULL, NULL}
};

void loop() {

    if(Serial.available() > 0)  {
        String input = Serial.readStringUntil('\r');
        int pos = input.indexOf(' ');

        String cmd;
        String args;

        if (pos != -1) {
            cmd = input.substring(0, pos);
            args = input.substring(pos+1);
            Serial.println(cmd);
        } else {
            cmd = input;
        }

        for (command *iter = known_cmds; iter->command_id != NULL; iter++) {
            if (cmd.equals(iter->command_id)) {
                (*iter->func)(args);
                break;
            }
        }

        Serial.println("\u0004\n");
    }

}

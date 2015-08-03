#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <Adafruit_TLC5947.h>

Adafruit_TLC5947 io(1, 5, 4, 6);

void setup() {
    io.begin();
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

command known_cmds[] = {
        {"pwm", handle_pwm},
        {"reset", handle_reset},
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

        Serial.println("*");
    }

}

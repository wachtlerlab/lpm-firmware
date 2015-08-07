#ifndef NIKONREMOTE_H
#define NIKONREMOTE_H

#include <Arduino.h>

class NikonRemote {
private:
    unsigned int ir_pin;
    void pulse_on( unsigned long );
    void pulse_off( unsigned long );

public:
    NikonRemote( unsigned int );
    void click();
};

#endif
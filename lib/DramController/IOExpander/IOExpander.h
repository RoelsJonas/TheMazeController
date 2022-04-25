#ifndef IOEXPANDER_H
#define IOEXPANDER_H
#include <arduino.h>

#define ledAddress 0x3B
#define controlRegister 0x03
#define outputRegister 0x01

#define HIGH 1
#define LOW 0

class IOExpander
{
    public:
        IOExpander(int address);
        void init();
        void setOut(int data);
        void setLeds(int data[5]);

    private:
        int _address; 
};
#endif
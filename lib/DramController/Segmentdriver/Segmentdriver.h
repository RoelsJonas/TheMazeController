#include <.\IOExpander\IOExpander.h>
#include <arduino.h>

#ifndef SEGMENTDRIVER_H
#define SEGMENTDRIVER_H

class Segmentdriver{
    private: 
        IOExpander *io;

    public:
        Segmentdriver(int addr);
        void init();
        void write_value(int value);
        void write_char(char kar);
};
#endif
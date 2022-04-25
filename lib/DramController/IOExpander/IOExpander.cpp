#include ".\IOExpander\IOExpander.h"
#include <Wire.h>

IOExpander::IOExpander(int address){
    _address = address;
    init();
}

void IOExpander::init(){
    Wire.begin();
    
    Wire.beginTransmission(_address);
    Wire.write(controlRegister);
    Wire.write(0b00000000);
    Wire.endTransmission();
}

void IOExpander::setOut(int data){
    Wire.beginTransmission(_address);
    Wire.write(outputRegister);
    Wire.write(data);
    Wire.endTransmission();
}

void IOExpander::setLeds(int data[5]){
    int dat = 0b00000000;
    for(int i = 0; i<5; i++){
        if(data[i] == 1){
            int temp = 0b1 << i;
        }
    }
}
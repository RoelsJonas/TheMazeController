#include ".\Segmentdriver\Segmentdriver.h"

Segmentdriver::Segmentdriver(int addr){
    io = new IOExpander(addr);
    init();
}

void Segmentdriver::init(){
    io->init();
}

void Segmentdriver::write_value(int value){
    switch(value){
        case 0: io->setOut(0b01000000); break;
        case 1: io->setOut(0b01111001); break;
        case 2: io->setOut(0b00100100); break;
        case 3: io->setOut(0b00110000); break;
        case 4: io->setOut(0b00011001); break;
        case 5: io->setOut(0b00010010); break;
        case 6: io->setOut(0b00000010); break;
        case 7: io->setOut(0b01111000); break;
        case 8: io->setOut(0b00000000); break;
        case 9: io->setOut(0b00010000); break;
        default: io->setOut(0); break;
    }
}
void Segmentdriver::write_char(char kar){
    switch(kar){
        case 'A': io->setOut(0b00001000); break;
        case 'B': io->setOut(0b00000011); break;
        case 'C': io->setOut(0b01000110); break;
        case 'D': io->setOut(0b00100001); break;
        case 'E': io->setOut(0b01010110); break;
        case 'F': io->setOut(0b00001110); break;
        case 'G': io->setOut(0b01000010); break;
        case 'H': io->setOut(0b00001001); break;
        case '0': io->setOut(0b01000000); break;
        case '1': io->setOut(0b01111001); break;
        case '2': io->setOut(0b00100100); break;
        case '3': io->setOut(0b00110000); break;
        case '4': io->setOut(0b00011001); break;
        case '5': io->setOut(0b00010010); break;
        case '6': io->setOut(0b00000010); break;
        case '7': io->setOut(0b01111000); break;
        case '8': io->setOut(0b00000000); break;
        case '9': io->setOut(0b00010000); break;
        default:  io->setOut(0b01111111); break;
    }
}

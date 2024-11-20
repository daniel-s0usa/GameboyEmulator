#pragma once

#include <cstdint>

class Io {
    private:
        // methods
        
        // variables
        uint8_t _data[0x80];   //0xFF7F - 0xFF00 + 1

    public:
        // Constructor

        // methods
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);

};
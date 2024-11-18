#pragma once

#include <cstdint>

class Ram {
    private:
        // methods
        
        // variables
        uint8_t _wram[0x2000];   //0xDFFF - 0xC000 + 1
        uint8_t _hram[0x007F];   //0xFFFE - 0xFF80 + 1

    public:
        // Constructor

        // methods
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);

};
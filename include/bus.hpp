#pragma once

#include <cartridge.hpp>

class Bus {
    private:
        // methods
        
        // variables
        Cartridge * _cartridge;

    public:
        // Constructor
        Bus(Cartridge * cartridge);

        // methods
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);
        void setCartridge(Cartridge * cartridge);

};
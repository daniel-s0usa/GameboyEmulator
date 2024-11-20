#pragma once

#include <cartridge.hpp>
#include <ram.hpp>
#include <io.hpp>

class Bus {
    private:
        // methods
        
        // variables
        Cartridge * _cartridge;
        Ram _ram;
        Io _io;
        uint8_t interrupt_enable;

    public:
        // Constructor
        Bus(Cartridge * cartridge);

        // methods
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);
        void setCartridge(Cartridge * cartridge);

};
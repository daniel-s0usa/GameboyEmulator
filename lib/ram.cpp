//Own import
#include <ram.hpp>

//Other component imports

//System imports
#include <iostream>



uint8_t Ram::read(uint16_t address) {
    if (0xC000 <= address && address <= 0xDFFF) {
        return _wram[address - 0xC000];
    }
    else if (0xFF80 <= address && address <= 0xFFFE) {
        return _hram[address - 0xFF80];
    }
    else {
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }
    return (uint8_t) 0xFFFF;
}


void Ram::write(uint16_t address, uint8_t value) {
    if (0xC000 <= address && address <= 0xDFFF) {
        _wram[address - 0xC000] = value;
    }
    else if (0xFF80 <= address && address <= 0xFFFE) {
        _hram[address - 0xFF80] = value;
    }
    else {
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }

}
//Own import
#include <io.hpp>

//Other component imports

//System imports
#include <iostream>



uint8_t Io::read(uint16_t address) {
    if (0xFF00 <= address && address <= 0xFF7F) {
        return _data[address - 0xFF00];
    }
    else {
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }
    return (uint8_t) 0xFFFF;
}


void Io::write(uint16_t address, uint8_t value) {
    if (0xFF00 <= address && address <= 0xFF7F) {
        _data[address - 0xFF00] = value;
    }
    else {
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }

}
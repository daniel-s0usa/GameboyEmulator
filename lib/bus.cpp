//Own import
#include <bus.hpp>

//Other component imports
#include <cartridge.hpp>
#include <ram.hpp>

//System imports
#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>


Bus::Bus(Cartridge * cartridge) {
    _cartridge = cartridge; 

    if (_cartridge->read_rom_address(0x0147) != 0x00) {
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }
}


uint8_t Bus::read(uint16_t address) {
    std::cout << "Reading address: " << address << '\n';
    
    if (0x0000 <= address && address <= 0x3FFF) {     // ROM0 - Non-switchable ROM Bank.
        return _cartridge->read_rom_address(address);
    }
    else if (0x4000 <= address && address <= 0x7FFF) {     // ROMX - Switchable ROM bank.
        return _cartridge->read_rom_address(address);
        std::cout << "WARNING: Implemented MBC 0 only!!!!!" << '\n';
    }
    else if (0x8000 <= address && address <= 0x9FFF) {     // VRAM - Video RAM, switchable (0-1) in GBC mode.
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }
    else if (0xA000 <= address && address <= 0xBFFF) {     // SRAM - External RAM in cartridge, often battery buffered.
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }
    else if (0xC000 <= address && address <= 0xCFFF) {     // WRAM0 - Work RAM.
        return _ram.read(address);
    }
    else if (0xD000 <= address && address <= 0xDFFF) {     // WRAMX - Work RAM, switchable (1-7) in GBC mode
        return _ram.read(address);
        std::cout << "WARNING: Switchable bank not implemented!!!!!" << '\n';
    }
    else if (0xE000 <= address && address <= 0xFDFF) {     // ECHO - Description of the behaviour below.
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }
    else if (0xFE00 <= address && address <= 0xFE9F) {     // OAM - (Object Attribute Table) Sprite information table.
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }
    else if (0xFEA0 <= address && address <= 0xFEFF) {     // UNUSED - Description of the behaviour below.
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }
    else if (0xFF00 <= address && address <= 0xFF7F) {     // I/O Registers - I/O registers are mapped here.
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }
    else if (0xFF80 <= address && address <= 0xFFFE) {     // HRAM - Internal CPU RAM
        return _ram.read(address);
    }
    else if (0xFFFF == address) {               // IE Register - Interrupt enable flags.
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }

    return (uint8_t) 0xFFFF;
}


void Bus::write(uint16_t address, uint8_t value) {
    std::cout << "Writing to address: " << address << '\n';
    
    if (0x0000 <= address && address <= 0x3FFF) {     // ROM0 - Non-switchable ROM Bank.
        _cartridge->write_rom_address(address, value);
    }
    else if (0x4000 <= address && address <= 0x7FFF) {     // ROMX - Switchable ROM bank.
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }
    else if (0x8000 <= address && address <= 0x9FFF) {     // VRAM - Video RAM, switchable (0-1) in GBC mode.
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }
    else if (0xA000 <= address && address <= 0xBFFF) {     // SRAM - External RAM in cartridge, often battery buffered.
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }
    else if (0xC000 <= address && address <= 0xCFFF) {     // WRAM0 - Work RAM.
        _ram.write(address, value);
    }
    else if (0xD000 <= address && address <= 0xDFFF) {     // WRAMX - Work RAM, switchable (1-7) in GBC mode
        _ram.write(address, value);
        std::cout << "WARNING: Switchable bank not implemented!!!!!" << '\n';
    }
    else if (0xE000 <= address && address <= 0xFDFF) {     // ECHO - Description of the behaviour below.
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }
    else if (0xFE00 <= address && address <= 0xFE9F) {     // OAM - (Object Attribute Table) Sprite information table.
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }
    else if (0xFEA0 <= address && address <= 0xFEFF) {     // UNUSED - Description of the behaviour below.
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }
    else if (0xFF00 <= address && address <= 0xFF7F) {     // I/O Registers - I/O registers are mapped here.
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }
    else if (0xFF80 <= address && address <= 0xFFFE) {     // HRAM - Internal CPU RAM
        _ram.write(address, value);
    }
    else if (0xFFFF == address) {               // IE Register - Interrupt enable flags.
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }
}

//Own import
#include <cartridge.hpp>

//Other component imports

//System imports
#include <iostream>
#include <fstream>
#include <filesystem>
#include<map>

std::map<uint8_t, std::string> Cartridge::cartridgeTypeMap = {
    {0x00, "ROM Only"},
    {0x01, "MBC1"},
    {0x02, "MBC1 + RAM"},
    {0x03, "MBC1 + RAM + Battery"},
    {0x05, "MBC2"},
    {0x06, "MBC2 + RAM + Battery"},
    {0x08, "ROM + RAM"},
    {0x09, "ROM + RAM + Battery"},
    {0x0B, "MMM01"},
    {0x0C, "MMM01 + RAM"},
    {0x0D, "MMM01 + RAM + Battery"},
    {0x0F, "MBC3 + Timer + Battery"},
    {0x10, "MBC3 + RAM + Timer + Battery"},
    {0x11, "MBC3"},
    {0x12, "MBC3 + RAM"},
    {0x13, "MBC3 + RAM + Battery"},
    {0x19, "MBC5"},
    {0x1A, "MBC5 + RAM"},
    {0x1B, "MBC5 + RAM + Battery"},
    {0x1C, "MBC5 + Rumble"},
    {0x1D, "MBC5 + RAM + Rumble"},
    {0x1E, "MBC5 + RAM + Battery + Rumble"},
    {0x20, "MBC6 + RAM + Battery"},
    {0x22, "MBC7 + RAM + Bat. + Accelerometer"},
    {0xFC, "POCKET CAMERA"},
    {0xFD, "BANDAI TAMA5"},
    {0xFE, "HuC3"},
    {0xFF, "HuC1 + RAM + Battery"}
};


std::map<uint8_t, std::string> Cartridge::licenseeCodeMap = {
    {0x00, "None"},
    {0x01, "Nintendo R&D1"},
    {0x08, "Capcom"},
    {0x13, "Electronic Arts"},
    {0x18, "Hudson Soft"},
    {0x19, "b-ai"},
    {0x20, "kss"},
    {0x22, "pow"},
    {0x24, "PCM Complete"},
    {0x25, "san-x"},
    {0x28, "Kemco Japan"},
    {0x29, "seta"},
    {0x30, "Viacom"},
    {0x31, "Nintendo"},
    {0x32, "Bandai"},
    {0x33, "Ocean/Acclaim"},
    {0x34, "Konami"},
    {0x35, "Hector"},
    {0x37, "Taito"},
    {0x38, "Hudson"},
    {0x39, "Banpresto"},
    {0x41, "Ubi Soft"},
    {0x42, "Atlus"},
    {0x44, "Malibu"},
    {0x46, "angel"},
    {0x47, "Bullet-Proof"},
    {0x49, "irem"},
    {0x50, "Absolute"},
    {0x51, "Acclaim"},
    {0x52, "Activision"},
    {0x53, "American sammy"},
    {0x54, "Konami"},
    {0x55, "Hi tech entertainment"},
    {0x56, "LJN"},
    {0x57, "Matchbox"},
    {0x58, "Mattel"},
    {0x59, "Milton Bradley"},
    {0x60, "Titus"},
    {0x61, "Virgin"},
    {0x64, "LucasArts"},
    {0x67, "Ocean"},
    {0x69, "Electronic Arts"},
    {0x70, "Infogrames"},
    {0x71, "Interplay"},
    {0x72, "Broderbund"},
    {0x73, "sculptured"},
    {0x75, "sci"},
    {0x78, "THQ"},
    {0x79, "Accolade"},
    {0x80, "misawa"},
    {0x83, "lozc"},
    {0x86, "Tokuma Shoten Intermedia"},
    {0x87, "Tsukuda Original"},
    {0x91, "Chunsoft"},
    {0x92, "Video system"},
    {0x93, "Ocean/Acclaim"},
    {0x95, "Varie"},
    {0x96, "Yonezawa/s’pal"},
    {0x97, "Kaneko"},
    {0x99, "Pack in soft"},
    {0xA4, "Konami (Yu-Gi-Oh!)"}
};

std::map<uint8_t, std::string> Cartridge::romSizeMap = {
    {0x00, "32KB"}, //2 banks (No MBC needed)
    {0x01, "64KB"}, //4 banks
    {0x02, "128KB"}, //8 banks
    {0x03, "256KB"}, //16 banks
    {0x04, "512KB"}, //32 banks
    {0x05, "1MB" }, //64 banks
    {0x06, "2MB" }, //128 banks
    {0x07, "4MB" }, //256 banks
    {0x08, "8MB" } //512 banks
};

std::map<uint8_t, std::string> Cartridge::ramSizeMap = {
    {0x00, "None"},
    {0x01, "2KB"},
    {0x02, "8KB"}, //1 bank
    {0x03, "32KB"}, //4 banks of 8KB
    {0x04, "128KB"}, //16 banks of 8KB
    {0x05, "64KB"} //8 banks of 8 KB. Used by “Pokémon Crystal (J)”
};

std::map<uint8_t, std::string> Cartridge::destinationCodeMap = {
    {0x00, "Japan"},
    {0x01, "World"}
};


/// @brief Loads the cartridge to rom structure
/// @param path - path to rom
/// @return rom struture with the header, data and size
rom_struct Cartridge::load_cartridge(char * path) {

    std::cout << path;
    std::cout << "\n";

    _open_file(path);

    std::cout << "\tTitle: " << _rom.rom_header.title << '\n';
    std::cout << "\tCartridge type: " << Cartridge::_getCartridgeType(_rom.rom_header.cartridge_type) << '\n';
    std::cout << "\tLicensee: " << Cartridge::_getLicensee(_rom.rom_header.new_license_code) << '\n';
    std::cout << "\tRom size: " << Cartridge::_getRomSize(_rom.rom_header.rom_size) << '\n';
    std::cout << "\tRam size: " << Cartridge::_getRamSize(_rom.rom_header.ram_size) << '\n';
    std::cout << "\tDestination code: " << Cartridge::_getDestinationCode(_rom.rom_header.destination_code) << '\n';
    std::cout << "\tOld License code: " << Cartridge::_getOldLicenseeCode(_rom.rom_header.old_license_code) << '\n';
    std::cout << "\tRom version: " << Cartridge::_getRomVersion(_rom.rom_header.rom_version) << '\n';



    return _rom;
}

/// @brief Opens the file and interprets the data to som struct
/// @param path - path to rom
/// @return true if opened file successfully
bool Cartridge::_open_file(char * path) {

    std::ifstream test_file (path, std::ios::binary);

    if (test_file.fail())
    {
        std::cout << "Could not open file to read.\n";
        return false;
    }

    std::cout << "Opened cartridge successfully.\n";

    int size = std::filesystem::file_size(path);

    header_struct rom_header;
    uint8_t rom_data[size - 0x150 + 1];

    test_file.seekg(0x100, std::ios::cur);
    test_file.read(reinterpret_cast<char*> (&rom_header), sizeof rom_header);
    test_file.read(reinterpret_cast<char*> (rom_data), sizeof rom_data);

    rom_header.title[15] = '\0';

    // test_file.clear();
    // test_file.seekg(0, std::ios::beg);
    // uint8_t test_data[size + 1];
    // test_file.read(reinterpret_cast<char*> (test_data), sizeof test_data);


    if (_check_header_checksum(rom_header)) {
        //std::cout << "File was read correctly\n";
    } else {
        std::cout << "Error on header checksum\n";
        return false;
    }

    // TODO: check nintendo logo (some gameboys did this)

    _rom.rom_data = rom_data;
    _rom.rom_header = rom_header;
    _rom.rom_size = size; 

    return true;

}

/// @brief checks the header checksum
/// @param data - header_struct data to check the checksum
/// @return true if checksum is correct
bool Cartridge::_check_header_checksum(header_struct data) {


    uint8_t sum = 0;

    for (int i = 0; i <= sizeof data.title - 1; i++)
    {
        sum += _header_checksum_math(data.title[i]);
    }
    
    sum += _header_checksum_math(static_cast<uint8_t>((data.new_license_code & 0xFF00) >> 8));
    sum += _header_checksum_math(static_cast<uint8_t>(data.new_license_code & 0x00FF));
    sum += _header_checksum_math(data.sgb_flag);
    sum += _header_checksum_math(data.cartridge_type);
    sum += _header_checksum_math(data.rom_size);
    sum += _header_checksum_math(data.ram_size);
    sum += _header_checksum_math(data.destination_code);
    sum += _header_checksum_math(data.old_license_code); 
    sum += _header_checksum_math(data.rom_version);

    return sum == data.header_checksum;

}

/// @brief header checksum math
/// @param value 
/// @return (-value-1)
uint8_t Cartridge::_header_checksum_math(uint8_t value) {
    return ( - value - 1);
}

/// @brief Get Cartridge Type
/// @param value 
/// @return String with type
std::string Cartridge::_getCartridgeType(uint8_t value) {
    if (cartridgeTypeMap.find(value) != cartridgeTypeMap.end()) {
        return cartridgeTypeMap[value];
    }
    return "Undefined";
}

/// @brief Get Licensee
/// @param value 
/// @return String with licensee name
std::string Cartridge::_getLicensee(uint8_t value) {
    if (licenseeCodeMap.find(value) != licenseeCodeMap.end()) {
        return licenseeCodeMap[value];
    }
    return "Undefined";
}


std::string Cartridge::_getRomSize(uint8_t value) {
    if (romSizeMap.find(value) != romSizeMap.end()) {
        return romSizeMap[value];
    }
    return "Undefined";
}

std::string Cartridge::_getRamSize(uint8_t value) {
    if (ramSizeMap.find(value) != ramSizeMap.end()) {
        return ramSizeMap[value];
    }
    return "Undefined";
}

std::string Cartridge::_getDestinationCode(uint8_t value) {
    if (destinationCodeMap.find(value) != destinationCodeMap.end()) {
        return destinationCodeMap[value];
    }
    return "Undefined";
}

std::string Cartridge::_getOldLicenseeCode(uint8_t value) {
    return "NOT IMPLEMENTED"; //TODO
}

int Cartridge::_getRomVersion(uint8_t value) {
    return int(value);
}

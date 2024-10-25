//Own import
#include <cartridge.hpp>

//Other component imports

//System imports
#include <iostream>
#include <fstream>
#include <filesystem>

/// @brief Loads the cartridge to rom structure
/// @param path - path to rom
/// @return rom struture with the header, data and size
rom_struct Cartridge::load_cartridge(char * path) {

    std::cout << path;
    std::cout << "\n";

    _open_file(path);


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
    std::cout << "File size is:" << size << "bytes.\n";

    header_struct rom_header;
    uint8_t rom_data[size - 0x150 + 1];

    test_file.seekg(0x100, std::ios::cur);
    test_file.read(reinterpret_cast<char*> (&rom_header), sizeof rom_header);
    test_file.read(reinterpret_cast<char*> (rom_data), sizeof rom_data);

    // test_file.clear();
    // test_file.seekg(0, std::ios::beg);
    // uint8_t test_data[size + 1];
    // test_file.read(reinterpret_cast<char*> (test_data), sizeof test_data);


    if (_check_header_checksum(rom_header)) {
        std::cout << "File was read correctly";
    } else {
        std::cout << "Error on header checksum";
        return false;
    }

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

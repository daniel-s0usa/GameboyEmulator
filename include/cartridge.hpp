#pragma once

#include <cstdint>
#include <map>
#include <string>


typedef struct {

    uint8_t start_vector[4];
    uint8_t nintendo_logo[0x30];
    char title[16];//last 4 bytes in the Manufacturer code and last byte the GBC flag
    uint16_t new_license_code; //0x145-0x144
    uint8_t sgb_flag; //0x146
    uint8_t cartridge_type; //0x147
    uint8_t rom_size; //0x148
    uint8_t ram_size; //0x149
    uint8_t destination_code; //0x14A
    uint8_t old_license_code; //0x14B
    uint8_t rom_version; //0x14C
    uint8_t header_checksum; //0x14D
    uint16_t global_checksum; //0x14F - 0x14E

} header_struct;

typedef struct {
    header_struct rom_header;
    uint8_t * rom_data;
    uint16_t rom_size;
} rom_struct;

/// @brief Cartridge Class
class Cartridge {
    private:
        // methods
        bool _open_file(char * path);
        bool _check_header_checksum(header_struct data);
        uint8_t _header_checksum_math(uint8_t value);
        std::string _getCartridgeType(uint8_t value);
        std::string _getLicensee(uint8_t value);
        std::string _getRomSize(uint8_t value);
        std::string _getRamSize(uint8_t value);
        std::string _getDestinationCode(uint8_t value);
        std::string _getOldLicenseeCode(uint8_t value);
        int _getRomVersion(uint8_t value);

        // variables
        rom_struct _rom;
        static std::map<uint8_t, std::string> cartridgeTypeMap;
        static std::map<uint8_t, std::string> licenseeCodeMap;
        static std::map<uint8_t, std::string> romSizeMap;
        static std::map<uint8_t, std::string> ramSizeMap;
        static std::map<uint8_t, std::string> destinationCodeMap;

    public:
        // methods
        rom_struct load_cartridge(char * path);

};
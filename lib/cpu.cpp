//Own import
#include <cpu.hpp>

//Other component imports
#include <bus.hpp>

//System imports
#include <iostream>
#include <vector>

std::map<instruction, std::string>Cpu::instructionToStringMap = {
    {instruction::NOP, "NOP"},
    {instruction::JMP, "JMP"},
    {instruction::CALL, "CALL"},
    {instruction::INC, "INC"},
    {instruction::DEC, "DEC"},
    {instruction::LD, "LD"},
    {instruction::XOR, "XOR"},
    {instruction::JR, "JR"},
    {instruction::DI, "DI"},
    {instruction::LDH, "LDH"},
    {instruction::CP, "CP"}
};

std::map<address_location, std::string>Cpu::address_locationToStringMap = {
    {address_location::REG_A, "A"},
    {address_location::REG_F, "F"},
    {address_location::REG_B, "B"},
    {address_location::REG_C, "C"},
    {address_location::REG_D, "D"},
    {address_location::REG_E, "E"},
    {address_location::REG_H, "H"},
    {address_location::REG_L, "L"},
    {address_location::REG_SP, "SP"},
    {address_location::REG_PC, "PC"},
    {address_location::REG_AF, "AF"},
    {address_location::REG_BC, "BC"},
    {address_location::REG_DE, "DE"},
    {address_location::REG_HL, "HL"},
    {address_location::REG_HL_INC, "HL+"},
    {address_location::REG_HL_DEC, "HL-"},
    {address_location::n, "n"},
    {address_location::nn, "nn"},
    {address_location::e, "e"},
    {address_location::AD_NONE, ""}
};

std::map<cond_type, std::string>Cpu::cond_typeToStringMap = {
    {cond_type::COND_NZ, "NZ"},
    {cond_type::COND_Z, "Z"},
    {cond_type::COND_NC, "NC"},
    {cond_type::COND_C, "C"},
    {cond_type::COND_NONE, ""}
};

std::map<operation_type, std::string>Cpu::operation_typeToStringMap = {
    {operation_type::OP_8Bit, "8 Bit"},
    {operation_type::OP_16Bit, "16 Bit"},
    {operation_type::OP_manipulation, "Bit manipulation"},
    {operation_type::OP_controlFlow, "Control flow"},
    {operation_type::OP_cpuExecution, "Cpu Execution"}
};

std::map<uint8_t, operation> Cpu::operationMap = {
    {0x00, {instruction::NOP, address_location::AD_NONE, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_cpuExecution}},
    {0x02, {instruction::LD, address_location::REG_BC, address_location::REG_A, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x05, {instruction::DEC, address_location::REG_B, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x06, {instruction::LD, address_location::REG_B, address_location::n, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x0A, {instruction::LD, address_location::REG_A, address_location::REG_BC, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x0D, {instruction::DEC, address_location::REG_C, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x0E, {instruction::LD, address_location::REG_C, address_location::n, cond_type::COND_NONE, operation_type::OP_8Bit}},

    {0x11, {instruction::LD, address_location::REG_DE, address_location::nn, cond_type::COND_NONE, operation_type::OP_16Bit}},
    {0x12, {instruction::LD, address_location::REG_DE, address_location::REG_A, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x16, {instruction::LD, address_location::REG_D, address_location::n, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x1A, {instruction::LD, address_location::REG_A, address_location::REG_DE, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x1D, {instruction::DEC, address_location::REG_E, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x1E, {instruction::LD, address_location::REG_E, address_location::n, cond_type::COND_NONE, operation_type::OP_8Bit}},

    {0x20, {instruction::JR, address_location::AD_NONE, address_location::e, cond_type::COND_NZ, operation_type::OP_controlFlow}},
    {0x21, {instruction::LD, address_location::REG_HL, address_location::nn, cond_type::COND_NONE, operation_type::OP_16Bit}},
    {0x22, {instruction::LD, address_location::REG_HL_INC, address_location::REG_A, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x26, {instruction::LD, address_location::REG_H, address_location::n, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x2C, {instruction::INC, address_location::REG_L, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x2D, {instruction::DEC, address_location::REG_L, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x2E, {instruction::LD, address_location::REG_L, address_location::n, cond_type::COND_NONE, operation_type::OP_8Bit}},

    {0x32, {instruction::LD, address_location::REG_HL_DEC, address_location::REG_A, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x36, {instruction::LD, address_location::REG_HL, address_location::n, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x3D, {instruction::DEC, address_location::REG_A, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x3E, {instruction::LD, address_location::REG_A, address_location::n, cond_type::COND_NONE, operation_type::OP_8Bit}},

    {0x40, {instruction::LD, address_location::REG_B, address_location::REG_B, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x41, {instruction::LD, address_location::REG_B, address_location::REG_C, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x42, {instruction::LD, address_location::REG_B, address_location::REG_D, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x43, {instruction::LD, address_location::REG_B, address_location::REG_E, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x44, {instruction::LD, address_location::REG_B, address_location::REG_H, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x45, {instruction::LD, address_location::REG_B, address_location::REG_L, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x46, {instruction::LD, address_location::REG_B, address_location::REG_HL, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x47, {instruction::LD, address_location::REG_B, address_location::REG_A, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x48, {instruction::LD, address_location::REG_C, address_location::REG_B, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x49, {instruction::LD, address_location::REG_C, address_location::REG_C, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x4A, {instruction::LD, address_location::REG_C, address_location::REG_D, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x4B, {instruction::LD, address_location::REG_C, address_location::REG_E, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x4C, {instruction::LD, address_location::REG_C, address_location::REG_H, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x4D, {instruction::LD, address_location::REG_C, address_location::REG_L, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x4E, {instruction::LD, address_location::REG_C, address_location::REG_HL, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x4F, {instruction::LD, address_location::REG_C, address_location::REG_A, cond_type::COND_NONE, operation_type::OP_8Bit}},

    {0x50, {instruction::LD, address_location::REG_D, address_location::REG_B, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x51, {instruction::LD, address_location::REG_D, address_location::REG_C, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x52, {instruction::LD, address_location::REG_D, address_location::REG_D, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x53, {instruction::LD, address_location::REG_D, address_location::REG_E, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x54, {instruction::LD, address_location::REG_D, address_location::REG_H, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x55, {instruction::LD, address_location::REG_D, address_location::REG_L, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x56, {instruction::LD, address_location::REG_D, address_location::REG_HL, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x57, {instruction::LD, address_location::REG_D, address_location::REG_A, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x58, {instruction::LD, address_location::REG_E, address_location::REG_B, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x59, {instruction::LD, address_location::REG_E, address_location::REG_C, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x5A, {instruction::LD, address_location::REG_E, address_location::REG_D, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x5B, {instruction::LD, address_location::REG_E, address_location::REG_E, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x5C, {instruction::LD, address_location::REG_E, address_location::REG_H, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x5D, {instruction::LD, address_location::REG_E, address_location::REG_L, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x5E, {instruction::LD, address_location::REG_E, address_location::REG_HL, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x5F, {instruction::LD, address_location::REG_E, address_location::REG_A, cond_type::COND_NONE, operation_type::OP_8Bit}},
    
    {0x60, {instruction::LD, address_location::REG_H, address_location::REG_B, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x61, {instruction::LD, address_location::REG_H, address_location::REG_C, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x62, {instruction::LD, address_location::REG_H, address_location::REG_D, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x63, {instruction::LD, address_location::REG_H, address_location::REG_E, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x64, {instruction::LD, address_location::REG_H, address_location::REG_H, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x65, {instruction::LD, address_location::REG_H, address_location::REG_L, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x66, {instruction::LD, address_location::REG_H, address_location::REG_HL, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x67, {instruction::LD, address_location::REG_H, address_location::REG_A, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x68, {instruction::LD, address_location::REG_L, address_location::REG_B, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x69, {instruction::LD, address_location::REG_L, address_location::REG_C, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x6A, {instruction::LD, address_location::REG_L, address_location::REG_D, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x6B, {instruction::LD, address_location::REG_L, address_location::REG_E, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x6C, {instruction::LD, address_location::REG_L, address_location::REG_H, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x6D, {instruction::LD, address_location::REG_L, address_location::REG_L, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x6E, {instruction::LD, address_location::REG_L, address_location::REG_HL, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x6F, {instruction::LD, address_location::REG_L, address_location::REG_A, cond_type::COND_NONE, operation_type::OP_8Bit}},

    {0x70, {instruction::LD, address_location::REG_HL, address_location::REG_B, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x71, {instruction::LD, address_location::REG_HL, address_location::REG_C, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x72, {instruction::LD, address_location::REG_HL, address_location::REG_D, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x73, {instruction::LD, address_location::REG_HL, address_location::REG_E, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x74, {instruction::LD, address_location::REG_HL, address_location::REG_H, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x75, {instruction::LD, address_location::REG_HL, address_location::REG_L, cond_type::COND_NONE, operation_type::OP_8Bit}},
    // {0x76, HALT},
    {0x77, {instruction::LD, address_location::REG_HL, address_location::REG_A, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x78, {instruction::LD, address_location::REG_A, address_location::REG_B, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x79, {instruction::LD, address_location::REG_A, address_location::REG_C, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x7A, {instruction::LD, address_location::REG_A, address_location::REG_D, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x7B, {instruction::LD, address_location::REG_A, address_location::REG_E, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x7C, {instruction::LD, address_location::REG_A, address_location::REG_H, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x7D, {instruction::LD, address_location::REG_A, address_location::REG_L, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x7E, {instruction::LD, address_location::REG_A, address_location::REG_HL, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x7F, {instruction::LD, address_location::REG_A, address_location::REG_A, cond_type::COND_NONE, operation_type::OP_8Bit}},

    {0x90, {instruction::SUB, address_location::REG_B, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x91, {instruction::SUB, address_location::REG_C, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x92, {instruction::SUB, address_location::REG_D, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x93, {instruction::SUB, address_location::REG_E, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x94, {instruction::SUB, address_location::REG_H, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x95, {instruction::SUB, address_location::REG_L, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x96, {instruction::SUB, address_location::REG_HL, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0x97, {instruction::SUB, address_location::REG_A, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_8Bit}},

    {0xB8, {instruction::CP, address_location::REG_B, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0xB9, {instruction::CP, address_location::REG_C, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0xBA, {instruction::CP, address_location::REG_D, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0xBB, {instruction::CP, address_location::REG_E, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0xBC, {instruction::CP, address_location::REG_H, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0xBD, {instruction::CP, address_location::REG_L, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0xBE, {instruction::CP, address_location::REG_HL, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0xBF, {instruction::CP, address_location::REG_A, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_8Bit}},

    {0xC3, {instruction::JMP, address_location::nn, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_controlFlow}},
    {0xC4, {instruction::CALL, address_location::nn, address_location::AD_NONE, cond_type::COND_NZ, operation_type::OP_controlFlow}},

    {0xAF, {instruction::XOR, address_location::REG_A, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_8Bit}},

    {0xE0, {instruction::LDH, address_location::n, address_location::REG_A, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0xE2, {instruction::LDH, address_location::REG_C, address_location::REG_A, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0xEA, {instruction::LD, address_location::nn, address_location::REG_A, cond_type::COND_NONE, operation_type::OP_8Bit}},

    {0xF0, {instruction::LDH, address_location::REG_A, address_location::n, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0xF2, {instruction::LDH, address_location::REG_A, address_location::REG_C, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0xF3, {instruction::DI, address_location::AD_NONE, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_cpuExecution}},
    {0xFA, {instruction::LD, address_location::REG_A, address_location::nn, cond_type::COND_NONE, operation_type::OP_8Bit}},
    {0xFE, {instruction::CP, address_location::n, address_location::AD_NONE, cond_type::COND_NONE, operation_type::OP_8Bit}}

};

void Cpu::_initialize_address_location_map() {
    address8BitRegisterMap[address_location::REG_A] = &reg.a;
    address8BitRegisterMap[address_location::REG_F] = &reg.f;
    address8BitRegisterMap[address_location::REG_B] = &reg.b;
    address8BitRegisterMap[address_location::REG_C] = &reg.c;
    address8BitRegisterMap[address_location::REG_D] = &reg.d;
    address8BitRegisterMap[address_location::REG_E] = &reg.e;
    address8BitRegisterMap[address_location::REG_H] = &reg.h;
    address8BitRegisterMap[address_location::REG_L] = &reg.l;

    address16BitRegisterMap[address_location::REG_AF] = {&reg.a, &reg.f};
    address16BitRegisterMap[address_location::REG_BC] = {&reg.b, &reg.c};
    address16BitRegisterMap[address_location::REG_DE] = {&reg.d, &reg.e};
    address16BitRegisterMap[address_location::REG_HL] = {&reg.h, &reg.l};
    address16BitRegisterMap[address_location::REG_HL_DEC] = {&reg.h, &reg.l};
    address16BitRegisterMap[address_location::REG_HL_INC] = {&reg.h, &reg.l};
}


void Cpu::_initialize_registers() {
    _write_16bit_to_register(address_location::REG_AF, 0x01B0);
    _write_16bit_to_register(address_location::REG_BC, 0x0013);
    _write_16bit_to_register(address_location::REG_DE, 0x00D8);
    _write_16bit_to_register(address_location::REG_HL, 0x014D);
}

std::string Cpu::instructionToString(instruction instruction){
    return instructionToStringMap[instruction];
}
std::string Cpu::address_locationToString(address_location address_location){
    return address_locationToStringMap[address_location];
}
std::string Cpu::cond_typeToString(cond_type cond_type){
    return cond_typeToStringMap[cond_type];
}
std::string Cpu::operation_typeToString(operation_type operation_type){
    return operation_typeToStringMap[operation_type];
}


Cpu::Cpu(Bus * bus) {

    _bus = bus;

    reg.pc = 0x0100;

    _stack = new Stack(bus, &reg.sp);

    _initialize_address_location_map();
    _initialize_registers();

};

void Cpu::run() {

    uint8_t instruction;
    operation operation;

    while (true)
    {
        instruction = _bus->read(reg.pc++);
        std::cout << "PC: " << reg.pc << '\n';
        std::cout << "Executing instruction: 0x" << std::uppercase << std::hex << static_cast<int>(instruction) << "\n";
        if (operationMap.find(instruction) != operationMap.end()){
            operation = operationMap[instruction];
            std::cout << "Executing instruction: " << instructionToString(operation.inst) << " " << address_locationToString(operation.operand1) << " " << address_locationToString(operation.operand2) << ", with condition: " << cond_typeToString(operation.condition) << " and type: " << operation_typeToString(operation.type) << '\n';
            _execute_instruction(operation);
        }
        else {
            throw std::invalid_argument("NOT YET IMPLEMENTED");
        }
    }
}

void Cpu::_execute_instruction(operation operation) {

    uint8_t value_8bit;
    int8_t value_signed_8bit;
    uint16_t value_16bit;
    uint16_t address;

    switch (operation.inst)
    {
    case instruction::NOP:
        //do nothing
        break;

    case instruction::JMP:

        _fetch_data_to16Bit(operation.operand1, &reg.pc);

        break;

    case instruction::CALL:

        if (_check_condition(operation.condition)) {
            _push_stack((reg.pc & 0xFF00) >> 8);
            _push_stack(reg.pc & 0x00FF);
        }
        _fetch_data_to16Bit(operation.operand1, &reg.pc);

        break;

    case instruction::INC:
        _increment_register(operation.operand1);

        break;

    case instruction::DEC:
        _decrement_register(operation.operand1);

        break;

    case instruction::LD:

        if (operation.type == operation_type::OP_8Bit) {
            if (_isRegister(operation.operand2)) {
                value_8bit = _read_8bit_from_register(operation.operand2);
            }
            else if (operation.operand2 == address_location::nn) {
                _fetch_data_to16Bit(operation.operand2, &address);
                value_8bit = _bus->read(address);
            }
            else if (operation.operand2 == address_location::n) {
                _fetch_data_to8Bit(operation.operand2, &value_8bit);
            }
            else {
                throw std::invalid_argument("NOT YET IMPLEMENTED");
            }


            if (_isRegister(operation.operand1)) {
                _write_8bit_to_register(operation.operand1, value_8bit);
            }
            else if (operation.operand1 == address_location::nn) {
                _fetch_data_to16Bit(operation.operand1, &address);
                _bus->write(address, value_8bit);
            }
            else if (operation.operand1 == address_location::n) {
                _fetch_data_to8Bit(operation.operand1, &value_8bit);
            }
            else {
                throw std::invalid_argument("NOT YET IMPLEMENTED");
            }
        }


        if (operation.type == operation_type::OP_16Bit) {
            if (_isRegister(operation.operand2)) {
                value_16bit = _read_16bit_from_register(operation.operand2);
            }
            else if (operation.operand2 == address_location::nn) {
                _fetch_data_to16Bit(operation.operand2, &value_16bit);
            }
            else {
                throw std::invalid_argument("NOT YET IMPLEMENTED");
            }


            if (_isRegister(operation.operand1)) {
                _write_16bit_to_register(operation.operand1, value_16bit);
            }
            else if (operation.operand1 == address_location::nn) {
                uint8_t hiB = (uint8_t) ((0xFF00 & value_16bit) >> 8);
                uint8_t loB = (uint8_t) (0x00FF & value_16bit);

                _bus->write(hiB, reg.pc++);
                _bus->write(loB, reg.pc++);
            }
            else {
                throw std::invalid_argument("NOT YET IMPLEMENTED");
            }
        }

        if ((operation.operand1 || operation.operand2) == address_location::REG_HL_DEC) {
            _decrement_register(address_location::REG_HL_DEC); //TODO: this might put Z flag to true or false
        }

        if ((operation.operand1 || operation.operand2) == address_location::REG_HL_INC) {
            _increment_register(address_location::REG_HL_DEC);
        }

        break;
    
    case instruction::XOR:
        if (_isRegister(operation.operand1)) {
            value_8bit = _read_8bit_from_register(operation.operand1);
        }
        else {
            throw std::invalid_argument("NOT POSSIBLE");
        }
        reg.a ^= value_8bit;

        _set_flags(reg.a == 0, 0, 0, 0);

        break;

    case instruction::JR:
        _fetch_data_to_signed8Bit(operation.operand2, &value_signed_8bit);
        if (_check_condition(operation.condition)) {
            reg.pc += value_signed_8bit;
        }

        break;
    
    case instruction::DI:
        _ime = 0;
        break;

    case instruction::LDH:

        if (operation.operand2 != address_location::REG_A) {
            if (_isRegister(operation.operand2)) {
                value_8bit = _read_8bit_from_register(operation.operand2);
            } else {
                _fetch_data_to8Bit(operation.operand2, &value_8bit);
            }
            address = 0xFF00 + ((uint16_t) value_8bit);
            value_8bit = _bus->read(address);
            reg.a = value_8bit;
        }
        else if (operation.operand2 == address_location::REG_A) {
            if (_isRegister(operation.operand1)) {
                value_8bit = _read_8bit_from_register(operation.operand1);
            } else {
                _fetch_data_to8Bit(operation.operand1, &value_8bit);
            }
            address = 0xFF00 + ((uint16_t) value_8bit);
            value_8bit = _read_8bit_from_register(operation.operand2);
            _bus->write(address, value_8bit);
        }
        else {
            throw std::invalid_argument("NOT YET IMPLEMENTED");
        }
        break;

    case instruction::CP:
        if (_isRegister(operation.operand1)) {
            value_8bit = _read_8bit_from_register(operation.operand1);
        }
        else if (operation.operand1 == address_location::n) {
            _fetch_data_to8Bit(operation.operand1, &value_8bit);
        }
        else {
            throw std::invalid_argument("NOT YET IMPLEMENTED");
        }
        value_signed_8bit = reg.a - value_8bit;

        _set_flags(value_signed_8bit == 0, 1, (value_signed_8bit == -1 || value_signed_8bit == 0x0F), value_signed_8bit < 0);

        break;

    default:
        throw std::invalid_argument("NOT YET IMPLEMENTED");
        break;


    }

}





void Cpu::_set_flags(int8_t z, int8_t n, int8_t h, int8_t c) {
    if (z != -1) {
        BIT_SET(reg.f, 7, z);
    }

    if (n != -1) {
        BIT_SET(reg.f, 6, n);
    }

    if (h != -1) {
        BIT_SET(reg.f, 5, h);
    }

    if (c != -1) {
        BIT_SET(reg.f, 4, c);
    }
}


bool Cpu::_check_condition(cond_type condition) {
    
    switch (condition)
    {
    case cond_type::COND_NZ:
        return ! (bool)FLAG_Z;
    case cond_type::COND_Z:
        return (bool)FLAG_Z;
    case cond_type::COND_NC:
        return ! (bool)FLAG_C;
    case cond_type::COND_C:
        return (bool)FLAG_C;
    default:
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }
}

void Cpu::_push_stack(uint8_t value) {
    throw std::invalid_argument("NOT YET IMPLEMENTED");
}


bool Cpu::_isRegister(address_location address) {
    if (address8BitRegisterMap.find(address) != address8BitRegisterMap.end() || address16BitRegisterMap.find(address) != address16BitRegisterMap.end() ) {
        return true;
    }
    else {
        return false;
    }
}

uint8_t Cpu::_read_8bit_from_register(address_location address) {
    std::vector<uint8_t*>  address_vector;

    if (address8BitRegisterMap.find(address) != address8BitRegisterMap.end()) {
        return *address8BitRegisterMap[address];
    }
    else if (address16BitRegisterMap.find(address) != address16BitRegisterMap.end()) {
        address_vector = address16BitRegisterMap[address];
        return _bus->read(((uint16_t) *(address_vector[0]) << 8 ) | *(address_vector[1]));
    }
    else {
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }
}

void Cpu::_write_8bit_to_register(address_location address, uint8_t value) {
    std::vector<uint8_t*>  address_vector;

    if (address8BitRegisterMap.find(address) != address8BitRegisterMap.end()) {
        *address8BitRegisterMap[address] = value;
    }
    else if (address16BitRegisterMap.find(address) != address16BitRegisterMap.end()) {
        address_vector = address16BitRegisterMap[address];
        return _bus->write(( ((uint16_t) *(address_vector[0]) << 8 ) | *(address_vector[1])), value);
    }
    else {
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }
}


uint16_t Cpu::_read_16bit_from_register(address_location address) {
    std::vector<uint8_t*>  address_value;

    if (address8BitRegisterMap.find(address) != address8BitRegisterMap.end()) {
        throw std::invalid_argument("NOT AN OPERATION");
    }
    else if (address16BitRegisterMap.find(address) != address16BitRegisterMap.end()) {
        address_value = address16BitRegisterMap[address];
        return (((uint16_t) *(address_value[0]) << 8 ) | *(address_value[1]));
    }
    else {
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }
}


void Cpu::_write_16bit_to_register(address_location address, uint16_t value) {
    std::vector<uint8_t*>  address_vector;

    if (address8BitRegisterMap.find(address) != address8BitRegisterMap.end()) {
        throw std::invalid_argument("NOT AN OPERATION");
    }
    else if (address16BitRegisterMap.find(address) != address16BitRegisterMap.end()) {
        address_vector = address16BitRegisterMap[address];
        *(address_vector[0]) = (uint8_t) (((0xFF00) & value) >> 8);
        *(address_vector[1]) = (uint8_t) ((0x00FF) & value);
    }
    else {
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }
}


void Cpu::_increment_register(address_location address) {

    if (address8BitRegisterMap.find(address) != address8BitRegisterMap.end()) {
        (*address8BitRegisterMap[address])++;

        _set_flags( (*address8BitRegisterMap[address]) == 0, 0, ((*address8BitRegisterMap[address]) & 0x0F) == 0, -1);
    }
    else {
        switch (address)
        {
        case address_location::REG_BC:
            _increment_16bit(&reg.b, &reg.c);
            _set_flags( reg.c == 0, 0, (reg.c & 0x0F) == 0, -1);
            break;
        case address_location::REG_DE:
            _increment_16bit(&reg.d, &reg.e);
            _set_flags( reg.e == 0, 0, (reg.e& 0x0F) == 0, -1);
            break;
        case address_location::REG_HL:
            _increment_16bit(&reg.h, &reg.l);
            _set_flags( reg.l == 0, 0, (reg.l& 0x0F) == 0, -1);
            break;
        default:
            throw std::invalid_argument("NOT YET IMPLEMENTED");
            break;
        }
    }
}

void Cpu::_increment_16bit(uint8_t * high, uint8_t * low) {
    uint16_t value = ((uint16_t) *high << 8) | *low;

    value++;

    *high = (uint8_t) ((0xFF00 & value) >> 8);
    *low = (uint8_t) ((0x00FF & value));

}

void Cpu::_decrement_register(address_location address) {

    if (address8BitRegisterMap.find(address) != address8BitRegisterMap.end()) {
        (*address8BitRegisterMap[address])--;
        _set_flags( (*address8BitRegisterMap[address]) == 0, 1, ((*address8BitRegisterMap[address]) & 0x0F) == 0x0F, -1);
    }
    else {
        switch (address)
        {
        case address_location::REG_BC:
            _decrement_16bit(&reg.b, &reg.c);
            _set_flags( reg.c == 0, 1, (reg.c & 0x0F) == 0x0F, -1);
            break;
        case address_location::REG_DE:
            _decrement_16bit(&reg.d, &reg.e);
            _set_flags( reg.e == 0, 1, (reg.e & 0x0F) == 0x0F, -1); //TODO: Not taking reg.d into account
            break;
        case address_location::REG_HL:
            _decrement_16bit(&reg.h, &reg.l);
            _set_flags( reg.l == 0, 1, (reg.l & 0x0F) == 0x0F, -1);
            break;
        default:
            throw std::invalid_argument("NOT YET IMPLEMENTED");
            break;
        }
    }
}

void Cpu::_decrement_16bit(uint8_t * high, uint8_t * low) {
    uint16_t value = ((uint16_t) *high << 8) | *low;

    value--;

    *high = (uint8_t) ((0xFF00 & value) >> 8);
    *low = (uint8_t) ((0x00FF & value));

}

void Cpu::_fetch_data_to16Bit(address_location address, uint16_t * value) {

    uint8_t hiB;
    uint8_t loB;

    if (address == address_location::nn) {
        loB = _bus->read(reg.pc++);
        hiB = _bus->read(reg.pc++);
        *value = ((uint16_t) hiB << 8 ) | loB;
    }
    else {
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }

}

void Cpu::_fetch_data_to8Bit(address_location address, uint8_t * value) {

    if (address == address_location::n || address == address_location::e) {
        *value = _bus->read(reg.pc++);
    }
    else {
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }

}

void Cpu::_fetch_data_to_signed8Bit(address_location address, int8_t * value) {

    if (address == address_location::n || address == address_location::e) {
        *value = _bus->read(reg.pc++);
    }
    else {
        throw std::invalid_argument("NOT YET IMPLEMENTED");
    }

}
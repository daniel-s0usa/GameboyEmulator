#pragma once

#include <bus.hpp>
#include <stack.hpp>

#include <vector>

struct Reg{
    uint8_t a; 
    uint8_t f;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    uint16_t sp;
    uint16_t pc;
};

typedef enum{
    NOP,
    JMP,
    CALL,
    INC,
    DEC,
    LD,
    SUB,
    XOR,
    JR
} instruction;

typedef enum{
    REG_A,
    REG_F,
    REG_B,
    REG_C,
    REG_D,
    REG_E,
    REG_H,
    REG_L,
    REG_SP,
    REG_PC,
    REG_AF, // REG_A and REG_F (16bit)
    REG_BC, // REG_B and REG_C (16bit)
    REG_DE, // REG_D and REG_E (16bit)
    REG_HL, // REG_H and REG_L (16bit)
    REG_HL_DEC,
    REG_HL_INC,
    n,  // the following 8bit
    nn, // the following 16bit
    e,  // relative Jump
    AD_NONE
} address_location;

typedef enum {
    COND_NZ,
    COND_Z,
    COND_NC,
    COND_C,
    COND_NONE
} cond_type;

typedef enum {
    OP_8Bit,
    OP_16Bit,
    OP_manipulation,
    OP_controlFlow,
    OP_cpuExecution,
    OP_Undefined,
} operation_type;

typedef struct{
    instruction inst;
    address_location operand1;
    address_location operand2;
    cond_type condition;
    operation_type type;
} operation;

#define BIT(a, n) (a & (1 << n));
#define BIT_SET(a, n, one) { if (one) a |= (1 << n); else a &= ~(1 << n);}

#define FLAG_Z BIT(reg.f, 7);
#define FLAG_N BIT(reg.f, 6);
#define FLAG_H BIT(reg.f, 5);
#define FLAG_C BIT(reg.f, 4);


class Cpu {
    private:
        // methods
        uint8_t _fetch_instruction(uint16_t);
        void _fetch_data_to16Bit(address_location address, uint16_t * value);
        void _fetch_data_to8Bit(address_location address, uint8_t * value);
        void _fetch_data_to_signed8Bit(address_location address, int8_t * value);
        void _execute_instruction(operation operation);
        bool _check_condition(cond_type condition);
        void _push_stack(uint8_t value);

        void _increment_16bit(uint8_t * high, uint8_t * low);
        void _increment_register(address_location);
        void _decrement_16bit(uint8_t * high, uint8_t * low);
        void _decrement_register(address_location);

        uint8_t _read_8bit_from_register(address_location);
        void _write_8bit_to_register(address_location address, uint8_t value);
        uint16_t _read_16bit_from_register(address_location);
        void _write_16bit_to_register(address_location address, uint16_t value);

        bool _isRegister(address_location address);

        void _set_flags(int8_t z = -1, int8_t n = -1, int8_t h = -1, int8_t c = -1);

        void _initialize_address_location_map();
        void _initialize_registers();

        
        // Variables
        Bus * _bus;
        Stack * _stack;
        Reg reg;

        // Maps
        static std::map<uint8_t, operation> operationMap;
        std::map<address_location, uint8_t*> address8BitRegisterMap;
        std::map<address_location, std::vector<uint8_t*> > address16BitRegisterMap;
        static std::map<instruction, std::string>instructionToStringMap;
        static std::map<address_location, std::string>address_locationToStringMap;
        static std::map<cond_type, std::string>cond_typeToStringMap;
        static std::map<operation_type, std::string>operation_typeToStringMap;


    public:
        // methods
        Cpu (Bus * bus);
        void run();
        std::string instructionToString(instruction instruction);
        std::string address_locationToString(address_location address_location);
        std::string cond_typeToString(cond_type cond_type);
        std::string operation_typeToString(operation_type operation_type);

};
#pragma once

#include <cartridge.hpp>
#include <cpu.hpp>
#include <bus.hpp>


class Emulator {
    private:
        Cartridge * cart;
        Bus * bus;
        Cpu * cpu;



    public:
        int run( int argc, char ** argv);

};
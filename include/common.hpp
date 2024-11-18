#pragma once

#include <cartridge.hpp>
#include <cpu.hpp>
#include <bus.hpp>

typedef struct {

    Cartridge * cart;
    Cpu * cpu;
    Bus * bus;

} emulator_components;
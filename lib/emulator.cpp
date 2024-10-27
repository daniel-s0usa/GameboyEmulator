//Own import
#include <emulator.hpp>

//Other component imports
#include <cartridge.hpp>
#include <cpu.hpp>

//System imports
#include <iostream>



int Emulator::run(int argc, char ** argv) {
    if ( argc != 2 ) {
        return 0;
    }

    //load cart
    Cartridge cart;
    rom_struct rom = cart.load_cartridge(argv[1]);

    Cpu cpu;

    cpu.init();
    


    return 1;
}



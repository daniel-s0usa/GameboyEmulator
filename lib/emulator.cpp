//Own import
#include <emulator.hpp>

//Other component imports
#include <cartridge.hpp>
#include <cpu.hpp>
#include <bus.hpp>

//System imports
#include <iostream>



int Emulator::run(int argc, char ** argv) {
    if ( argc != 2 ) {
        return 0;
    }
    cart = new Cartridge(argv[1]); //init cartridge (load and interpret cartridge contents)
    bus = new Bus(cart);
    cpu = new Cpu(bus);
    

    while (true) {

        cpu->run();


    }

    return 1;
}



#pragma once

#include <bus.hpp>

class Stack {
    private:

    Bus * _bus;
    uint16_t * _sp;


    public:
        // Constructor
        Stack(Bus * bus, uint16_t * sp);

        void push(uint8_t);
        uint8_t pop();

};
//Own import
#include <stack.hpp>

//Other component imports
#include <bus.hpp>

//System imports


Stack::Stack (Bus * bus, uint16_t * sp) {
    _bus = bus;
    _sp = sp;
}

void Stack::push(uint8_t value){
    _sp--;
    _bus->write(*_sp, value);
}

uint8_t Stack::pop() {

    uint8_t value = _bus->read(*_sp);
    _sp++;
    return value;

}

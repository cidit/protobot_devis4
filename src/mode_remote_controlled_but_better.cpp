#include "modes.hpp"
#include "dels.hpp"
#include "telecommande.hpp"

uint32_t RemoteControlledButBetter::get_associated_color() 
{
    return make_color(255, 255, 0);
}

String RemoteControlledButBetter::get_name() 
{
    return "RemoteControlledButBetter";
}

void RemoteControlledButBetter::reset()
{
    _speed = 0;
}

void RemoteControlledButBetter::loop()
{
    // TODO: LAST
}
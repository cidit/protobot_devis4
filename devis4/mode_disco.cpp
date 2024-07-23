#include "modes.hpp"
#include "dels.hpp"
#include "roues.hpp"
#include "constants.hpp"

uint32_t Disco::get_associated_color()
{
    return make_color(0, 255, 255);
}

String Disco::get_name()
{
    return "Disco";
}

void Disco::reset()
{
    _start_of_dance = millis();
}

void Disco::loop()
{
    const auto SPEED = 40;
    const auto COLOR_COUNT = 6;
    const int COLORS[COLOR_COUNT] = {
        make_color(255, 0, 0),
        make_color(0, 255, 0),
        make_color(0, 0, 255),
        make_color(255, 255, 0),
        make_color(0, 255, 255),
        make_color(255, 0, 255)
    };

    auto time_since_start = millis() - _start_of_dance;

    // la vitesse de rotation du robot est une fonction du temps.
    auto step_percentage = float(time_since_start % ONE_SECOND) / ONE_SECOND;
    tourner(0, SPEED * step_percentage);
    
    // on passe à une couleur aléatoire à chaques secondes.
    if (time_since_start % ONE_SECOND == 0)
    {
        auto color_idx = random(COLOR_COUNT);
        changerCouleur(COLORS[color_idx]);
    }
}
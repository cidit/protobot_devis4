#include "modes.hpp"
#include "dels.hpp"
#include "ultrason.hpp"
#include "roues.hpp"
#include <Touches.h>
#include "constants.hpp"

const auto EXPLORER_SPEED = 30;
const auto SLOWDOWN_DISTANCE = 300; // millimètres
const auto EXPLORER_TURN_TIME = ONE_SECOND * 0.5;

Explorer::Explorer(Touches *touches) : _touches(touches) {}

uint32_t Explorer::get_associated_color()
{
    return make_color(0, 255, 0);
}

String Explorer::get_name()
{
    return "Explorer";
}

void Explorer::reset()
{
    // no-op
}

unsigned long last_bumper_left = 0L, last_bumper_right = 0L;

void Explorer::loop()
{
    auto now = millis();
    if (_touches->parechocDroite.isOnPress())
    {
        last_bumper_right = now;
    }
    if (_touches->parechocGauche.isOnPress())
    {
        last_bumper_left = now;
    }

    // on veut que le robot recule seulement EXPLORER_TURN_TIME.
    if (last_bumper_left + EXPLORER_TURN_TIME > now)
    {
        tourner(-EXPLORER_SPEED / 2, -EXPLORER_SPEED);
    }
    else if (last_bumper_right + EXPLORER_TURN_TIME > now)
    {
        tourner(-EXPLORER_SPEED, -EXPLORER_SPEED / 2);
    }
    else
    {
        // si on n'est pas en train de reculer, on veut avancer.
        // si la distance le permet, on avance à pleine vitesse. sinon, la vitesse est une fonction de la distance au prochain obstacle (détecté avec le capteur ultrason).
        auto distance = getDistance();
        if (distance != -1 && distance <= SLOWDOWN_DISTANCE)
        {
            // Réduction graduelle de la vitesse proportionnellement à la distance du mur, mais elle ne decendra jamais sous 20 parce que on veut que les pare-chocs ne prennent pas trops de temps à s'activer.
            auto new_explorer_speed = EXPLORER_SPEED * distance / SLOWDOWN_DISTANCE;
            tourner(new_explorer_speed, new_explorer_speed);
        }
        else
        {
            tourner(EXPLORER_SPEED, EXPLORER_SPEED);
        }
    }
}
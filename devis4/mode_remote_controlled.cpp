#include "modes.hpp"
#include "telecommande.hpp"
#include "dels.hpp"
#include "roues.hpp"

uint32_t RemoteControlled::get_associated_color()
{
    return make_color(255, 0, 0);
}

String RemoteControlled::get_name()
{
    return "RemoteControlled";
}

void RemoteControlled::reset()
{
    this->_speed = 0.5;
}

void RemoteControlled::loop()
{
    Serial.println(_speed);
    auto command = getLastCodeRecu();

    // Lorsqu'on change la vitesse et uniquement dans ce cas, on veut réinviquer la dernière commande pour appliquer tout de suite le changement de vitesse aux roues.
    switch (command)
    {
    case REMOTE_BUTTON_CODES::VOL_PLUS:
        _speed = constrain(_speed + 0.005, 0, 1);
        apply_wheel_change(_last_command);
        break;
    case REMOTE_BUTTON_CODES::VOL_MINUS:
        _speed = constrain(_speed - 0.005, 0, 1);
        apply_wheel_change(_last_command);
        break;
    default:
        apply_wheel_change(command);
    }
    _last_command = command;
}

/** 
 * Cette fonction géris le fonctionnement des roues seulement.
 * @param command La commande qui détermine quoi faire avec les roues.
*/
void RemoteControlled::apply_wheel_change(REMOTE_BUTTON_CODES command) {
    switch (command)
    {
    case REMOTE_BUTTON_CODES::N_2: // avant
        tourner(_speed * 100, _speed * 100);
        break;
    case REMOTE_BUTTON_CODES::N_8: // arrière
        tourner(_speed * -100, _speed * -100);
        break;
    case REMOTE_BUTTON_CODES::N_5: // arrèt
        tourner(_speed * 0, _speed * 0);
        break;
    case REMOTE_BUTTON_CODES::N_4: // rotation gauche
        tourner(_speed * -50, _speed * 50);
        break;
    case REMOTE_BUTTON_CODES::N_6: // rotation droite
        tourner(_speed * 50, _speed * -50);
        break;
    case REMOTE_BUTTON_CODES::N_1: // avancer vers la gauche
        tourner(_speed * 75, _speed * 100);
        break;
    case REMOTE_BUTTON_CODES::N_3: // avancer vers la droite
        tourner(_speed * 100, _speed * 75);
        break;
    case REMOTE_BUTTON_CODES::N_7: // reculer vers la gauche
        tourner(_speed * -75, _speed * -100);
        break;
    case REMOTE_BUTTON_CODES::N_9: // reculer vers la droite
        tourner(_speed * -100, _speed * -75);
        break;
    default:
        break;
    }
}
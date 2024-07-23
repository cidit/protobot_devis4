#include "modes.hpp"
#include "dels.hpp"
#include "telecommande.hpp"
#include "buzzer.hpp"
#include "constants.hpp"

uint32_t Instrument::get_associated_color()
{
    return make_color(255, 0, 255);
}

String Instrument::get_name()
{
    return "Instrument";
}

void Instrument::reset()
{
    // no-op
}

void Instrument::loop()
{
    auto command = getLastCodeRecu();
    if (command == INVALID)
    {
        // Si aucune touche n'est appuyées, on quitte.
        eteindreBuzzer();
        return;
    }

    // On cherche à produire une tonalitée à un interval régulier. On veut aussi changer la couleur à chaque pesée de bouton, pour rajouter un effet fun.
    switch (command)
    {
    case N_1:
        changerCouleur(255, 255, 255);
        buzzDelay(ONE_SECOND * 0.01);
        break;
    case N_2:
        changerCouleur(0, 255, 255);
        buzzDelay(ONE_SECOND * 0.009);
        break;
    case N_3:
        changerCouleur(0, 0, 255);
        buzzDelay(ONE_SECOND * 0.008);
        break;
    case N_4:
        changerCouleur(255, 0, 0);
        buzzDelay(ONE_SECOND * 0.007);
        break;
    case N_5:
        changerCouleur(255, 255, 0);
        buzzDelay(ONE_SECOND * 0.006);
        break;
    case N_6:
        changerCouleur(0, 255, 0);
        buzzDelay(ONE_SECOND * 0.005);
        break;
    case N_7:
        changerCouleur(0, random(255), 0);
        buzzDelay(ONE_SECOND * 0.004);
        break;
    case N_8:
        changerCouleur(random(255), 0, 0);
        buzzDelay(ONE_SECOND * 0.003);
        break;
    case N_9:
        changerCouleur(0, 0, random(255));
        buzzDelay(ONE_SECOND * 0.002);
        break;
    case N_0:
        changerCouleur(0, 0, 0);
        buzzDelay(ONE_SECOND * 0.001);
    default:
        break;
    }
}
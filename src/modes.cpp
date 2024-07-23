#include "modes.hpp"
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "roues.hpp"
#include "constants.hpp"
#include "dels.hpp"

/**
 * Renouvelle l'état initial de la stratégie. Indique quel mode viens d'être activé en clignotant les dels de la couleur du mode.
*/
void ModeStrategy::runTransition()
{
    this->reset();
    tourner(0, 0);
    auto color = this->get_associated_color();
    const auto BLACK = make_color(0, 0, 0);
    const auto FLASH_INDICATOR_AMOUNT = 3;
    const auto FLASH_DELAY = ONE_SECOND * 0.125;
    for (auto i = 0; i < FLASH_INDICATOR_AMOUNT; i++)
    {
        changerCouleur(color);
        delay(FLASH_DELAY);
        changerCouleur(BLACK);
        delay(FLASH_DELAY);
    }
}

/**
 * Lie les stratégies du tableau passé en paramètres de manière à créer une liste chainée cyclique.
 * @param strategies Les stratégies à lier ensembles.
 * @param length La longueur du tableau.
*/
void ModeStrategy::chainStrategies(ModeStrategy *strategies[], size_t length)
{
    // sliding winddow algorithm
    for (size_t i = 0; i < length - 1; i++)
    {
        strategies[i]->_next = strategies[i + 1];
        strategies[i + 1]->_prev = strategies[i];
    }
    strategies[0]->_prev = strategies[length - 1];
    strategies[length - 1]->_next = strategies[0];
}

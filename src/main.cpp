#include <Arduino.h>
#include <Wire.h>
#include <Touches.h>
#include "buzzer.hpp"
#include "dels.hpp"
#include "i2c.hpp"
#include "roues.hpp"
#include "telecommande.hpp"
#include "ultrason.hpp"
#include "suiveurs.hpp"
#include "constants.hpp"
#include "modes.hpp"

Touches touches(&Wire);
SensorCalibration line_follower_calibration {
    {SENSOR_MID_VALUE, SENSOR_MID_VALUE, SENSOR_MID_VALUE, SENSOR_MID_VALUE, SENSOR_MID_VALUE},
    {SENSOR_MID_VALUE, SENSOR_MID_VALUE, SENSOR_MID_VALUE, SENSOR_MID_VALUE, SENSOR_MID_VALUE},
};

RemoteControlled remote_controlled_mode;
Explorer explorer_mode{&touches};
Disco disco_mode;
LineFollower line_follower_mode{&line_follower_calibration, &touches};
Instrument instrument_mode;
Calibration calibration_mode{&line_follower_calibration};
ModeStrategy *current_mode;

void setup()
{
    // initialisation de tous nos capteurs et periphériques.
    Serial.begin(115200);
    initI2C();
    initDels();
    initRoues();
    initTelecommande();
    initUltrason();
    initSuiveur();
    touches.begin();

    // Liaison des stratégies entre elles. Pour plus d'infromations, consulter la documentation dans `modes.hpp`.
    const size_t HOW_MANY_STRATEGIES = 6;
    ModeStrategy *strategies[HOW_MANY_STRATEGIES] = {&remote_controlled_mode,
                                                     &explorer_mode,
                                                     &disco_mode,
                                                     &line_follower_mode,
                                                     &instrument_mode,
                                                     &calibration_mode};
    ModeStrategy::chainStrategies(strategies, HOW_MANY_STRATEGIES);

    // La première stratégie est celle qu'on vas utiliser par défaut. On veut aussi executer sa transition immédiatement.
    current_mode = strategies[0];
    current_mode->runTransition();
}

/**
 * Rapporte le nom du mode actuellement sélectionné dans le port série.
*/
void raporterNomModeActuel() {
    // On affiche le nom du mode à toutes les secondes pour éviter de rendre le port série inutilisable.
    if (millis() % 1000 == 0)
    {
        Serial.println(current_mode->get_name());
    }
}

void loop()
{
    touches.refresh();
    refreshTelecommande();
    auto command = getLastCodeRecu();
    if (command != INVALID)
    {
        rapporterCommande(command);
    }

    // Cette partie du code sert à changer de mode. La transition de chaques modes est roulée à chaque fois qu'ils sont activés.
    bool must_go_next_mode = touches.droite.isPressed() || command == REMOTE_BUTTON_CODES::NEXT,
        must_go_prev_mode = touches.gauche.isPressed() || command == REMOTE_BUTTON_CODES::PREV;
    if (must_go_next_mode)
    {
        current_mode = current_mode->get_next();
        current_mode->runTransition();
    }
    else if (must_go_prev_mode)
    {
        current_mode = current_mode->get_prev();
        current_mode->runTransition();
    }

    raporterNomModeActuel();
    Sting
    current_mode->loop();
}
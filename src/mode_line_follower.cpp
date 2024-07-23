#include "modes.hpp"
#include "dels.hpp"
#include "suiveurs.hpp"
#include "roues.hpp"
#include "constants.hpp"
#include <Touches.h>

const int BASE_SPEED = 25;

LineFollower::LineFollower(SensorCalibration *calibration, Touches *touches) : _calibration(calibration), _touches(touches) {}

uint32_t LineFollower::get_associated_color()
{
    return make_color(0, 0, 255);
}

String LineFollower::get_name()
{
    return "LineFollower";
}

void LineFollower::reset()
{
    // no-op
}

/**
 * Calibration du devis.
 * @param calibration L'endroit où seront écrites les données de calibration.
*/
void calibration_du_devis(SensorCalibration *calibration)
{
    auto start = millis();

    // on fait tourner le robot sur lui même.
    tourner(50, -50);
    int sensor_values[NOMBRE_SENSORS];

    // on fais le contenu du while pour les 5 prochaines secondes
    while (start + 5 * ONE_SECOND > millis())
    {
        suiveurRefresh(sensor_values);
        for (int i = 0; i < NOMBRE_SENSORS; i++)
        {
            if (sensor_values[i] < calibration->min[i])
            {
                calibration->min[i] = sensor_values[i];
            }
            else if (sensor_values[i] > calibration->max[i])
            {
                calibration->max[i] = sensor_values[i];
            }
        }
    }

    // on arrête de tourner après la calibration achevée.
    tourner(0, 0);
}

void LineFollower::loop()
{
    auto command = getLastCodeRecu();
    if (command == REMOTE_BUTTON_CODES::EQUALIZER || _touches->bas.isPressed())
    {
        calibration_du_devis(_calibration);
    }

    int sensor_values[NOMBRE_SENSORS];
    suiveurRefresh(sensor_values);
    // On reutilise le tableau de sensor values pour sauver de l'espace.
    rectify_sensor_values(sensor_values, _calibration, sensor_values);
    float position = getPosition(sensor_values);
    // Gros gossage, semi-aléatoire pour avoir un suiveur qui a de l'allure.
    // *Noter l'ajout de la fonction exponentielle pour tourner sec quand on s'éloigne trops.
    float turn_factor = constrain(1 - pow(abs(position), 0.2), 0, 1);

    if (position < 0)
    {
        tourner(BASE_SPEED, BASE_SPEED * turn_factor);
    }
    else if (position > 0)
    {
        tourner(BASE_SPEED * turn_factor, BASE_SPEED);
    }
    else
    {
        tourner(BASE_SPEED, BASE_SPEED);
    }
}
#include "modes.hpp"
#include "dels.hpp"
#include "suiveurs.hpp"
#include <Arduino.h>

Calibration::Calibration(SensorCalibration *calibration) : _calibration(calibration) {}

uint32_t Calibration::get_associated_color()
{
    return make_color(255, 255, 255);
}

String Calibration::get_name()
{
    return "Calibration";
}

void Calibration::reset()
{
    // no-op
}

void Calibration::loop()
{
    int sensor_values[NOMBRE_SENSORS];
    suiveurRefresh(sensor_values);
    auto new_calibration = update_calibration(_calibration, sensor_values);
    // Ici, on cherche à aller changer la calibration déclarée dans l'espace global du main.
    *_calibration = new_calibration;
    
    // -------- Impression des données
    for (int i = 0; i < NOMBRE_SENSORS; i++)
    {
        Serial.print(String(_calibration->min[i]) + '\t');
        Serial.print(String(_calibration->max[i]) + '\t');
        Serial.print(String(sensor_values[i]) + '\t');
        Serial.print("|\t");
    }

    // Ici, on viens rectifier la valeur des senseurs avant de chercher la position pour donner une idée à l'utilisateur de la forme des données. On réutilise notre tableau de senseurs pour recycler notre espace memoire. 
    rectify_sensor_values(sensor_values, _calibration, sensor_values);
    auto pos = getPosition(sensor_values);
    Serial.print("rectified pos:" + String(pos));
    Serial.println();
    // --------- Fin des impressions des données
}
#pragma once

/*
  Programme:       AlphaBot2_suivueur.ino
  Date:             23 avril 2024
  Auteur:           Claude Bouchard
  Pltform matériel: Arduino Uno
  Pltform develop : Arduino 2.2.1
  Description:      Exemple pour lire et décoder le suiveur de lignes
  Fonctionnalités:  Communique via SPI au convertisseur pour obtenir la lecture des 5 capteurs infrarouges.
  Notes:            ADAPTÉ PAR FÉLIX ST-GELAIS pour être utilisé avec d'autres programmes.

  -- Inspirations et credits: --
https://www.waveshare.com/wiki/AlphaBot2-Ar

*/

/* --- Materiel et composants -------------------------------------------
 * Robot AlphaBot2-Ar
 *
 */

//--- Definitions -------------------------------------------------------
#define SUIVEUR_SPI_CLOCK 13
#define SUIVEUR_SPI_ADDRESS 12
#define SUIVEUR_SPI_DATAOUT 11
#define SUIVEUR_SPI_CS 10

const auto RECTIFIED_MAX = 1000, RECTIFIED_MIN = 0;
#define NOMBRE_SENSORS 5

struct SensorCalibration
{
  int min[NOMBRE_SENSORS], max[NOMBRE_SENSORS];
};

void initSuiveur();
float getPosition(int capteurs[NOMBRE_SENSORS]);
SensorCalibration update_calibration(SensorCalibration *old_calibration, int changes[NOMBRE_SENSORS]);
void suiveurRefresh(int out_capteurs[NOMBRE_SENSORS]);
void rectify_sensor_values(int sensor_values[NOMBRE_SENSORS], SensorCalibration *calibration, int out_rectified_sensor_values[NOMBRE_SENSORS]);

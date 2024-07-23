#include <Arduino.h>
#include "Adafruit_BusIO_Register.h"
#include "Adafruit_SPIDevice.h"
#include "suiveurs.hpp"

// CRÉDITS: les fonctions suiveurRefresh et initSuiveur ont étés écrites par Claude Bouchard <https://github.com/dualB>

/**
 Calcule la position estimée de la ligne
 @param capteurs: Tableau de ints dans lequel la valeur des capteurs est lue.
 @returns une valeur numérique entre -1 et +1
*/
float getPosition(int capteurs[NOMBRE_SENSORS])
{
    // Dans cette fonction, on fais une distribution pondérée des valeurs des senseurs pour
    // déterminer la position de la ligne en dessous.
    auto captors_values_sum = 0;
    for (int i = 0; i < NOMBRE_SENSORS; i++)
    {
        captors_values_sum += capteurs[i];
    }
    if (captors_values_sum == 0)
    {
        // On évite une division par zéro.
        return 0;
    }
    auto numerateur = 0.0;
    for (auto i = 0; i < 5; i++)
    {
        numerateur += i * capteurs[i];
    }
    // on décale
    auto position = (numerateur / captors_values_sum);
    return (position-2)/2;
}

/*
 Fonction: Initialise les broches pour la communication SPI
 Argument(s) réception: -
 Argument(s) de retour: -
 Modifie/utilise (globale): -
*/
void initSuiveur()
{
    pinMode(SUIVEUR_SPI_CLOCK, OUTPUT);
    pinMode(SUIVEUR_SPI_ADDRESS, OUTPUT);
    pinMode(SUIVEUR_SPI_DATAOUT, INPUT);
    pinMode(SUIVEUR_SPI_CS, OUTPUT);
}

/*
 Fonction: Communique selon le protocole SPI avec le convertisseur et stocke les valeurs lues des capteurs infrarouges
 Argument(s) réception:
 - out_capteurs: Tableau de ints dans lequel la valeur des capteurs sera écrite.
 Argument(s) de retour: -
 Modifie/utilise (globale): le tableau "capteurs" est mis à jour

*/
void suiveurRefresh(int out_capteurs[NOMBRE_SENSORS])
{

  int i, j;

  unsigned int values[NOMBRE_SENSORS * 2]; //Initialisation du tableau temporaire de lecture
  for (i = 0; i < NOMBRE_SENSORS * 2; i++) {
    values[i] = 0;
  }

  //Boucle pour chacun des 5 capteurs; On doit effectuer une itération de plus car la valeur
  //demandée via le SPI sera reçue à la communication suivante
  for (j = 0; j < NOMBRE_SENSORS + 1; j++) { 
    digitalWrite(SUIVEUR_SPI_CS, LOW);
    
    //Enovi des 8 premiers bits
    for (i = 0; i < 8; i++) {
      if (i < 4) { 
        //Durant les 4 premiers bits, on envoie l'adresse du capteur à lire (0,1,2,3 et 4)
        if ((j >> (3 - i) & 0x01))
          digitalWrite(SUIVEUR_SPI_ADDRESS, HIGH);
        else
          digitalWrite(SUIVEUR_SPI_ADDRESS, LOW);
      } else {
        digitalWrite(SUIVEUR_SPI_ADDRESS, LOW);
      }

      //Durant les 8 premier bits, on reçoit la valeur lue du capteur, demandée à l'itération précédente
      values[j] <<= 1;
      if (digitalRead(SUIVEUR_SPI_DATAOUT))
        values[j] |= 0x01;
      digitalWrite(SUIVEUR_SPI_CLOCK, HIGH);
      digitalWrite(SUIVEUR_SPI_CLOCK, LOW);
    }
    //Les 4 bits suivants poursuivent la réception de la valeur lue du capteur
    for (i = 0; i < 4; i++) {
      values[j] <<= 1;
      if (digitalRead(SUIVEUR_SPI_DATAOUT))
        values[j] |= 0x01;
      digitalWrite(SUIVEUR_SPI_CLOCK, HIGH);
      digitalWrite(SUIVEUR_SPI_CLOCK, LOW);
    }
    //Les 4 derniers bits ne font que compléter le cycle de communication (total de 16 bits)
    for (i = 0; i < 0; i++) {
      digitalWrite(SUIVEUR_SPI_CLOCK, HIGH);
      digitalWrite(SUIVEUR_SPI_CLOCK, LOW);
    }
    digitalWrite(SUIVEUR_SPI_CS, HIGH);
  }
  //On décale les valeurs reçus de 2 bits et on les sauvegarde dans le tableau capteurs, à la bonne position
  for (i = 0; i < NOMBRE_SENSORS + 1; i++) {
    values[i] = values[i] >> 2;
  }
  // La valeur est convertie pour que noir==min (0) et blanc==max (1023)
  for (i = 0; i < NOMBRE_SENSORS; i++) {
    out_capteurs[i] = values[i + 1];
  }
}

/**
 * Permet d'appliquer une calibration à une suite de valeurs de senseurs.
 * @param sensor_values Les valeurs d'origines
 * @param calibration La calibration à appliquer
 * @param out_rectified_sensor_values L'endroit où vas être écrit les valeures calibrées des senseurs.
*/
void rectify_sensor_values(int sensor_values[NOMBRE_SENSORS], SensorCalibration *calibration, int out_rectified_sensor_values[NOMBRE_SENSORS])
{
    for (int i = 0; i < NOMBRE_SENSORS; i++)
    {
        out_rectified_sensor_values[i] = map(
            sensor_values[i],
            calibration->min[i],
            calibration->max[i],
            RECTIFIED_MIN,
            RECTIFIED_MAX);
    }
}

/**
 * Permet de "tuner" une calibration en lui appliquant des nouvelles valeurs de référence.
 * @param old_calibration la calibration de référence.
 * @param changes la nouvelle série de données. 
 * @return un nouvel objet calibration avec les changements appliqués.
*/
SensorCalibration update_calibration(SensorCalibration *old_calibration, int changes[NOMBRE_SENSORS])
{
    SensorCalibration new_calibration;
    auto old_min = old_calibration->min, old_max = old_calibration->max;

    for (int i = 0; i < NOMBRE_SENSORS; i++)
    {
        new_calibration.min[i] = changes[i] < old_min[i]
                                     ? changes[i]
                                     : old_min[i];
        new_calibration.max[i] = changes[i] > old_max[i]
                                     ? changes[i]
                                     : old_max[i];
    }
    return new_calibration;
}
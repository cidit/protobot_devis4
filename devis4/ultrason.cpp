#include "ultrason.hpp"
#include <Arduino.h>

const auto ECHO_PIN = 2, TRIGGER_PIN = 3;

/**
 * Initialization des pins nécessaires au bon fonctionnement du capteur ultrasonique.
*/
void initUltrason()
{
    pinMode(ECHO_PIN, INPUT);
    pinMode(TRIGGER_PIN, OUTPUT);
}

/**
 * Code emprunté de l'exemple `Ultrasonic-Ranging`.
 * Je suis pas super sur de comprendre ce code, mais je sais au moins l'utiliser.
 * @return La distance du premier obstacle en face du robot, ou -1 si pas d'obstacle a été détecté dans la distance d'utilisation du capteur.
*/
float getDistance()
{
    // Les 5 lignes suivantes créent une impulsion d'ultrasons émise par le capteur.
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);
    // Lecture du temps que les ultrasons ont pris pour revenir.
    // Le chiffre 58 me semble un peu arbitraire mais cette opération transforme un nombre de microsecondes en un nombre de centimètres. Par quelle magie ça marche, je ne sais pas, mais ça marche!
    float cm_dist = pulseIn(ECHO_PIN, HIGH) / 58; 
    
    // On détermine si la mesure qui a été prise entre dans l'écart de bonne utilisation du capteur à ultrasons.
    if (cm_dist > 2 && cm_dist < 400) {
        return cm_dist*10; // Multiplié par 10 pour convertir en millimetres.
    } else {
        return -1;
    }
}

/**
 * Imprime la distance sur le moniteur série.
*/
void raporterDistance(float distance)
{
    Serial.println("Distance: " + String(distance) + "cm");
}
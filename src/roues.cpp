#include <Arduino.h>
#include "roues.hpp"

// la signature de la struct `motor_pin_set` se trouve dans `roues.hpp`
const motor_pin_set RIGHT_MOTOR{5, A2, A3}, LEFT_MOTOR{6, A0, A1};

/**
 * Initialise les pins nécéssaires à la manipulation d'un moteur.
 */
void setMotorPinModes(motor_pin_set pins)
{
    pinMode(pins.speed, OUTPUT);
    pinMode(pins.forward, OUTPUT);
    pinMode(pins.backward, OUTPUT);
}

/**
 * Permet de modifier la vitesse ainsi que la direction d'un moteur.
 * @param motor_pins Ensembles de pins nécéssaires à la manipulation d'un moteur.
 * @param speed Nouvelle vitesse du moteur. 
 *  Elle est attendue d'être dans l'intervale [-1, 1]. 
 *  Si la vitesse est négative, le moteur tourne à l'envers.
 */
void setMotorSpeed(motor_pin_set motor_pins, float speed)
{
    auto magnitude = abs(speed);
    auto pwm = magnitude * 255;
    if (speed > 0)
    {
        digitalWrite(motor_pins.forward, HIGH);
        digitalWrite(motor_pins.backward, LOW);
        analogWrite(motor_pins.speed, pwm);
    }
    else if (speed < 0)
    {
        digitalWrite(motor_pins.forward, LOW);
        digitalWrite(motor_pins.backward, HIGH);
        analogWrite(motor_pins.speed, pwm);
    }
    else // La variable `speed` est donc à 0.
    {
        digitalWrite(motor_pins.forward, LOW);
        digitalWrite(motor_pins.backward, LOW);
        analogWrite(motor_pins.speed, 0);
    }
}

/**
 * Initialise tous les moteurs pour controler les roues du robot.
*/
void initRoues()
{
    setMotorPinModes(RIGHT_MOTOR);
    setMotorPinModes(LEFT_MOTOR);
}

/**
 * Permet de modifier la vitesse des deux moteurs.
 * Les paramètres sont des vitesses contenues entre [-100, 100].
 * Les vitesses négatives indiquent que le moteur tourne à l'envers.
 * @param vitesseG La nouvelle vitesse de la roue gauche.
 * @param vitesseD La nouvelle vitesse de la roue droite.
*/
void tourner(float vitesseG, float vitesseD)
{
    auto speedR = vitesseD / 100;
    auto speedL = vitesseG / 100;
    setMotorSpeed(RIGHT_MOTOR, -speedR);
    setMotorSpeed(LEFT_MOTOR, speedL);
}
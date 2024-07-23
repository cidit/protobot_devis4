#include "i2c.hpp"
#include <Arduino.h>
#include <Wire.h>

/*
 * Code emprunté de l'exemple `Joystick`.
 * Je suis pas super sur de comprendre ce code, mais je sais au moins l'utiliser.
 */

const auto I2C_ADDR = 0x20;

/**
 * Initialise le bus I2C.
 */
void initI2C()
{
    Wire.begin();
}

/**
 * Fais une transmission sur le port I2C.
 * @param data L'information à transmettre sur le bus I2C.
 */
void ecrire(int data)
{
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(data);
    Wire.endTransmission();
}

/**
 * Lis le port I2C.
 * @param out Paramètre de sortie dans lequel l'information obtenue vas être écrite, si l'opération de lecture n'échoue pas.
 * @return `true` si l'opération de lecture a réuissit, `false` si non.
 */
bool lire(int &out)
{
    Wire.requestFrom(I2C_ADDR, 1);
    if (!Wire.available())
    {
        return false;
    }
    out = Wire.read();
    return true;
}
#include "buzzer.hpp"
#include "i2c.hpp"
#include <Arduino.h>
#include "constants.hpp"

/*
 * Code emprunté de l'exemple `Joystick`.
 * Je suis pas super sur de comprendre ce code, mais je sais au moins l'utiliser.
 */

/**
 * Alumme le buzzer.
 */
void alumerBuzzer()
{
    int value;
    bool success = lire(value);
    if (!success)
    {
        return;
    }
    ecrire(0xDF & value);
}

/**
 * Éteint le buzzer.
 */
void eteindreBuzzer()
{
    int value;
    bool success = lire(value);
    if (!success)
    {
        return;
    }
    ecrire(0x20 | value);
}

/**
 * Émet un très court buzz, juste assez long pour être clairement remarquable mais pas asser pour être carrément chiant et insuportable.
 */
void petitBuzz()
{
    alumerBuzzer();
    delay(ONE_SECOND * 0.01);
    eteindreBuzzer();
}

/**
 * Émet un buzz de la longueur définie.
 * @param time Le temps du buzz.
*/
void buzzDelay(long time) {
    alumerBuzzer();
    delay(time);
    eteindreBuzzer();
    delay(time);
}
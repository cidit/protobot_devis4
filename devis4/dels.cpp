#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "dels.hpp"

/*
 * Code inspiré de l'exemple `W2812`.
 */

const auto PIN_DELS = 7;
const auto NOMBRE_DE_DELS = 4;

Adafruit_NeoPixel RGB = Adafruit_NeoPixel(NOMBRE_DE_DELS, PIN_DELS, NEO_GRB + NEO_KHZ800);

/**
 * Initialise les dels et le met à blanc par défaut.
 */
void initDels()
{
    RGB.begin();
}

/**
 * Change la couleur des dels.
 * TODO: params and other things.
 */
void changerCouleur(uint32_t color)
{
    for (auto i = 0; i < NOMBRE_DE_DELS; i++)
    {
        RGB.setPixelColor(i, color);
    }
    RGB.show();
}

/**
 * Change la couleur des dels.
 * @param rouge La quantitée de rouge dans la couleur. [0-255]
 * @param vert La quantitée de vert dans la couleur. [0-255]
 * @param bleu La quantitée de bleu dans la couleur. [0-255]
 */
void changerCouleur(uint8_t rouge, uint8_t vert, uint8_t bleu)
{
    auto color = make_color(rouge, vert, bleu);
    changerCouleur(color);
}

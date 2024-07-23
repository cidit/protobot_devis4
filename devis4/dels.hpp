#pragma once
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define make_color(r, g, b) Adafruit_NeoPixel::Color(r, g, b)

void initDels();
void changerCouleur(uint8_t rouge, uint8_t vert, uint8_t bleu);
void changerCouleur(uint32_t color);
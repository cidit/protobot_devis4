#pragma once
#include <Arduino.h>

void initI2C();
void ecrire(int data);
bool lire(int &out);
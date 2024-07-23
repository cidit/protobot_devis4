#pragma once

struct motor_pin_set
{
    int speed, forward, backward;
};

void initRoues();
void tourner(float vitesseG, float vitesseD);

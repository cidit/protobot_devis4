#pragma once
#include "telecommande.hpp"
#include <Arduino.h>
#include "dels.hpp"
#include <Touches.h>
#include "suiveurs.hpp"

/**
 * Class virtuelle servant de patron aux différentes stratégies des modes implémentés.
 * Cette classe implémente à la fois le "design pattern" de stratégie, et permet de cycler entre les
 * différentes autres stratégies en appellant les fonctions get_prev et get_next.
*/
class ModeStrategy
{
    ModeStrategy *_prev, *_next;

public:
    virtual ~ModeStrategy() = default;
    virtual uint32_t get_associated_color() = 0;
    virtual String get_name() = 0;
    virtual void reset() = 0;
    virtual void loop() = 0;
    void runTransition();

    // circular linked list properties
    static void chainStrategies(ModeStrategy *strategies[], size_t length);
    ModeStrategy *get_prev() { return _prev; }
    ModeStrategy *get_next() { return _next; }
};

/**
 * Mode télécommandé, comme définit dans le devis.
 */
class RemoteControlled : public ModeStrategy
{
    REMOTE_BUTTON_CODES _last_command;
    float _speed;
    void apply_wheel_change(REMOTE_BUTTON_CODES command);

public:
    uint32_t get_associated_color() override;
    String get_name() override;
    void reset() override;
    void loop() override;
};

/**
 * Mode télécommandé, mais avec les contrôles améliorés de Mathieu Cartier.
 */
class RemoteControlledButBetter : public ModeStrategy
{
    float _speed;

public:
    uint32_t get_associated_color() override;
    String get_name() override;
    void reset() override;
    void loop() override;
};

/**
 * Mode explorateur.
 */
class Explorer : public ModeStrategy
{
    Touches *_touches;

public:
    Explorer(Touches *touches);
    uint32_t get_associated_color() override;
    String get_name() override;
    void reset() override;
    void loop() override;
};

/**
 * Mode Disco-party.
 */
class Disco : public ModeStrategy
{
    long _start_of_dance;
public:
    uint32_t get_associated_color() override;
    String get_name() override;
    void reset() override;
    void loop() override;
};

/**
 * Mode Suiveur de ligne.
 */
class LineFollower : public ModeStrategy
{
    SensorCalibration *_calibration;
    Touches *_touches;

public:
    LineFollower(SensorCalibration *calibration, Touches *touches);
    uint32_t get_associated_color() override;
    String get_name() override;
    void reset() override;
    void loop() override;
};

/**
 * Mode bonus, où le buzzer est utilisé à différents écarts pour simuler différentes notes.
 */
class Instrument : public ModeStrategy
{
public:
    uint32_t get_associated_color() override;
    String get_name() override;
    void reset() override;
    void loop() override;
};

/**
 * Mode "bonus" qui permet de changer les seuils minimums des senseurs infrarouges, ainsi que de calibrer la vitesse minimum fonctionnelle des roues.
 */
class Calibration : public ModeStrategy
{
    SensorCalibration *_calibration;

public:
    Calibration(SensorCalibration *calibration);
    uint32_t get_associated_color() override;
    String get_name() override;
    void reset() override;
    void loop() override;
};

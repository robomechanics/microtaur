#pragma once
#include "motor.h"
#include "Arduino.h"
#include "ChRt.h"
#include "imu.h"
#include "led.h"
#include "machine.h"

class Microtaur : Singleton<Microtaur>
{
    void init_motors();
    void init_imu();
    void init_machine();
    void init_led();
    Microtaur(){}

public:
    void init();
};
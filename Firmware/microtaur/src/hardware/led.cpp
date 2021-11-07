#include "led.h"
#include "motor.h"
#include "ChRt.h"


LED::LED() : on_ms_(200), off_ms_(200), mutex_(_MUTEX_DATA(mutex_))
{
    pinMode(LED_PIN, OUTPUT);
}

void LED::on()
{
    digitalWrite(LED_PIN, HIGH);
}
void LED::off()
{
    digitalWrite(LED_PIN, LOW);
}

void LED::set(unsigned int on, unsigned int off)
{
    chMtxLock(&mutex_);
    on_ms_ = on;
    off_ms_ = off;
    chMtxUnlock(&mutex_);
}

// void LED::init(tprio_t priority){
//     Thread<LED>::init(priority, work_area_, sizeof(work_area_));
// }

void LED::run()
{
    while (true)
    {
        auto prev = chVTGetSystemTime();
        on();
        chMtxLock(&mutex_);
        int on_time = on_ms_;
        int off_time = off_ms_;
        chMtxUnlock(&mutex_);
        prev = chThdSleepUntilWindowed(prev, chTimeAddX(prev, TIME_MS2I(on_time)));
        off();
        prev = chThdSleepUntilWindowed(prev, chTimeAddX(prev, TIME_MS2I(off_time)));
        Serial.print("Motor1: ");
        Serial.println(chTimeI2US(Motor<1>::instance().time_));
        Serial.print("Motor2: ");
        Serial.println(chTimeI2US(Motor<2>::instance().time_));
        Serial.print("Motor3: ");
        Serial.println(chTimeI2US(Motor<3>::instance().time_));
        Serial.flush();
    }
}
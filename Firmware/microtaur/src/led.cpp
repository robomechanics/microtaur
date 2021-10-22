#include "led.h"

LED::LED(): on_ms_(200.0), off_ms_(200.0), mutex_(_MUTEX_DATA(mutex_)) {
    pinMode(LED_PIN, OUTPUT);
}

void LED::on(){
    digitalWrite(LED_PIN, HIGH);
}
void LED::off(){
    digitalWrite(LED_PIN, LOW);
}

void LED::set(double on, double off){
    chMtxLock(&mutex_);
    on_ms_ = on;
    off_ms_ = off;
    chMtxUnlock(&mutex_);
}

void LED::run(){
    on();
    chMtxLock(&mutex_);
    double on_time = on_ms_;
    double off_time = off_ms_;
    chMtxUnlock(&mutex_);
    chThdSleepMilliseconds(on_time);
    off();
    chThdSleepMilliseconds(off_time);
}
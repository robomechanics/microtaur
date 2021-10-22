#pragma once

#include "singleton.h"
#include "ChRt.h"

#define LED_PIN 13

class LED : public Singleton<LED>{
    friend class Singleton<LED>;
    
    public:
        void on();
        void off();
        void run();
        void set(double on, double off);

    private:
        double  on_ms_;
        double  off_ms_;
        mutex_t mutex_;
        LED();
};
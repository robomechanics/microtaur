#pragma once

#include "singleton.h"
#include "ChRt.h"

#define LED_PIN 13

class LED : public Singleton<LED>{
    friend class Singleton<LED>;
    
    public:
        double  off_ms_;
        double  on_ms_;
        void on();
        void off();
        void run();
        void set(double on, double off);

    private:
        LED();
        mutex_t mutex_;
};
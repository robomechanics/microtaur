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
        void set(unsigned int on, unsigned int off);

    private:
        unsigned int  on_ms_;
        unsigned int  off_ms_;
        mutex_t mutex_;
        LED();
};
#pragma once

#include "singleton.h"
#include "ChRt.h"
#include "thread.h"

#define LED_PIN 13

class LED : public Singleton<LED>, public Thread<LED, DEFAULT_STACK>
{
    friend class Singleton<LED>;
    unsigned int on_ms_;
    unsigned int off_ms_;
    mutex_t mutex_;
    LED();

public:
    void on();
    void off();
    void run();
    void set(unsigned int on, unsigned int off);
};
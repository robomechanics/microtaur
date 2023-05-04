#pragma once
#include "Arduino.h"
#include "singleton.h"
#include "BNO055_support.h"
#include "Wire.h"
#include "ChRt.h"
#include "thread.h"

struct IMUState
{
    double roll, pitch, yaw;
};

class IMU : public Singleton<IMU>, public Thread<IMU, DEFAULT_STACK>
{
    friend class Singleton<IMU>;

    virtual_timer_t timer_;
    IMU();
    static void timer_callback(void *arg);
    mutex_t mutex_;
    IMUState state_;
    struct bno055_t device_;

public:
    IMUState state();
    void run();
    void init(tprio_t priority);
};
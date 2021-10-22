#pragma once
#include "Arduino.h"
#include "singleton.h"
#include "BNO055_support.h"
#include "Wire.h"
#include "ChRt.h"

struct IMUState{
    double roll, pitch, yaw;
};

class IMU : public Singleton<IMU> {
    friend class Singleton<IMU>;
    
    public:
        IMUState state();
        void run();

    private:
        IMU();
        mutex_t mutex_;
        IMUState state_;
        struct bno055_t device_;
};
#include "imu.h"

#define IMU_RADIANS(x) x / 900.0
#define IMU_QUAT(x) double(x) / (1 << 14)


IMU::IMU() : mutex_(_MUTEX_DATA(mutex_))
{
    Wire.begin();
    BNO_Init(&device_);

    bno055_set_operation_mode(OPERATION_MODE_NDOF);
    delay(1);
}

void IMU::init(tprio_t priority)
{
    Thread<IMU, DEFAULT_STACK>::init(priority);
    chVTSet(&timer_,
            TIME_MS2I(100),
            &IMU::timer_callback,
            this);
}
void IMU::timer_callback(void *arg)
{
    IMU &obj = *reinterpret_cast<IMU *>(arg);
    obj.signal(EVENT_MASK(0));
    chVTSet(&obj.timer_,
            TIME_MS2I(100),
            &IMU::timer_callback,
            arg);
}
void IMU::run()
{
    thread_ = chThdGetSelfX();
    while (true)
    {
        chEvtWaitAny(ALL_EVENTS);
        struct bno055_euler data;
        bno055_read_euler_hrp(&data);
        chMtxLock(&mutex_);
        state_.roll = IMU_RADIANS(data.r);
        state_.pitch = IMU_RADIANS(data.p);
        state_.yaw = IMU_RADIANS(data.h);
        chMtxUnlock(&mutex_);
    }
}

IMUState IMU::state()
{
    IMUState data;
    chMtxLock(&mutex_);
    data = state_;
    chMtxUnlock(&mutex_);
    return data;
}
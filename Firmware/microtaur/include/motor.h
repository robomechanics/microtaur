#pragma once

#include <iq_module_communication.hpp>
#include <iq/iq_serial_multithread.hpp>

typedef enum
{
    no_change = -1,
    brake,
    coast,
    pwm,
    volts,
    velocity,
    angle,
    trajectory
} ctrl_mode_t;

class Motor
{
private:
    IqSerialMultithreaded ser_;
    MultiTurnAngleControlClient client_;

public:
    Motor(HardwareSerial serial) : ser_(serial), client_(0) {}

    void setCoast()
    {
        ser_.set(client_.ctrl_coast_);
    }
    void sendTrajectorySpeed(double speed_cmd, double angle_cmd)
    {
        ser_.set(client_.trajectory_angular_displacement_, angle_cmd);
        ser_.set(client_.trajectory_average_speed_, speed_cmd);
    }

    void sendTrajectoryTime(double time_cmd, double angle_cmd)
    {
        ser_.set(client_.trajectory_angular_displacement_, angle_cmd);
        ser_.set(client_.trajectory_duration_, time_cmd);
    }

    ctrl_mode_t getMode()
    {
        ctrl_mode_t mode = 0;
        ser_.get(client_.ctrl_mode_, mode);
        return mode;
    }
}
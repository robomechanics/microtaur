#pragma once

#include "singleton.h"
#include "thread.h"
#include "Arduino.h"
#include "iq_module_communication.hpp"
#include "iq/iq_serial_multithread.hpp"
#include <memory>

template <unsigned int N>
class Motor : public Singleton<Motor<N>>, public Thread<Motor<N>, 200>
{
    friend class Singleton<Motor<N>>;
    std::unique_ptr<IqSerialMultithreaded> ser_;
    MultiTurnAngleControlClient client_;
    float pos_;
    float cmd_pos_;
    float vel_;
    float Kp_;
    float Kd_;
    virtual_timer_t timer_;

    static void timer_callback(void * arg)
    {
        Motor<N> &obj = *reinterpret_cast<Motor<N> *>(arg);
        obj.signal(EVENT_MASK(0));
        chVTSet(&obj.timer_,
                TIME_MS2I(5),
                &Motor<N>::timer_callback,
                arg);
    }
    Motor() : client_(0), cmd_pos_(0){}
    systime_t prev_;

public:
    sysinterval_t time_;
    void run()
    {
        this->set_thread(chThdGetSelfX());
        while (true)
        {
            auto mask = chEvtWaitAny(ALL_EVENTS);
            if (mask & EVENT_MASK(Signals::Update_PosVel))
            {
                auto start = chVTGetSystemTime();
                time_ = chTimeDiffX(prev_, start);
                prev_ = start;
                ser_->set(client_.ctrl_angle_, cmd_pos_);
                ser_->get(client_.obs_angular_displacement_, pos_);
                ser_->get(client_.obs_angular_velocity_, vel_);
            }
            // if (mask & EVENT_MASK(Signals::Update_Gains))
            // {
            //     ser_->set(client_.angle_Kp_, Kp_);
            //     ser_->set(client_.angle_Kd_, Kd_);
            // }
        }
    }
    enum class Signals
    {
        Update_PosVel = 0,
        Update_Gains
    };
    void init(tprio_t priority)
    {
        Thread<Motor<N>, DEFAULT_STACK>::init(priority);
        chVTSet(&timer_,
                TIME_MS2I(100),
                &Motor<N>::timer_callback,
                this);
    }
    void attach_serial_port(HardwareSerial &serial)
    {
        ser_ = std::make_unique<IqSerialMultithreaded>(serial);
        ser_->begin();
    }
    void set_position(double position) { cmd_pos_ = position; }
    float get_position() { return pos_; }
    void set_gains(double Kp, double Kd)
    {
        Kp_ = Kp;
        Kd_ = Kd;
        signal(this->thread(), EVENT_MASK(1));
    }
};
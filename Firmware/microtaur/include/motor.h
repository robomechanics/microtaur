#pragma once

#include "singleton.h"
#include "thread.h"
#include "Arduino.h"
#include "iq_module_communication.hpp"
#include "iq/iq_serial_multithread.hpp"
#include "client_communication.hpp"
#include <memory>

template <unsigned int N>
class Motor : public Singleton<Motor<N>>, public Thread<Motor<N>, 200>
{
    friend class Singleton<Motor<N>>;
    std::unique_ptr<IqSerialMultithreaded> ser_;
    MultiTurnAngleControlClient client_;
    float pos_;
    float cmd_pos_;
    float acc_;
    float amps;
    float vel_;
    float Kp_;
    float Kd_;
    float Ki_;
    float voltage_ = 0.0f;
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

    // float get_amps() {
    //     pwr.amps_.get(com);
    //     return 0;
    // }
    

    float get_K_p() {
        float Kp;
        ser_->get(client_.angle_Kp_, Kp);
        // Kp = client_.angle_Kp_.get();
        
        return Kp;
    } 
    float get_K_d() {
        float Kd;
        ser_->get(client_.angle_Kd_, Kd);
        // Kd = client_.angle_Kd_.get();
        return Kd;
    } 

    void set_ang_vel(float w) {
        ser_->set(client_.angular_speed_max_, w);
    }
    
    float get_location() {
        float loc;
        ser_->get(client_.obs_angular_displacement_, loc);
        return loc;
    }

    void move_by_traj(float disp, float time) {
        float loc_zero;
        loc_zero = get_location();

        ser_->set(client_.trajectory_angular_displacement_, disp);
        ser_->set(client_.trajectory_duration_, time);
        delay(1000);
    }

    void set_gains(float Kp, float Ki, float Kd)
    {
        Kp_ = Kp;
        Ki_ = Ki;
        Kd_ = Kd;

        ser_->set(client_.angle_Kp_, Kp_);
        ser_->set(client_.angle_Ki_, Ki_);
        ser_->set(client_.angle_Kd_, Kd_);
    }

    void set_coast_mode() {
        ser_->set(client_.ctrl_coast_);
    }

    void set_up_traj(float zero_pos) {
        ser_->set(client_.obs_angular_displacement_, zero_pos); // sets current location to zero
        ser_->set(client_.trajectory_queue_mode_, (int8_t)0); // sets traj to overwrite mode
    }

    void set_overwrite_mode() {
        ser_->set(client_.trajectory_queue_mode_, (int8_t)1); // sets traj to overwrite mode
    }

    void set_queue_mode() {
        ser_->set(client_.trajectory_queue_mode_, (int8_t)0); // sets traj to overwrite mode
    }

    void setPosToZero() {
        ser_->set(client_.obs_angular_displacement_, 0.0f);
    }

    void move_traj_by_time(float disp, float time) {
        ser_->set(client_.trajectory_angular_displacement_, disp);
        ser_->set(client_.trajectory_duration_, time);
        // Serial.println("function activated");
    }

    void move_traj_by_speed(float disp, float speed) {
        ser_->set(client_.trajectory_angular_displacement_, disp);
        ser_->set(client_.trajectory_average_speed_, speed);
    }

    void update_volts() {
        ser_->get(client_.ctrl_volts_, voltage_);
    }

    float get_volts() {
        // ser_->get(client_.ctrl_volts_, voltage_);
        return voltage_;
    }

    void update_acc() {
        ser_->get(client_.trajectory_angular_acceleration_, acc_);
    }

    float get_acc() {
        return acc_;
    }

    void update_positions() {
        ser_->get(client_.obs_angular_displacement_, pos_);
    }

    void serial_print_volts(void) {
        Serial.print(voltage_);
    }

    void serial_print_position(void) {
        Serial.print(pos_);
    }

    void check_prev() {
      int8_t mode = 0;
      // At this point the motor should be executing a trajectory.
      // Wait for the trajectory to finish
      do
      {
        // Gets ctrl_mode_ from the module and puts the result in the mode variable
        ser_->get(client_.ctrl_mode_, mode);
      } while(mode == 6); // Check if the motor is still executing the last trajectory
    }

};
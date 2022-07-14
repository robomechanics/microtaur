#pragma once
#include "motor.h"
#include "Arduino.h"
#include "ChRt.h"
#include "imu.h"
#include "led.h"
#include "machine.h"


class Microtaur : public Singleton<Microtaur>
{
    void init_motors();
    void init_imu();
    void init_machine();
    void init_led();
    // Microtaur(){}

public:

    uint32_t buttons_ = 0;
    // Joystick key-encodings
    uint32_t X = 1;
    uint32_t A = 2;
    uint32_t B = 4;
    uint32_t Y = 8;
    uint32_t start = 512;
    uint32_t back = 256;
    uint32_t right_knoch_click_down = 2048;
    uint32_t left_knoch_click_down = 1024;
    uint32_t LT = 64;
    uint32_t LB = 16;
    uint32_t RT = 128;
    uint32_t RB = 32;

    float cmd_pos_M1_;
    float cmd_pos_M2_;
    float cmd_pos_M3_;
    float cmd_pos_M4_;
    float cmd_pos_M5_;
    float cmd_pos_M6_;
    float cmd_pos_M7_;
    float cmd_pos_M8_;

    float Kp_ = 60.0f;
    float Ki_ = 0.0f;
    float Kd_ = 0.3;
    
    float motor_pos[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // could use this later for simplicity

    void init();

    uint32_t get_buttons(uint32_t buttons) {
        buttons_ = buttons;
        return buttons;
    }

    void setup() {
        Motor<1>::instance().attach_serial_port(Serial1);
        Motor<2>::instance().attach_serial_port(Serial2);
        Motor<3>::instance().attach_serial_port(Serial3);
        Motor<4>::instance().attach_serial_port(Serial4);
        Motor<5>::instance().attach_serial_port(Serial5);
        Motor<6>::instance().attach_serial_port(Serial6);
        Motor<7>::instance().attach_serial_port(Serial7);
        Motor<8>::instance().attach_serial_port(Serial8);

        Motor<1>::instance().set_gains(Kp_, Ki_, Kd_);
        Motor<2>::instance().set_gains(Kp_, Ki_, Kd_);
        Motor<1>::instance().set_up_traj(0.0f);
        Motor<2>::instance().set_up_traj(0.0f);

        Motor<4>::instance().set_gains(Kp_, Ki_, Kd_);
        Motor<5>::instance().set_gains(Kp_, Ki_, Kd_);
        Motor<4>::instance().set_up_traj(0.0f);
        Motor<5>::instance().set_up_traj(0.0f);

        Motor<6>::instance().set_gains(Kp_, Ki_, Kd_);
        Motor<7>::instance().set_gains(Kp_, Ki_, Kd_);
        Motor<6>::instance().set_up_traj(0.0f);
        Motor<7>::instance().set_up_traj(0.0f);

        Motor<8>::instance().set_gains(Kp_, Ki_, Kd_);
        Motor<3>::instance().set_gains(Kp_, Ki_, Kd_);
        Motor<3>::instance().set_up_traj(0.0f);
        Motor<8>::instance().set_up_traj(0.0f);
    }


    void stand() {
        if (buttons_ == start) {
            Serial.println("Start was pressed, begin standing");
            // voltage_readings();
            uint32_t start_time = millis();
            Motor<1>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<2>::instance().move_traj_by_time(2.50f, 1.0f);
            Motor<4>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<5>::instance().move_traj_by_time(2.50f, 1.0f);
            Motor<6>::instance().move_traj_by_time(2.50f, 1.0f);
            Motor<7>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<8>::instance().move_traj_by_time(2.50f, 1.0f);
            Motor<3>::instance().move_traj_by_time(0.0f, 1.0f);
            // duration = 1.0f seconds == 1000 ms

            get_voltage(start_time, 1000);
            
            // update positions
            cmd_pos_M1_ = 0.0f;
            cmd_pos_M2_ = 2.50f;
            cmd_pos_M3_ = 0.0f;
            cmd_pos_M4_ = 0.0f;
            cmd_pos_M5_ = 2.50f;
            cmd_pos_M6_ = 2.50f;
            cmd_pos_M7_ = 0.0f;
            cmd_pos_M8_ = 2.50f;
            delay(1000);
            Serial.println("Done standing");
        }
    }

    void sit() {
        if (buttons_ == back) {
            Serial.println("Back was pressed, begin sitting");
            // starting from a stance position
            uint32_t start_time = millis();
            Motor<1>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<2>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<4>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<5>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<6>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<7>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<8>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<3>::instance().move_traj_by_time(0.0f, 1.0f);
            get_voltage(start_time, 1000);
            delay(1000);
            Serial.println("Done sitting");
        }
    }

    void walk() {
        if (buttons_ == X) {
            float phase_time_ = 0.04;
            uint32_t delay_ = 40;
            //                   FAST Walking-Trot
            Serial.println("Beginning fast walking trot");
            uint32_t start_time = millis();
            // raise TR&BL legs up
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.5f, phase_time_);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.5f, phase_time_);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.5f, phase_time_);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.5f, phase_time_);
            get_voltage(start_time, delay_);
            start_time = millis(); // reset start_time for next trajectory

            //step TR&BL forward (on ground)
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.44f, phase_time_);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.02f, phase_time_);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.44f, phase_time_);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.02f, phase_time_);
            get_voltage(start_time, delay_);
            start_time = millis();

            
            // back to stance
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, phase_time_);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, phase_time_);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.0f, phase_time_);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.0f, phase_time_);
            get_voltage(start_time, delay_);
            start_time = millis();

            // send back
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.02f, phase_time_);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.44f, phase_time_);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.02f, phase_time_);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.44f, phase_time_);
            get_voltage(start_time, delay_);
            start_time = millis();

            // Raise TL&BR legs up  
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.5f, phase_time_);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.5f, phase_time_);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.5f, phase_time_);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.5f, phase_time_);
            get_voltage(start_time, delay_);
            start_time = millis();

            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.44f, phase_time_);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.02f, phase_time_);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.44f, phase_time_);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.02f, phase_time_);
            get_voltage(start_time, delay_);
            start_time = millis();

            // step back to standing stance
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, phase_time_);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, phase_time_);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, phase_time_);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, phase_time_);
            get_voltage(start_time, delay_);
            start_time = millis();

            // send back
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.02f, phase_time_);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.44f, phase_time_);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.02f, phase_time_);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.44f, phase_time_);
            get_voltage(start_time, delay_);

            Serial.println("ending fast walking trot");

        } else if (buttons_ == LB) {
            //                      SLOW Walking-Trot (Backwards)
            Serial.println("Beginning walking trot");
            uint32_t start_time = millis();
            // raise TR&BL legs up
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.5f, 0.1f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.5f, 0.1f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.5f, 0.1f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.5f, 0.1f);
            get_voltage(start_time, 100);
            start_time = millis();
            // step TR&BL forward 
            Serial.println("step TR&BL forward");
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.42f, 0.1f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.3f, 0.1f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.42f, 0.1f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.3f, 0.1f);
            get_voltage(start_time, 100);
            start_time = millis();

            // back to stance
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, 0.3f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, 0.3f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.0f, 0.3f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.0f, 0.3f);
            // get_voltage(start_time, 300);
            delay(125);
            start_time = millis();
            // delay(500);

            // Raise TL&BR legs up  
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.5f, 0.1f);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.5f, 0.1f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.5f, 0.1f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.5f, 0.1f);
            get_voltage(start_time, 100);
            start_time = millis();

            // step TL&BR forward
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.42f, 0.1f);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.3f, 0.1f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.42f, 0.1);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.3f, 0.1f);
            get_voltage(start_time, 100);
            start_time = millis();

            // step back to standing stance
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, 0.3f);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, 0.3f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, 0.3f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, 0.3f);
            // get_voltage(start_time, 300);
            delay(125);
            start_time = millis();
            // delay(500);
            Serial.println("ending walking trot");
        }
    }

    void bound() {
        if (buttons_ == LT) {
            //                      Bound Gait
            // 1.
            // jump upwards with front legs
            // send rear legs backward

            // 2.
            // send front legs forwards
            // jump up with rear legs when front hits ground

            // 3.
            // send front legs backward
            // send rear legs forward

            // raise front slightly
            // uint32_t start_time = millis();
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.5f, 0.04f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.5f, 0.04f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.5f, 0.04f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.5f, 0.04f);
            // get_voltage(start_time, 40);
            // start_time = millis();
            // step forward front
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.42f, 0.04f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.3f, 0.04f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.42f, 0.04f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.3f, 0.04f);
            // get_voltage(start_time, 40);
            // start_time = millis();
            // step to stance front
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, 0.04f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, 0.04f);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, 0.04f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, 0.04f);
            // get_voltage(start_time, 40);
            // start_time = millis();
            delay(120);

            // raise back slightly
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.5f, 0.04f);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.5f, 0.04f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.5f, 0.04f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.5f, 0.04f);
            // get_voltage(start_time, 40);
            // start_time = millis();

            // step forward back
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.42f, 0.04f);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.3f, 0.04f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.42f, 0.04f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.3f, 0.04f);
            // get_voltage(start_time, 40);+
            // start_time = millis();

            // step to stance back
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, 0.04f);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, 0.04f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.0f, 0.04f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.0f, 0.04f);
            // get_voltage(start_time, 40);
            // start_time = millis();

            delay(120);
        } 
    }

    void hop() {
        if (buttons_ == RT) {
            //                     Hop
            // crouch down (similar to raising all legs)
            Serial.println("beginning hop");
            uint32_t start_time = millis();
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.9f, 2.0f);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.9f, 2.0f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.9f, 2.0f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.9f, 2.0f);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.9f, 2.0f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.9f, 2.0f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.9f, 2.0f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.9f, 2.0f);
            get_voltage(start_time, 1000);
            start_time = millis();

            // extend all legs quickly
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.8f, 0.05f);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.8f, 0.05f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.8f, 0.05f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.8f, 0.05f);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.8f, 0.05f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.8f, 0.05f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.8f, 0.05f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.8f, 0.05f);
            get_voltage(start_time, 1000);
            start_time = millis();

            // bring in legs
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.4f, 0.1f);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.4f, 0.1f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.4f, 0.1f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.4f, 0.1f);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.4f, 0.1f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.4f, 0.1f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.4f, 0.1f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.4f, 0.1f);
            get_voltage(start_time, 1000);
            start_time = millis();
            delay(1500);

            // back to standing
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, 2.0f);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, 2.0f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, 2.0f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, 2.0f);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, 2.0f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, 2.0f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.0f, 2.0f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.0f, 2.0f);
            get_voltage(start_time, 2000);
            start_time = millis();
            delay(2000);
            Serial.println("ending hop");
        }  
    }

    void extend_legs() {
        if (buttons_ == Y) {
            Serial.println("Y was pressed, lock position as zero and enter mobile stance");
            uint32_t start_time = millis();
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.3f, 1.0f);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.3f, 1.0f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.3f, 1.0f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.3f, 1.0f);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.3f, 1.0f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.3f, 1.0f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.3f, 1.0f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.3f, 1.0f);
            get_voltage(start_time, 1000);
            start_time = millis();
            delay(1000);
            // udpdate positions
            cmd_pos_M1_ = cmd_pos_M1_+0.3f;
            cmd_pos_M2_ = cmd_pos_M2_+0.3f;
            cmd_pos_M3_ = cmd_pos_M3_+0.3f;
            cmd_pos_M4_ = cmd_pos_M4_+0.3f;
            cmd_pos_M5_ = cmd_pos_M5_+0.3f;
            cmd_pos_M6_ = cmd_pos_M6_+0.3f;
            cmd_pos_M7_ = cmd_pos_M7_+0.3f;
            cmd_pos_M8_ = cmd_pos_M8_+0.3f;

            Serial.println("Done extending");
        }

    }

    void compress_legs() {
        if (buttons_ == B) {
            Serial.println("B was pressed, going back to standing stance");
            uint32_t start_time = millis();
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, 1.0f);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, 1.0f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, 1.0f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.0f, 1.0f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.0f, 1.0f);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, 1.0f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, 1.0f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, 1.0f);
            get_voltage(start_time, 1000);
            start_time = millis();

            delay(1000);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.3f, 1.0f);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.3f, 1.0f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.3f, 1.0f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.3f, 1.0f);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.3f, 1.0f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.3f, 1.0f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.3f, 1.0f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.3f, 1.0f);
            get_voltage(start_time, 1000);
            start_time = millis();

            delay(1000);
            // udpdate positions
            cmd_pos_M1_ = cmd_pos_M1_-0.3f;
            cmd_pos_M2_ = cmd_pos_M2_-0.3f;
            cmd_pos_M3_ = cmd_pos_M3_-0.3f;
            cmd_pos_M4_ = cmd_pos_M4_-0.3f;
            cmd_pos_M5_ = cmd_pos_M5_-0.3f;
            cmd_pos_M6_ = cmd_pos_M6_-0.3f;
            cmd_pos_M7_ = cmd_pos_M7_-0.3f;
            cmd_pos_M8_ = cmd_pos_M8_-0.3f;

            Serial.println("Done moving back to normal stance");
        }
    }

    void motions() {
        Microtaur::instance().stand();
        Microtaur::instance().sit();
        Microtaur::instance().walk();
        Microtaur::instance().hop();
        Microtaur::instance().bound();
        Microtaur::instance().compress_legs();
        Microtaur::instance().extend_legs();
        Microtaur::instance().activateCoast();
        Microtaur::instance().recordPos();
    }

    void get_voltage(uint32_t start_time, uint32_t duration) {
        print_headers();

        while (millis() < start_time + duration) {
            voltage_readings(millis()); // printing out real time

        }
        voltage_readings(millis()); // print out final location
    }

    void print_headers() {
        Serial.println("Time, M1, M2, M4, M5, M6, M7, M8, M3");
    }

    void voltage_readings(uint32_t time) {
        Serial.print(time); Serial.print(","); 
        Serial.print(Motor<1>::instance().get_volts()); Serial.print(",");
        Serial.print(Motor<2>::instance().get_volts()); Serial.print(", ");

        Serial.print(Motor<4>::instance().get_volts()); Serial.print(", ");
        Serial.print(Motor<5>::instance().get_volts()); Serial.print(", ");

        Serial.print(Motor<6>::instance().get_volts()); Serial.print(", ");
        Serial.print(Motor<7>::instance().get_volts()); Serial.print(", ");

        Serial.print(Motor<8>::instance().get_volts()); Serial.print(", ");
        Serial.print(Motor<3>::instance().get_volts()); Serial.print(" \n");
    }

/////////////////////// other functions

    void incrementKd() {
        if (buttons_ == A) {
            Kd_ = Kd_ + (float)0.1f;
            Serial.println("-----Kd incremented (+1)------");
            delay(1000);
        }
    }

    void incrementKp() {
        if (buttons_ == B) {
            Kp_ = Kp_ + (float)10.0f;
            Serial.println("-----Kp incremented (+10)------");
            delay(1000);
        }
    }

    void incrementKi() {
        if (buttons_ == Y) {
            Ki_ = Ki_ + (float)10.0f;
            Serial.println("-----Ki incremented (+10)------");
            delay(1000);
            
        } 
    }

    void updateGains() {
        Serial.println("gains updated");
        Motor<2>::instance().set_gains(Kp_, Ki_, Kd_);
    }

    void kill() {
        if (buttons_ == X) {
            Serial.println("motor stopped");
            Motor<2>::instance().set_coast_mode();
        }
    }
    
    void moveMotor() {
    if (buttons_ == start) {
        Serial.println("Moving...");
        Motor<1>::instance().move_traj_by_time(0.0f, 1.0f);
        Motor<2>::instance().move_traj_by_time(2.50f, 1.0f);
        delay(1000);
    }
    }

    void raiselegs() {
    if (buttons_ == RT) {
        // raise TR&BL legs up
        Motor<6>::instance().move_traj_by_time(-0.5f, 1.0f);
        Motor<7>::instance().move_traj_by_time(-0.5f, 1.0f);
        Motor<5>::instance().move_traj_by_time(-0.5f, 1.0f);
        Motor<4>::instance().move_traj_by_time(-0.5f, 1.0f);
        // step TR&BL forward 
        Motor<6>::instance().set_coast_mode();
        Motor<7>::instance().set_coast_mode();
        Motor<5>::instance().set_coast_mode();
        Motor<4>::instance().set_coast_mode();
        delay(2000);
    }
    }

    void getPos() {
    // if (buttons_ == LB) {
    // Motor<1>::instance().set_coast_mode();
    // Motor<2>::instance().set_coast_mode();
    Serial.print("Motor 6:");
    Serial.print(Motor<6>::instance().get_location());
    Serial.print(" Motor 7: ");
    Serial.print(Motor<2>::instance().get_location());
    Serial.print("\n");
        // }
    }

    void activateCoast() {
        if (buttons_ == right_knoch_click_down) {
            Motor<6>::instance().set_coast_mode();
            Motor<7>::instance().set_coast_mode();
        }
    }
    void recordPos() {
        if (buttons_ == left_knoch_click_down) {
            Serial.print("M6: "); Serial.print(Motor<6>::instance().get_location()); 
            Serial.print(" M7: "); Serial.print(Motor<7>::instance().get_location()); 
            Serial.print("\n"); 
        }
    }
};


// Notes on controls
// Motors: Clockwise == Positive dir.
//         Counter == Negative dir.


// Joystick Button Encoding: in terms of bitset
// X -> 0000 0000 0001
// A -> 0000 0000 0010
// B -> 0000 0000 0100
// Y -> 0000 0000 1000
// Start -> 0010 0000 0000
// Back -> 0001 0000 0000
// Right knoch click-down -> 1000 0000 0000
// Left knoch click-down -> 0100 0000 0000
// LT -> 0000 0100 0000
// LB -> 0000 0001 0000
// RT -> 0000 1000 0000
// RB -> 0000 0010 0000

// Joystick Button Encoding: in terms of uint32_t
// X -> 1
// A -> 2
// B -> 4
// Y -> 8
// Start -> 512
// Back -> 256
// Right knoch click-down -> 2048
// Left knoch click-down -> 1024
// LT -> 64
// LB -> 16
// RT -> 128
// RB -> 32

// D-Pad Controls: Axes[0, 1]
// Horizontal:
//    Base (untouched) -> 128
//    Left Pressed -> 0
//    Right pressed -> 255
//
// Vertical:
//    Base (untouched) -> 127
//    Up Pressed -> 0
//    Down Pressed -> 255

// Joystick: similar to D-Pad ; Axes[2, 5]

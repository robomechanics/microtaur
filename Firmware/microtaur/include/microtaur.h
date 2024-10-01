#pragma once
#include "motor.h"
#include "Arduino.h"
#include "ChRt.h"
#include "imu.h"
#include "led.h"
#include "machine.h"
#include "TimerThree.h"
#include "TeensyThreads.h"

class Microtaur : public Singleton<Microtaur>
{
    void init_motors();
    void init_imu();
    void init_machine();
    void init_led();
    
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

    // PID Controller Tuning
    float Kp_ = 60.0f;
    float Ki_ = 0.0f;
    float Kd_ = 0.0f;

    void init();

    uint32_t get_buttons(uint32_t buttons) {
        buttons_ = buttons;
        return buttons;
    }

    void setup() {
        // Attach serials ports and initialize PID parameters
  
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
            Motor<1>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<2>::instance().move_traj_by_time(2.50f, 1.0f);
            Motor<4>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<5>::instance().move_traj_by_time(2.50f, 1.0f);
            Motor<6>::instance().move_traj_by_time(2.50f, 1.0f);
            Motor<7>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<8>::instance().move_traj_by_time(2.50f, 1.0f);
            Motor<3>::instance().move_traj_by_time(0.0f, 1.0f);

            // update positions relative to sitting pose
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
            Motor<1>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<2>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<4>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<5>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<6>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<7>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<8>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<3>::instance().move_traj_by_time(0.0f, 1.0f);
            delay(1000);

            Serial.println("Done sitting");
        }
    }

    bool is_in_spider_mode_ = false;

    void go_into_spider_mode() {
        if (is_in_spider_mode_ == false && buttons_ == left_knoch_click_down) {
            Serial.println("Microtaur is transitioning to spider mode!");
            // go back to base stance
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_, 2.0f);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_, 2.0f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_, 2.0f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_, 2.0f);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_, 2.0f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_, 2.0f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_, 2.0f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_, 2.0f);
            delay(2000);
            // raise robot
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.9f, 2.0f);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.9f, 2.0f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.9f, 2.0f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.9f, 2.0f);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.9f, 2.0f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.9f, 2.0f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.9f, 2.0f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.9f, 2.0f);
            delay(3000);


            // invert legged direction of front
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+1.4f, 1.0f);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+1.4f, 1.0f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+1.4f, 1.0f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+1.4f, 1.0f);
            delay(1000);

            // lower robot (**Front end is now inverted**)
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+2.2f, 3.0f);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+2.2f, 3.0f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+2.2f, 3.0f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+2.2f, 3.0f);

            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_, 3.0f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_, 3.0f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_, 3.0f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_, 3.0f);
            delay(3000);

            cmd_pos_M1_ = cmd_pos_M1_+2.2f;
            cmd_pos_M2_ = cmd_pos_M2_+2.2f;
            cmd_pos_M4_ = cmd_pos_M4_+2.2f;
            cmd_pos_M5_ = cmd_pos_M5_+2.2f;

            is_in_spider_mode_ = true;
            Serial.println("Microtaur is in Spider Mode Now!");
        }
    }

    void revert_spider_mode() {
        if (is_in_spider_mode_ == true && buttons_ == right_knoch_click_down) {
            Serial.println("Microtaur is transitioning to NORMAL stance");
            // go to base stance
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_, 2.0f);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_, 2.0f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_, 2.0f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_, 2.0f);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_, 2.0f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_, 2.0f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_, 2.0f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_, 2.0f);
            delay(2000);
            // raise robot
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.9f, 2.0f);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.9f, 2.0f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.9f, 2.0f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.9f, 2.0f);

            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.9f, 2.0f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.9f, 2.0f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.9f, 2.0f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.9f, 2.0f);
            delay(2000);

            // invert legged direction of front
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-1.4f, 1.0f);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-1.4f, 1.0f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-1.4f, 1.0f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-1.4f, 1.0f);
            delay(1000);

            // lower robot (**Front end is now inverted *BACK TO NORMAL*)
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-2.2f, 3.0f);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-2.2f, 3.0f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-2.2f, 3.0f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-2.2f, 3.0f);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_, 3.0f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_, 3.0f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_, 3.0f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_, 3.0f);
            delay(3000);

            cmd_pos_M1_ = cmd_pos_M1_-2.2f;
            cmd_pos_M2_ = cmd_pos_M2_-2.2f;
            cmd_pos_M4_ = cmd_pos_M4_-2.2f;
            cmd_pos_M5_ = cmd_pos_M5_-2.2f;

            is_in_spider_mode_ = false;

            Serial.println("Microtaur is now in NORMAL stance");
        }
    }

    void leap() {
        if (buttons_ == RB) {
            float phase_time_ = 0.05f;

            // picks legs up (moves body lower)
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.5f, 1.0f);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.5f, 1.0f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.5f, 1.0f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.5f, 1.0f);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.5f, 1.0f);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.5f, 1.0f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.5f, 1.0f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.5f, 1.0f);
            delay(1000);
            // send all legs back
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.02f, phase_time_);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.44f, phase_time_);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.02f, phase_time_);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.44f, phase_time_);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.02f, phase_time_);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.44f, phase_time_);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.02f, phase_time_);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.44f, phase_time_);
            delay(50);

            // extend all legs back  ## Add 0.5f to stepped back position to extend
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.02f+0.7f, phase_time_/2);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.44f+0.7f, phase_time_/2);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.02f+0.7f, phase_time_/2);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.44f+0.7f, phase_time_/2);
            delay(60);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.02f+0.7f, phase_time_/2);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.44f+0.7f, phase_time_/2);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.02f+0.7f, phase_time_/2);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.44f+0.7f, phase_time_/2);


            // bring legs back in
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.5f, phase_time_);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.5f, phase_time_);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.5f, phase_time_);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.5f, phase_time_);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.5f, phase_time_);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.5f, phase_time_);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.5f, phase_time_);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.5f, phase_time_);
            delay(500);

            // Back to Normal Stance
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_, 1.0f);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_, 1.0f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_, 1.0f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_, 1.0f);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_, 1.0f);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_, 1.0f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_, 1.0f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_, 1.0f);
        }

    }

    void trot() {
        if (buttons_ == X) {
            float phase_time_ = 0.1;
            uint32_t delay_ = 100;
            Serial.println("Beginning trot");
            // raise TR&BL legs up
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.5f, phase_time_);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.5f, phase_time_);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.5f, phase_time_);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.5f, phase_time_);
            delay(delay_);

            //step TR&BL forward (on ground)
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.44f, phase_time_);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.02f, phase_time_);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.44f, phase_time_);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.02f, phase_time_);
            delay(delay_);

            // back to stance
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, phase_time_);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, phase_time_);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.0f, phase_time_);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.0f, phase_time_);
            delay(delay_);

            // send back
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.02f, phase_time_);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.44f, phase_time_);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.02f, phase_time_);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.44f, phase_time_);
            delay(delay_);

            // Raise TL&BR legs up
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.5f, phase_time_);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.5f, phase_time_);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.5f, phase_time_);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.5f, phase_time_);
            delay(delay_);

            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.44f, phase_time_);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.02f, phase_time_);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.44f, phase_time_);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.02f, phase_time_);
            delay(delay_);

            // step back to standing stance
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, phase_time_);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, phase_time_);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, phase_time_);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, phase_time_);
            delay(delay_);

            // send back
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.02f, phase_time_);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.44f, phase_time_);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.02f, phase_time_);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.44f, phase_time_);
            delay(delay_);

            Serial.println("ending trot");

        } else if (buttons_ == LB) {
            //                      Trot (Backwards)
            Serial.println("Beginning backwards trot");
            // raise TR&BL legs up
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.5f, 0.1f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.5f, 0.1f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.5f, 0.1f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.5f, 0.1f);
            delay(100);

            // step TR&BL forward
            Serial.println("step TR&BL forward");
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.42f, 0.1f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.3f, 0.1f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.42f, 0.1f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.3f, 0.1f);
            delay(100);

            // back to stance
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, 0.3f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, 0.3f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.0f, 0.3f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.0f, 0.3f);
            delay(125); // works as a delay

            // Raise TL&BR legs up
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.5f, 0.1f);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.5f, 0.1f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.5f, 0.1f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.5f, 0.1f);
            delay(100);

            // step TL&BR forward
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.42f, 0.1f);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.3f, 0.1f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.42f, 0.1);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.3f, 0.1f);
            delay(100);

            // step back to standing stance
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, 0.3f);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, 0.3f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, 0.3f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, 0.3f);
            delay(125);
            Serial.println("ending backwards trot");
        }
    }

    void bound() {
        if (buttons_ == LT) {
            float phase_time = 0.03f;
            // Bound Gait
            Serial.println("Beginning Bound");
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.5f, phase_time);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.5f, phase_time);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.5f, phase_time);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.5f, phase_time);

            // step forward front
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.42f, phase_time);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.3f, phase_time);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.42f, phase_time);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.3f, phase_time);

            // step to stance front

            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, phase_time);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, phase_time);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, phase_time);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, phase_time);

            delay(90);


            // raise back slightly
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.5f, phase_time);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.5f, phase_time);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.5f, phase_time);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.5f, phase_time);

            // step forward back
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.42f, phase_time);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.3f, phase_time);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.42f, phase_time);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.3f, phase_time);

            // step to stance back
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, phase_time);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, phase_time);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.0f, phase_time);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.0f, phase_time);

            delay(90);
            Serial.println("Ending Bound");
        }
    }

    void hop() {
        if (buttons_ == RT) {
            //                     Hop
            // crouch down (similar to raising all legs)
            if (is_in_spider_mode_ == false) {
                Serial.println("beginning hop");
                Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.9f, 2.0f);
                Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.9f, 2.0f);
                Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.9f, 2.0f);
                Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.9f, 2.0f);
                Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.9f, 2.0f);
                Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.9f, 2.0f);
                Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.9f, 2.0f);
                Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.9f, 2.0f);
                delay(2000);

                // extend all legs quickly
                Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.8f, 0.03f);
                Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.8f, 0.03f);
                Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.8f, 0.03f);
                Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.8f, 0.03f);
                Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.8f, 0.03f);
                Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.8f, 0.03f);
                Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.8f, 0.03f);
                Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.8f, 0.03f);
                delay(100);

                // bring in legs
                Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.4f, 0.05f);
                Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.4f, 0.05f);
                Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.4f, 0.05f);
                Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.4f, 0.05f);
                Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.4f, 0.05f);
                Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.4f, 0.05f);
                Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.4f, 0.05f);
                Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.4f, 0.05f);

                delay(1750); // delay

                // back to standing
                Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, 2.0f);
                Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, 2.0f);
                Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, 2.0f);
                Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, 2.0f);
                Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, 2.0f);
                Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, 2.0f);
                Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.0f, 2.0f);
                Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.0f, 2.0f);
                delay(2000);
                }
            else {
                //              robot is in spider stance
                // lower legs
                Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.9f, 2.0f);
                Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.9f, 2.0f);
                Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.9f, 2.0f);
                Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.9f, 2.0f);

                Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.9f, 2.0f);
                Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.9f, 2.0f);
                Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.9f, 2.0f);
                Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.9f, 2.0f);
                delay(2000);

                // extend all legs quickly
                Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.9f, 0.03f);
                Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.9f, 0.03f);
                Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.9f, 0.03f);
                Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.9f, 0.03f);

                Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.9f, 0.03f);
                Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.9f, 0.03f);
                Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.9f, 0.03f);
                Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.9f, 0.03f);
                delay(100);

                // bring in legs quickly
                Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.4f, 0.05f);
                Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.4f, 0.05f);
                Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.4f, 0.05f);
                Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.4f, 0.05f);

                Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.4f, 0.05f);
                Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.4f, 0.05f);
                Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.4f, 0.05f);
                Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.4f, 0.05f);
                delay(100);

                // back to standing
                Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, 2.0f);
                Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, 2.0f);
                Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.0f, 2.0f);
                Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.0f, 2.0f);

                Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, 2.0f);
                Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, 2.0f);
                Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, 2.0f);
                Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, 2.0f);
                delay(2000);
            }
            Serial.println("ending hop");
        }
    }

    void extend_legs() {
        if (buttons_ == Y) {
            Serial.println("Y was pressed, lock position as zero and enter mobile stance");
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.3f, 1.0f);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.3f, 1.0f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.3f, 1.0f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.3f, 1.0f);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.3f, 1.0f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.3f, 1.0f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.3f, 1.0f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.3f, 1.0f);
            delay(2000);
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
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, 1.0f);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, 1.0f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, 1.0f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.0f, 1.0f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.0f, 1.0f);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, 1.0f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, 1.0f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, 1.0f);
            delay(2000);

            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.3f, 1.0f);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.3f, 1.0f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.3f, 1.0f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.3f, 1.0f);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.3f, 1.0f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.3f, 1.0f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.3f, 1.0f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.3f, 1.0f);
            delay(2000);

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

    void update_voltages_positions() {
        Motor<1>::instance().update_volts();
        Motor<2>::instance().update_volts();
        Motor<3>::instance().update_volts();
        Motor<4>::instance().update_volts();
        Motor<5>::instance().update_volts();
        Motor<6>::instance().update_volts();
        Motor<7>::instance().update_volts();
        Motor<8>::instance().update_volts();

        Motor<1>::instance().update_positions();
        Motor<2>::instance().update_positions();
        Motor<3>::instance().update_positions();
        Motor<4>::instance().update_positions();
        Motor<5>::instance().update_positions();
        Motor<6>::instance().update_positions();
        Motor<7>::instance().update_positions();
        Motor<8>::instance().update_positions();
    }

    void motions() {
      Microtaur::instance().stand();               // start
      Microtaur::instance().sit();                 // back
      Microtaur::instance().trot();                // X-fwd, LB-bck
      Microtaur::instance().hop();                 // RT
    //   Microtaur::instance().bound();               // LT // this is very strenuous on the legs, be careful, can break
      Microtaur::instance().compress_legs();       // B
      Microtaur::instance().extend_legs();         // Y
      Microtaur::instance().leap();                // RB
      if (buttons_ != 0) {
        Serial.println(buttons_);
      }
      buttons_ = 0;
    }
};

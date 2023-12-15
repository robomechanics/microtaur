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
    // Microtaur(){}
    
private:


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

    // PID Controller Tuning, helps tune the ammount of voltage to each motor (how strong motor is)
    float Kp_ = 60.0f;
    float Ki_ = 0.0f;
    float Kd_ = 0.0f;

    bool is_in_spider_mode_ = false;


    void init();

    uint32_t get_buttons(uint32_t buttons) {
        buttons_ = buttons;
        return buttons;
    }

    void setup() {

        // Attach serials ports and initialize PID parameters, assigns PID values to each motor
        
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

///////////////////// Kim Testing Turning Code /////////////////////////

///////////Turn like before but diffrent? freezes diagnal and moves other diagnal back [works, unreliable]//////////////        >filmed
//    void turn_right() {  //"sides move alternate directions" : turning right via alternating leg moving back and forth like a car
//         if (buttons_ == right_knoch_click_down)  {   //refrencing walk code
//             float phase_time_ = 0.1;
//             uint32_t delay_ = 100;
//             //                   FAST Walking-Trot (according to walk code)
//             Serial.println("Beginning fast walking trot turn to the right");

//             // raise TR&BL legs up
//             Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.5f, phase_time_);
//             Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.5f, phase_time_);
//             Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.5f, phase_time_);
//             Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.5f, phase_time_);
//             get_voltage_position_delay(millis(), delay_);

//             // step front right forward
//             Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.44f, phase_time_);
//             Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.02f, phase_time_);
//             // step back left backwards
//             Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.42f, phase_time_); 
//             Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.02f, phase_time_);  //was +0.2

//             // back to stance
//             Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, phase_time_);
//             Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, phase_time_);
//             Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.0f, phase_time_);
//             Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.0f, phase_time_);
//             get_voltage_position_delay(millis(), delay_);

//             // send back
//             Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.02f, phase_time_);
//             Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.44f, phase_time_);
//             Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.03f, phase_time_); //was +0.03
//             Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.42f, phase_time_); //was -0.44
//             get_voltage_position_delay(millis(), delay_);

//             delay(250);     //to let body stabalize

//             // // Raise TL&BR legs up
//             // Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.5f, phase_time_);
//             // Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.5f, phase_time_);
//             // Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.5f, phase_time_);
//             // Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.5f, phase_time_);
//             // get_voltage_position_delay(millis(), delay_);

//             // Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.42f, phase_time_); //was -0.44
//             // Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.03f, phase_time_); //was +0.02
//             // Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.42f, phase_time_); //move back right backwards
//             // Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.02f, phase_time_); // ^^   //was +0.03
//             // get_voltage_position_delay(millis(), delay_);

//             // // step back to standing stance
//             // Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, phase_time_);
//             // Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, phase_time_);
//             // Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, phase_time_);
//             // Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, phase_time_);
//             // get_voltage_position_delay(millis(), delay_);

//             // // send back
//             // Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.02f, phase_time_);
//             // Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.44f, phase_time_);
//             // Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.02f, phase_time_);
//             // Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.44f, phase_time_);
//             // get_voltage_position_delay(millis(), delay_);

//             // delay(250);

//             Serial.println("Done turning right");

//         }
//     }

// void turn_left() {  //turning left like right turn
//     if (buttons_ == left_knoch_click_down)  {
//         float phase_time_ = 0.1;
//         uint32_t delay_ = 100;
//         //                   FAST Walking-Trot (according to walk code)
//         Serial.println("Beginning fast walking trot turn to the left");

//         // Raise 1/2 and 3/8
//         Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.5f, phase_time_);
//         Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.5f, phase_time_);
//         Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.5f, phase_time_);
//         Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.5f, phase_time_);
//         get_voltage_position_delay(millis(), delay_);

//         // step ___
//         Motor<3>::instance().move_traj_by_time(cmd_pos_M7_-0.44f, phase_time_);
//         Motor<8>::instance().move_traj_by_time(cmd_pos_M6_+0.02f, phase_time_);
//         // step ___
//         Motor<2>::instance().move_traj_by_time(cmd_pos_M5_-0.44f, phase_time_); 
//         Motor<1>::instance().move_traj_by_time(cmd_pos_M4_+0.02f, phase_time_); 

//         // back to stance
//         Motor<1>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, phase_time_);
//         Motor<2>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, phase_time_);
//         Motor<3>::instance().move_traj_by_time(cmd_pos_M4_+0.0f, phase_time_);
//         Motor<8>::instance().move_traj_by_time(cmd_pos_M5_+0.0f, phase_time_);
//         get_voltage_position_delay(millis(), delay_);

//         // send back
//         Motor<1>::instance().move_traj_by_time(cmd_pos_M7_+0.03f, phase_time_); 
//         Motor<2>::instance().move_traj_by_time(cmd_pos_M6_-0.42f, phase_time_); 
//         Motor<3>::instance().move_traj_by_time(cmd_pos_M4_+0.03f, phase_time_);
//         Motor<8>::instance().move_traj_by_time(cmd_pos_M5_-0.42f, phase_time_);
//         get_voltage_position_delay(millis(), delay_);

//         delay(250);     //to let body stabalize

//         // // Raise other 2 legs (6/7 and 3/8)
//         // Motor<7>::instance().move_traj_by_time(cmd_pos_M1_-0.5f, phase_time_);
//         // Motor<6>::instance().move_traj_by_time(cmd_pos_M2_-0.5f, phase_time_);
//         // Motor<4>::instance().move_traj_by_time(cmd_pos_M3_-0.5f, phase_time_);
//         // Motor<5>::instance().move_traj_by_time(cmd_pos_M8_-0.5f, phase_time_);
//         // get_voltage_position_delay(millis(), delay_);

//         // Motor<7>::instance().move_traj_by_time(cmd_pos_M1_-0.42f, phase_time_);
//         // Motor<6>::instance().move_traj_by_time(cmd_pos_M2_+0.03f, phase_time_);
//         // Motor<4>::instance().move_traj_by_time(cmd_pos_M3_-0.44f, phase_time_); //move back right backwards
//         // Motor<5>::instance().move_traj_by_time(cmd_pos_M8_+0.02f, phase_time_); // ^^
//         // get_voltage_position_delay(millis(), delay_);

//         // // step back to standing stance
//         // Motor<7>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, phase_time_);
//         // Motor<6>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, phase_time_);
//         // Motor<4>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, phase_time_);
//         // Motor<5>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, phase_time_);
//         // get_voltage_position_delay(millis(), delay_);

//         // // send back
//         // Motor<7>::instance().move_traj_by_time(cmd_pos_M1_+0.02f, phase_time_);
//         // Motor<6>::instance().move_traj_by_time(cmd_pos_M2_-0.44f, phase_time_);
//         // Motor<4>::instance().move_traj_by_time(cmd_pos_M3_+0.02f, phase_time_);
//         // Motor<5>::instance().move_traj_by_time(cmd_pos_M8_-0.44f, phase_time_);
//         // get_voltage_position_delay(millis(), delay_);

//         // delay(250);

//         Serial.println("Done turning left");

//     }
// }

///////////////Outer legs faster then inner legs [works technically]///////////////////  //trying with excessive delays

// void turn_left() {     //for left, 1/2 6/7 faster (inner)
//         if (buttons_ == left_knoch_click_down) {    //from walk code

//             float phase_time_ = 0.1*2;   //double of normal phase time
//             uint32_t delay_ = 100/2;     //half of normal delay time

//             Serial.println("Beginning fast walking trot, turn left");

//             //first couple of walking
//             //step 1 1/2
//             Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.5f, phase_time_);
//             Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.5f, phase_time_);

//             Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.25f, phase_time_);
//             Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.25f, phase_time_);
//             get_voltage_position_delay(millis(), delay_);

//             //step 1 2/2
//             Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.44f, phase_time_);
//             Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.02f, phase_time_);

//             Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.5f, phase_time_);
//             Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.5f, phase_time_);
//             get_voltage_position_delay(millis(), delay_);

//             //step 2 1/2
//             Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, phase_time_);
//             Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, phase_time_);

//             Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.22f, phase_time_); 
//             Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.01f, phase_time_);
//             get_voltage_position_delay(millis(), delay_);

//             //step 2 2/2
//             Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.02f, phase_time_);
//             Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.44f, phase_time_);

//             Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.44f, phase_time_);
//             Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.02f, phase_time_);
//             get_voltage_position_delay(millis(), delay_);

//             //step 3 1/2
//             Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.5f, phase_time_);
//             Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.5f, phase_time_);

//             Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.22f, phase_time_);
//             Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.01f, phase_time_);
//             get_voltage_position_delay(millis(), delay_);

//             //step 3 2/2
//             Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.44f, phase_time_);
//             Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.02f, phase_time_);

//             Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.0f, phase_time_);
//             Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.0f, phase_time_);
//             get_voltage_position_delay(millis(), delay_);

//             //step 4 1/2
//             Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, phase_time_);
//             Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, phase_time_);

//             Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.01f, phase_time_);
//             Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.22f, phase_time_);
//             get_voltage_position_delay(millis(), delay_);

//             //step 4 2/2
//             Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.02f, phase_time_);
//             Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.44f, phase_time_);

//             Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.02f, phase_time_);
//             Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.44f, phase_time_);
//             get_voltage_position_delay(millis(), delay_);

//             //second couple of walking
//             //step 1 1/2
//             Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.5f, phase_time_);
//             Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.5f, phase_time_);

//             Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.25f, phase_time_);
//             Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.25f, phase_time_);
//             get_voltage_position_delay(millis(), delay_);

//             //step 1 2/2
//             Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.44f, phase_time_);
//             Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.02f, phase_time_);

//             Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.5f, phase_time_);
//             Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.5f, phase_time_);
//             get_voltage_position_delay(millis(), delay_);

//             //step 2 1/2
//             Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, phase_time_);
//             Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, phase_time_);

//             Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.22f, phase_time_); 
//             Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.01f, phase_time_);
//             get_voltage_position_delay(millis(), delay_);

//             //step 2 2/2
//             Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.02f, phase_time_);
//             Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.44f, phase_time_);

//             Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.44f, phase_time_);
//             Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.02f, phase_time_);
//             get_voltage_position_delay(millis(), delay_);

//             //step 3 1/2
//             Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.5f, phase_time_);
//             Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.5f, phase_time_);

//             Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.22f, phase_time_);
//             Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.01f, phase_time_);
//             get_voltage_position_delay(millis(), delay_);

//             //step 3 2/2
//             Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.44f, phase_time_);
//             Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.02f, phase_time_);

//             Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, phase_time_);
//             Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, phase_time_);
//             get_voltage_position_delay(millis(), delay_);

//             //step 4 1/2
//             Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, phase_time_);
//             Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, phase_time_);

//             Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.01f, phase_time_);
//             Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.22f, phase_time_);
//             get_voltage_position_delay(millis(), delay_);

//             //step 4 2/2
//             Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.02f, phase_time_);
//             Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.44f, phase_time_);

//             Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.02f, phase_time_);
//             Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.44f, phase_time_);
//             get_voltage_position_delay(millis(), delay_);

//             Serial.println("ending fast walking trot turn left");
//         }
// }

////////////////Differntial Drive Turn w/ 1:2 ratio [sucessful]//////////////////////
// void turn_right() {      //left or right?
//     if (buttons_ == right_knoch_click_down) {        //right turn by making inner legs take smaller steps then out legs at same timing

//                 float phase_time_ = 0.1;
//                 uint32_t delay_ = 100;

//                 // raise TR&BL legs up
//                 Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.5f, phase_time_);      
//                 Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.5f, phase_time_);
//                 Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.6f, phase_time_);
//                 Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.6f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 //step TR&BL forward (on ground)
//                 Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.88f, phase_time_);
//                 Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.04f, phase_time_);
//                 Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.22f, phase_time_);
//                 Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.01f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 // back to stance
//                 Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, phase_time_);
//                 Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, phase_time_);
//                 Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.0f, phase_time_);
//                 Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.0f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 // send back
//                 Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.04f, phase_time_);
//                 Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.88f, phase_time_);
//                 Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.01f, phase_time_);
//                 Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.22f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 // Raise TL&BR legs up
//                 Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.5f, phase_time_);      
//                 Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.5f, phase_time_);
//                 Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.6f, phase_time_);
//                 Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.6f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 //step TL&BR forward (?) (on ground)
//                 Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.88f, phase_time_);
//                 Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.04f, phase_time_);
//                 Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.22f, phase_time_);
//                 Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.01f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 // step back to standing stance
//                 Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, phase_time_);
//                 Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, phase_time_);
//                 Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, phase_time_);
//                 Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 // send back
//                 Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.04f, phase_time_);
//                 Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.88f, phase_time_);
//                 Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.01f, phase_time_);
//                 Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.22f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 Serial.println("ending right turn");
//     }
// }

// void turn_left() {      
//     if (buttons_ == left_knoch_click_down) {        //left turn by making inner legs take smaller steps then out legs at same timing

//                 float phase_time_ = 0.1;
//                 uint32_t delay_ = 100;


//                 // raise TR&BL legs up
//                 Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.6f, phase_time_);      
//                 Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.6f, phase_time_);
//                 Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.5f, phase_time_);
//                 Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.5f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 //step TR&BL forward (on ground)
//                 Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.22f, phase_time_);
//                 Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.01f, phase_time_);
//                 Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.88f, phase_time_);
//                 Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.04f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 // back to stance
//                 Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, phase_time_);
//                 Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, phase_time_);
//                 Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.0f, phase_time_);
//                 Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.0f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 // send back
//                 Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.01f, phase_time_);
//                 Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.22f, phase_time_);
//                 Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.04f, phase_time_);
//                 Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.88f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 // Raise TL&BR legs up
//                 Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.6f, phase_time_);      
//                 Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.6f, phase_time_);
//                 Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.5f, phase_time_);
//                 Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.5f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 //step TL&BR forward (?) (on ground)
//                 Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.22f, phase_time_);
//                 Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.01f, phase_time_);
//                 Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.88f, phase_time_);
//                 Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.04f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 // step back to standing stance
//                 Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, phase_time_);
//                 Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, phase_time_);
//                 Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, phase_time_);
//                 Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 // send back
//                 Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.01f, phase_time_);
//                 Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.22f, phase_time_);
//                 Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.04f, phase_time_);
//                 Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.88f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 Serial.println("ending left turn");
//     }
// }

////////////////Differntial Drive Turn w/ 1:2 ratio w/banking [sucessful]//////////////////////
// void turn_right() {      //left or right?
//     if (buttons_ == right_knoch_click_down) {        //right turn by making inner legs take smaller steps then out legs at same timing

//                 float phase_time_ = 0.1;
//                 uint32_t delay_ = 100;


//                 // raise TR&BL legs up
//                 Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.5f, phase_time_);      
//                 Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.5f, phase_time_);
//                 Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.5f, phase_time_);
//                 Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.5f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 //step TR&BL forward (on ground)
//                 Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.88f, phase_time_);
//                 Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.04f, phase_time_);
//                 Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.22f, phase_time_);
//                 Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.01f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 // back to stance
//                 Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, phase_time_);
//                 Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, phase_time_);
//                 Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.0f, phase_time_);
//                 Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.0f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 // send back
//                 Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.04f, phase_time_);
//                 Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.88f, phase_time_);
//                 Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.01f, phase_time_);
//                 Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.22f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 // Raise TL&BR legs up
//                 Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.5f, phase_time_);      
//                 Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.5f, phase_time_);
//                 Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.5f, phase_time_);
//                 Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.5f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 //step TL&BR forward (?) (on ground)
//                 Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.88f, phase_time_);
//                 Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.04f, phase_time_);
//                 Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.22f, phase_time_);
//                 Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.01f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 // step back to standing stance
//                 Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, phase_time_);
//                 Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, phase_time_);
//                 Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, phase_time_);
//                 Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 // send back
//                 Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.04f, phase_time_);
//                 Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.88f, phase_time_);
//                 Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.01f, phase_time_);
//                 Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.22f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 Serial.println("ending right turn");
//     }
// }

// void turn_left() {      
//     if (buttons_ == left_knoch_click_down) {        //left turn by making inner legs take smaller steps then out legs at same timing

//                 float phase_time_ = 0.1;
//                 uint32_t delay_ = 100;


//                 // raise TR&BL legs up
//                 Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.5f, phase_time_);      
//                 Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.5f, phase_time_);
//                 Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.5f, phase_time_);
//                 Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.5f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 //step TR&BL forward (on ground)
//                 Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.22f, phase_time_);
//                 Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.01f, phase_time_);
//                 Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.88f, phase_time_);
//                 Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.04f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 // back to stance
//                 Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, phase_time_);
//                 Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, phase_time_);
//                 Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.0f, phase_time_);
//                 Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.0f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 // send back
//                 Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.01f, phase_time_);
//                 Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.22f, phase_time_);
//                 Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.04f, phase_time_);
//                 Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.88f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 // Raise TL&BR legs up
//                 Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.5f, phase_time_);      
//                 Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.5f, phase_time_);
//                 Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.5f, phase_time_);
//                 Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.5f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 //step TL&BR forward (?) (on ground)
//                 Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.22f, phase_time_);
//                 Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.01f, phase_time_);
//                 Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.88f, phase_time_);
//                 Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.04f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 // step back to standing stance
//                 Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, phase_time_);
//                 Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, phase_time_);
//                 Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, phase_time_);
//                 Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 // send back
//                 Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.01f, phase_time_);
//                 Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.22f, phase_time_);
//                 Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.04f, phase_time_);
//                 Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.88f, phase_time_);
//                 get_voltage_position_delay(millis(), delay_);

//                 Serial.println("ending left turn");
//     }
// }

/////////////////////////////////Banking Turn [left sucessful]///////////////////////////     
    // void bank_left() {     //rasies legs for a left turn, must use walk function after
    //     if (buttons_ == LT) {
        
    //     float phase_time_ = 0.1;
    //     uint32_t delay_ = 100;

    //     Serial.println("Raise and lower legs for fast walk trot to the left");     

    //     //normal leg height stance [i don't think this is necissery]
    //     Motor<1>::instance().move_traj_by_time(0.0f, 1.0f);
    //     Motor<2>::instance().move_traj_by_time(2.50f, 1.0f);
    //     Motor<4>::instance().move_traj_by_time(0.0f, 1.0f);
    //     Motor<5>::instance().move_traj_by_time(2.50f, 1.0f);
    //     Motor<6>::instance().move_traj_by_time(2.50f, 1.0f);
    //     Motor<7>::instance().move_traj_by_time(0.0f, 1.0f);
    //     Motor<8>::instance().move_traj_by_time(2.50f, 1.0f);
    //     Motor<3>::instance().move_traj_by_time(0.0f, 1.0f);
    //     // duration = 1.0f seconds == 1000 ms

    //     // get_voltage_position_delay(millis(), 1000);      //debugging code

    //     // update positions
    //     cmd_pos_M1_ = 0.0f;     //sets stand position
    //     cmd_pos_M2_ = 2.50f;
    //     cmd_pos_M3_ = 0.0f;
    //     cmd_pos_M4_ = 0.0f;
    //     cmd_pos_M5_ = 2.50f;
    //     cmd_pos_M6_ = 2.50f;
    //     cmd_pos_M7_ = 0.0f;
    //     cmd_pos_M8_ = 2.50f;

    //     delay(500);

    //     //set inner legs lower (1/2 and 6/7) and outer legs up

    //     delay(1000);
    //     Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.5f, 1.0f);
    //     Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.5f, 1.0f);
    //     Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.5f, 1.0f);
    //     Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.5f, 1.0f);

    //     Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.6f, 1.0f);
    //     Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.6f, 1.0f);
    //     Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.6f, 1.0f);
    //     Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.6f, 1.0f);

    //     get_voltage_position_delay(millis(), 1000);

    //     delay(1000); // prevent spam
    //     // udpdate positions
    //     cmd_pos_M1_ = cmd_pos_M1_-0.5f;     //new values for standing position 
    //     cmd_pos_M2_ = cmd_pos_M2_-0.5f;
    //     cmd_pos_M6_ = cmd_pos_M6_-0.5f;
    //     cmd_pos_M7_ = cmd_pos_M7_-0.5f;

    //     cmd_pos_M4_ = cmd_pos_M4_+0.6f;     //new values for standing position 
    //     cmd_pos_M5_ = cmd_pos_M5_+0.6f;
    //     cmd_pos_M3_ = cmd_pos_M3_+0.6f;
    //     cmd_pos_M8_ = cmd_pos_M8_+0.6f;
    //     }  
    // }

    // void bank_right() {     //rasies legs for a right turn, must use walk function after
    //     if (buttons_ == RT) {
        
    //     float phase_time_ = 0.1;
    //     uint32_t delay_ = 100;

    //     Serial.println("Raise and lower legs for fast walk trot to the right");     

    //     //normal leg height stance
    //     Motor<1>::instance().move_traj_by_time(0.0f, 1.0f);
    //     Motor<2>::instance().move_traj_by_time(2.50f, 1.0f);
    //     Motor<4>::instance().move_traj_by_time(0.0f, 1.0f);
    //     Motor<5>::instance().move_traj_by_time(2.50f, 1.0f);
    //     Motor<6>::instance().move_traj_by_time(2.50f, 1.0f);
    //     Motor<7>::instance().move_traj_by_time(0.0f, 1.0f);
    //     Motor<8>::instance().move_traj_by_time(2.50f, 1.0f);
    //     Motor<3>::instance().move_traj_by_time(0.0f, 1.0f);
    //     // duration = 1.0f seconds == 1000 ms

    //     // get_voltage_position_delay(millis(), 1000);      //debugging code

    //     // update positions
    //     cmd_pos_M1_ = 0.0f;     //sets stand position
    //     cmd_pos_M2_ = 2.50f;
    //     cmd_pos_M3_ = 0.0f;
    //     cmd_pos_M4_ = 0.0f;
    //     cmd_pos_M5_ = 2.50f;
    //     cmd_pos_M6_ = 2.50f;
    //     cmd_pos_M7_ = 0.0f;
    //     cmd_pos_M8_ = 2.50f;

    //     delay(500);

    //     //set inner legs lower (3/8 and 4/5) and outer legs up

    //     delay(1000);
    //     Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.6f, 1.0f);      //was +0.6, making higher to get to hit the floor and actulyl make friction with the ground
    //     Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.6f, 1.0f);
    //     Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.6f, 1.0f);
    //     Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.6f, 1.0f);

    //     Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.5f, 1.0f);  
    //     Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.5f, 1.0f);
    //     Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.5f, 1.0f);
    //     Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.5f, 1.0f);

    //     get_voltage_position_delay(millis(), 1000);

    //     delay(1000); // prevent spam
    //     // udpdate positions
    //     cmd_pos_M1_ = cmd_pos_M1_+0.6f;     //new values for standing position 
    //     cmd_pos_M2_ = cmd_pos_M2_+0.6f;
    //     cmd_pos_M6_ = cmd_pos_M6_+0.6f;
    //     cmd_pos_M7_ = cmd_pos_M7_+0.6f;

    //     cmd_pos_M4_ = cmd_pos_M4_-0.5f;     //new values for standing position 
    //     cmd_pos_M5_ = cmd_pos_M5_-0.5f;
    //     cmd_pos_M3_ = cmd_pos_M3_-0.5f;
    //     cmd_pos_M8_ = cmd_pos_M8_-0.5f;
    //     }  
    // }

////////////////////////////////////////////////////////////////////////////

//////////////////////////////// Silly Walks //////////////////////////////     //make the robot switch up and down while walking
void silly_walk() {
        if (buttons_ == right_knoch_click_down) {        //button for walking, technically this is walking backwards realtive to the bound and hop and stuff but becasuse the 
            // walk performs better in this direction, moving "forwards" (twords the yellow power plug) is considered backwards

            float phase_time_ = 0.1;
            uint32_t delay_ = 100;
            //                   FAST Walking-Trot
            Serial.println("Beginning silly walk");

            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.5f, 1.0f);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.5f, 1.0f);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.5f, 1.0f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.5f, 1.0f);

            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.6f, 1.0f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.6f, 1.0f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.6f, 1.0f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.6f, 1.0f);

            // raise TR&BL legs up
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.5f, phase_time_);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.5f, phase_time_);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.5f, phase_time_);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.5f, phase_time_);
            get_voltage_position_delay(millis(), delay_);

            //step TR&BL forward (on ground)
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.44f, phase_time_);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.02f, phase_time_);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.44f, phase_time_);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.02f, phase_time_);
            get_voltage_position_delay(millis(), delay_);

            // back to stance
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, phase_time_);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, phase_time_);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.0f, phase_time_);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.0f, phase_time_);
            // send back
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.02f, phase_time_);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.44f, phase_time_);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.02f, phase_time_);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.44f, phase_time_);
            get_voltage_position_delay(millis(), delay_);

            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.6f, 1.0f);      //was +0.6, making higher to get to hit the floor and actulyl make friction with the ground
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.6f, 1.0f);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.6f, 1.0f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.6f, 1.0f);

            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.5f, 1.0f);  
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.5f, 1.0f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.5f, 1.0f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.5f, 1.0f);

            // Raise TL&BR legs up
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.5f, phase_time_);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.5f, phase_time_);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.5f, phase_time_);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.5f, phase_time_);
            get_voltage_position_delay(millis(), delay_);

            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.44f, phase_time_);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.02f, phase_time_);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.44f, phase_time_);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.02f, phase_time_);
            get_voltage_position_delay(millis(), delay_);

            // step back to standing stance
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, phase_time_);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, phase_time_);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, phase_time_);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, phase_time_);
            get_voltage_position_delay(millis(), delay_);

            // send back
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.02f, phase_time_);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.44f, phase_time_);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.02f, phase_time_);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.44f, phase_time_);
            get_voltage_position_delay(millis(), delay_);

            Serial.println("ending fast walking trot");

        } else if (buttons_ == LB) {        //walking backwards, technically this is walking forward realtive to the bound and hop and stuff but becasuse the 
            // walk performs better in the opposite direction, moving "forwards" (twords the yellow power plug) is considered backwards

            //                      SLOW Walking-Trot (Backwards)
            Serial.println("Beginning walking trot");
            // raise TR&BL legs up
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.5f, 0.1f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.5f, 0.1f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.5f, 0.1f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.5f, 0.1f);
            get_voltage_position_delay(millis(), 100);

            // step TR&BL forward
            Serial.println("step TR&BL forward");
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.42f, 0.1f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.3f, 0.1f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.42f, 0.1f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.3f, 0.1f);
            get_voltage_position_delay(millis(), 100);

            // back to stance
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, 0.3f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, 0.3f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.0f, 0.3f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.0f, 0.3f);
            get_voltage_position_delay(millis(), 125); // works as a delay

            // Raise TL&BR legs up
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.5f, 0.1f);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.5f, 0.1f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.5f, 0.1f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.5f, 0.1f);
            get_voltage_position_delay(millis(), 100);

            // step TL&BR forward
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.42f, 0.1f);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.3f, 0.1f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.42f, 0.1);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.3f, 0.1f);
            get_voltage_position_delay(millis(), 100);

            // step back to standing stance
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, 0.3f);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, 0.3f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, 0.3f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, 0.3f);
            get_voltage_position_delay(millis(), 125);
            Serial.println("ending walking trot");
        }
    }

//////////////////////////////////////////////////////////////////////////

    void stand() {
        if (buttons_ == start) {        //carried out when start button pressed, robot will stand
            Serial.println("Start was pressed, begin standing");
            Motor<1>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<2>::instance().move_traj_by_time(2.50f, 1.0f);
            Motor<4>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<5>::instance().move_traj_by_time(2.50f, 1.0f);
            Motor<6>::instance().move_traj_by_time(2.50f, 1.0f);
            Motor<7>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<8>::instance().move_traj_by_time(2.50f, 1.0f);
            Motor<3>::instance().move_traj_by_time(0.0f, 1.0f);
            // duration = 1.0f seconds == 1000 ms

            // get_voltage_position_delay(millis(), 1000);      //debugging code

            // update positions
            cmd_pos_M1_ = 0.0f;     //sets stand position
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
        if (buttons_ == back) {     //when back pressed, sits robot down
            Serial.println("Back was pressed, begin sitting");
            // starting from a stance position
            Motor<1>::instance().move_traj_by_time(0.0f, 1.0f);     //"move traj by time" rotates motor over time by set time and radian. works becasue set 0 position known
            Motor<2>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<4>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<5>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<6>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<7>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<8>::instance().move_traj_by_time(0.0f, 1.0f);
            Motor<3>::instance().move_traj_by_time(0.0f, 1.0f);
            get_voltage_position_delay(millis(), 1000);

            Serial.println("Done sitting");
        }
    }

    void go_into_spider_mode() {
        if (is_in_spider_mode_ == false && buttons_ == left_knoch_click_down) {     //goes into spider mode if not already, clikc left joystick button
            Serial.println("Microtaur is transitioning to spider mode!");
            // go back to base stance
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_, 2.0f);      //"cmd_pos_M#" set when start button pushed, rotates motor by "cmd" over the time of second variable (2.0f here)
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_, 2.0f);      //"cmd_pos_M#" is stand position of motors. so this tells robot to lie down
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_, 2.0f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_, 2.0f);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_, 2.0f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_, 2.0f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_, 2.0f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_, 2.0f);
            delay(2000);
            // raise robot
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.9f, 2.0f);     //rotate motors past stand position by +0.9f to raise robot
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.9f, 2.0f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.9f, 2.0f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.9f, 2.0f);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.9f, 2.0f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.9f, 2.0f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.9f, 2.0f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.9f, 2.0f);
            delay(2000);

            delay(1000);

            // invert legged direction of front
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+1.4f, 1.0f);     //only back 4 motors/ 2 legs
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

            cmd_pos_M1_ = cmd_pos_M1_+2.2f;     //new stand positions now that inverted
            cmd_pos_M2_ = cmd_pos_M2_+2.2f;
            cmd_pos_M4_ = cmd_pos_M4_+2.2f;
            cmd_pos_M5_ = cmd_pos_M5_+2.2f;

            is_in_spider_mode_ = true;
            Serial.println("Microtaur is in Spider Mode Now!");
        }
    }

    void revert_spider_mode() {     //undo spider mode
        if (is_in_spider_mode_ == true && buttons_ == right_knoch_click_down) {     //press right joystick
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

            cmd_pos_M1_ = cmd_pos_M1_-2.2f;     //reset stand position values now that it's back to normal
            cmd_pos_M2_ = cmd_pos_M2_-2.2f;
            cmd_pos_M4_ = cmd_pos_M4_-2.2f;
            cmd_pos_M5_ = cmd_pos_M5_-2.2f;

            is_in_spider_mode_ = false;

            Serial.println("Microtaur is now in NORMAL stance");
        }
    }

    void leap() {
        if (buttons_ == RB) {
            // 1. crouch down
            // 2. when sending back, push off ground
            // 3. move back to normal stance
            // 3. repeat
            float phase_time_ = 0.05f;      //500 ms (1/2 a second)
            uint32_t delay_ = 100;

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
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.02f+0.7f, phase_time_/2);      //very quick becasue trying to catapult itself up
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
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_, 1.0f);      //back to stand position
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_, 1.0f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_, 1.0f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_, 1.0f);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_, 1.0f);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_, 1.0f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_, 1.0f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_, 1.0f);
        }

    }

    void slow_bound() {     //tbd
        // 1. Move front quick step forward
        // 2. Move Back quick step forward
        // 3. repeat
        // if (buttons_ == ...) {

        // }



    }

    void walk() {
        if (buttons_ == X) {        //button for walking, technically this is walking backwards realtive to the bound and hop and stuff but becasuse the 
            // walk performs better in this direction, moving "forwards" (twords the yellow power plug) is considered backwards

            float phase_time_ = 0.1;
            uint32_t delay_ = 100;
            //                   FAST Walking-Trot
            Serial.println("Beginning fast walking trot");
            // raise TR&BL legs up
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.5f, phase_time_);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.5f, phase_time_);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.5f, phase_time_);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.5f, phase_time_);
            get_voltage_position_delay(millis(), delay_);

            //step TR&BL forward (on ground)
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.44f, phase_time_);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.02f, phase_time_);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.44f, phase_time_);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.02f, phase_time_);
            get_voltage_position_delay(millis(), delay_);

            // back to stance
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, phase_time_);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, phase_time_);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.0f, phase_time_);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.0f, phase_time_);
            get_voltage_position_delay(millis(), delay_);

            // send back
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.02f, phase_time_);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.44f, phase_time_);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.02f, phase_time_);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.44f, phase_time_);
            get_voltage_position_delay(millis(), delay_);

            // Raise TL&BR legs up
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.5f, phase_time_);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.5f, phase_time_);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.5f, phase_time_);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.5f, phase_time_);
            get_voltage_position_delay(millis(), delay_);

            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.44f, phase_time_);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.02f, phase_time_);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.44f, phase_time_);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.02f, phase_time_);
            get_voltage_position_delay(millis(), delay_);

            // step back to standing stance
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, phase_time_);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, phase_time_);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, phase_time_);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, phase_time_);
            get_voltage_position_delay(millis(), delay_);

            // send back
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.02f, phase_time_);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.44f, phase_time_);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.02f, phase_time_);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.44f, phase_time_);
            get_voltage_position_delay(millis(), delay_);

            Serial.println("ending fast walking trot");

        } else if (buttons_ == LB) {        //walking backwards, technically this is walking forward realtive to the bound and hop and stuff but becasuse the 
            // walk performs better in the opposite direction, moving "forwards" (twords the yellow power plug) is considered backwards

            //                      SLOW Walking-Trot (Backwards)
            Serial.println("Beginning walking trot");
            // raise TR&BL legs up
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.5f, 0.1f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.5f, 0.1f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.5f, 0.1f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.5f, 0.1f);
            get_voltage_position_delay(millis(), 100);

            // step TR&BL forward
            Serial.println("step TR&BL forward");
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.42f, 0.1f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.3f, 0.1f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.42f, 0.1f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.3f, 0.1f);
            get_voltage_position_delay(millis(), 100);

            // back to stance
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, 0.3f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, 0.3f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.0f, 0.3f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.0f, 0.3f);
            get_voltage_position_delay(millis(), 125); // works as a delay

            // Raise TL&BR legs up
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.5f, 0.1f);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.5f, 0.1f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.5f, 0.1f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.5f, 0.1f);
            get_voltage_position_delay(millis(), 100);

            // step TL&BR forward
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.42f, 0.1f);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.3f, 0.1f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.42f, 0.1);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.3f, 0.1f);
            get_voltage_position_delay(millis(), 100);

            // step back to standing stance
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, 0.3f);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, 0.3f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, 0.3f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, 0.3f);
            get_voltage_position_delay(millis(), 125);
            Serial.println("ending walking trot");
        }
    }

    void bound() {
        if (buttons_ == LT) {
            float phase_time = 0.03f;
            int traj_time = 30;
            uint32_t delay_ = 0;
            //                      Bound Gait
            Serial.println("Beginning Bound");
            float start_time = millis();
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.5f, phase_time);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.5f, phase_time);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.5f, phase_time);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.5f, phase_time);

            // step forward front
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.42f, phase_time);      //larger steps?
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.3f, phase_time);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.42f, phase_time);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.3f, phase_time);

            // step to stance front

            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, phase_time);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, phase_time);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, phase_time);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, phase_time);

            get_voltage_position_delay(start_time, 90);

            start_time = millis();      //? what does this do

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

            get_voltage_position_delay(start_time, 90);
            Serial.println("Ending Bound");
        }
    }

    void hop() {
        if (buttons_ == RT) {
            //                     Hop
            // crouch down (similar to raising all legs), how? aren't they the opposite movements
            if (is_in_spider_mode_ == false) {      //if robot in normal/ not spider stance
                Serial.println("beginning hop");
                Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.9f, 2.0f);
                Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.9f, 2.0f);
                Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.9f, 2.0f);
                Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.9f, 2.0f);
                Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.9f, 2.0f);
                Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.9f, 2.0f);
                Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.9f, 2.0f);
                Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.9f, 2.0f);
                get_voltage_position_delay(millis(), 2000);

                // extend all legs quickly
                Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.8f, 0.03f);
                Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.8f, 0.03f);
                Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.8f, 0.03f);
                Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.8f, 0.03f);
                Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.8f, 0.03f);
                Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.8f, 0.03f);
                Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.8f, 0.03f);
                Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.8f, 0.03f);
                get_voltage_position_delay(millis(), 100);

                // bring in legs
                Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.4f, 0.05f);        //also very quickly
                Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.4f, 0.05f);
                Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.4f, 0.05f);
                Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.4f, 0.05f);
                Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.4f, 0.05f);
                Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.4f, 0.05f);
                Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.4f, 0.05f);
                Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.4f, 0.05f);
                get_voltage_position_delay(millis(), 100);

                get_voltage_position_delay(millis(), 1500); // delay

                // back to standing
                Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, 2.0f);
                Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, 2.0f);
                Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, 2.0f);
                Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, 2.0f);
                Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, 2.0f);
                Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, 2.0f);
                Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.0f, 2.0f);
                Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.0f, 2.0f);
                get_voltage_position_delay(millis(), 2000);
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
                get_voltage_position_delay(millis(), 2000);

                // extend all legs quickly
                Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.9f, 0.03f);
                Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.9f, 0.03f);
                Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.9f, 0.03f);
                Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.9f, 0.03f);

                Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.9f, 0.03f);
                Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.9f, 0.03f);
                Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.9f, 0.03f);
                Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.9f, 0.03f);
                get_voltage_position_delay(millis(), 100);

                // bring in legs quickly
                Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.4f, 0.05f);
                Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.4f, 0.05f);
                Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.4f, 0.05f);
                Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.4f, 0.05f);

                Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.4f, 0.05f);
                Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.4f, 0.05f);
                Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.4f, 0.05f);
                Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.4f, 0.05f);
                get_voltage_position_delay(millis(), 100);

                // back to standing
                Motor<2>::instance().move_traj_by_time(cmd_pos_M2_+0.0f, 2.0f);
                Motor<1>::instance().move_traj_by_time(cmd_pos_M1_+0.0f, 2.0f);
                Motor<5>::instance().move_traj_by_time(cmd_pos_M5_+0.0f, 2.0f);
                Motor<4>::instance().move_traj_by_time(cmd_pos_M4_+0.0f, 2.0f);

                Motor<8>::instance().move_traj_by_time(cmd_pos_M8_+0.0f, 2.0f);
                Motor<3>::instance().move_traj_by_time(cmd_pos_M3_+0.0f, 2.0f);
                Motor<6>::instance().move_traj_by_time(cmd_pos_M6_+0.0f, 2.0f);
                Motor<7>::instance().move_traj_by_time(cmd_pos_M7_+0.0f, 2.0f);
                get_voltage_position_delay(millis(), 2000);
            }
            Serial.println("ending hop");
        }
    }

    void extend_legs() {        //moves legs slightly up
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
            get_voltage_position_delay(millis(), 1000);
            delay(1000); // prevent spam
            // udpdate positions
            cmd_pos_M1_ = cmd_pos_M1_+0.3f;     //new motor standing position for walking and all other motion manipulation 
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

    void compress_legs() {      //robot goes lower/shorter
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
            get_voltage_position_delay(millis(), 1000);

            delay(1000);
            Motor<1>::instance().move_traj_by_time(cmd_pos_M1_-0.3f, 1.0f);
            Motor<2>::instance().move_traj_by_time(cmd_pos_M2_-0.3f, 1.0f);
            Motor<4>::instance().move_traj_by_time(cmd_pos_M4_-0.3f, 1.0f);
            Motor<5>::instance().move_traj_by_time(cmd_pos_M5_-0.3f, 1.0f);
            Motor<6>::instance().move_traj_by_time(cmd_pos_M6_-0.3f, 1.0f);
            Motor<7>::instance().move_traj_by_time(cmd_pos_M7_-0.3f, 1.0f);
            Motor<8>::instance().move_traj_by_time(cmd_pos_M8_-0.3f, 1.0f);
            Motor<3>::instance().move_traj_by_time(cmd_pos_M3_-0.3f, 1.0f);
            get_voltage_position_delay(millis(), 1000);

            delay(1000); // prevent spam
            // udpdate positions
            cmd_pos_M1_ = cmd_pos_M1_-0.3f;     //new values for standing position 
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

    void update_voltages_positions() {      //why are you updating it? is this just a called helper function?
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
        Microtaur::instance().walk();                // X-fwd, LB-bck
        // Microtaur::instance().hop();                 // RT
        // Microtaur::instance().bound();               // LT
        Microtaur::instance().compress_legs();       // B
        Microtaur::instance().extend_legs();         // Y
        Microtaur::instance().silly_walk();          // right knoch
        // Microtaur::instance().turn_right();          // right knoch
        // Microtaur::instance().turn_left();           // left knoch
        // Microtaur::instance().bank_right();         // RT
        // Microtaur::instance().bank_left();         // LT
        // // Microtaur::instance().go_into_spider_mode(); // left knoch
        // Microtaur::instance().revert_spider_mode();  // right knoch
        Microtaur::instance().leap();                // RB
        // Microtaur::instance().manual_get_voltage();  // left knoch
        // Microtaur::instance().voltage_readings(1);
        // Microtaur::instance().activateCoast();       // right knoch
        // Microtaur::instance().slow_bound();          // TBD
        // Microtaur::instance().getPos();              // left knoch
        // Microtaur::instance().test_comms();          // testing motors


        if (buttons_ != 0) { // if a button is pressed: report pressed button
            Serial.println(buttons_);
        }

        buttons_ = 0; // resets buttons_


    }


    void print_headers() {
        Serial.println("Time, M1, M2, M4, M5, M6, M7, M8, M3, P1, P2, P4, P5, P6, P7, P8, P3");
    }

    void get_voltage_position_delay(uint32_t start_time, uint32_t duration) {       //prints voltage? or delay for voltage to be outputed?
        print_headers();
        // Timer3.restart();
        while (millis() < start_time + duration) {
            voltage_readings(millis()); // printing out real time
            update_voltages_positions();
        }
        // Timer3.stop();
    }
























//////////////////////////// Debugging functions ///////////////////////////////
    void test_comms() { // testing motor comms

        // Motor<1>::instance().move_traj_by_time(0.0f, 1.0f);
        // delay(3000);
        // Motor<1>::instance().move_traj_by_time(3.14f, 1.0f);
        // delay(3000);

        // Motor<2>::instance().move_traj_by_time(3.14f, 1.0f);
        // delay(3000);
        // Motor<2>::instance().move_traj_by_time(3.14f, 1.0f);
        // delay(3000);

        // Motor<3>::instance().move_traj_by_time(3.14f, 1.0f);
        // delay(3000);
        // Motor<3>::instance().move_traj_by_time(3.14f, 1.0f);
        // delay(3000);

        // Motor<4>::instance().move_traj_by_time(0.0f, 1.0f);
        // delay(3000);
        // Motor<4>::instance().move_traj_by_time(3.14f, 1.0f);
        // delay(3000);

        // Motor<5>::instance().move_traj_by_time(0.0f, 1.0f);
        // delay(3000);
        // Motor<5>::instance().move_traj_by_time(3.14f, 1.0f);
        // delay(3000);

        // Motor<6>::instance().move_traj_by_time(3.14f, 1.0f);
        // delay(3000);
        // Motor<6>::instance().move_traj_by_time(3.14f, 1.0f);
        // delay(3000);

        // Motor<7>::instance().move_traj_by_time(3.14f, 1.0f);
        // delay(3000);
        // Motor<7>::instance().move_traj_by_time(3.14f, 1.0f);
        // delay(3000);

        // Motor<8>::instance().move_traj_by_time(0.0f, 1.0f);
        // delay(3000);
        // Motor<8>::instance().move_traj_by_time(3.14f, 1.0f);
        // delay(3000);

        delay(10000); // delay 10 secs
    }


    void manual_get_voltage() {
        if (buttons_ == left_knoch_click_down) {
            voltage_readings(millis());
            update_voltages_positions();
        }
    }

    void voltage_readings(uint32_t time) {
        // Serial.print(time); Serial.print(", ");
        // Serial.print(Motor<1>::instance().get_volts()); Serial.print(", ");
        // Serial.print(Motor<2>::instance().get_volts()); Serial.print(" \n");

        // Serial.print(Motor<4>::instance().get_volts()); Serial.print(", ");
        // Serial.print(Motor<5>::instance().get_volts()); Serial.print(" \n");

        // Serial.print(Motor<6>::instance().get_volts()); Serial.print(", ");
        // Serial.print(Motor<7>::instance().get_volts()); Serial.print(", ");

        Serial.print(Motor<8>::instance().get_volts()); Serial.print(", ");
        Serial.print(Motor<3>::instance().get_volts()); Serial.print(" \n");
    }

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

    void kill() {       //stops motor movement 
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
    if (buttons_ == left_knoch_click_down) {
    // Motor<1>::instance().set_coast_mode();
    // Motor<2>::instance().set_coast_mode();
        Serial.print("Motor 6:");
        Serial.print(Motor<6>::instance().get_location());
        Serial.print(" Motor 7: ");
        Serial.print(Motor<2>::instance().get_location());
        Serial.print("\n");
        }
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



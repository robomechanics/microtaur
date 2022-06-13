#include <Arduino.h>
#include "ChRt.h"
// #include "microtaur.h"
#include "motor.h"
#include "led.h"
#include "joystick.h"
#include "controllers/controllers.h"

double a = 0;

void joy_callback(const JoyState state, const JoyState prev_state)
{
  // Serial.printf("Joy: %s",state.buttons.to_string().c_str());
  Serial.print("Joystick: buttons = ");
  Serial.print(state.buttons.to_string().c_str());
  Serial.print(" Axes: ");
  Serial.print(state.axes[0]);
  Serial.print(":");
  Serial.print(state.axes[1]);
  Serial.print(" ");
  Serial.print(state.axes[2]);
  Serial.print(":");
  Serial.println(state.axes[3]);
}

void chSetup()
{
  // Microtaur::instance().init();
  Motor<1>::instance().init(NORMALPRIO + 1);
  Motor<2>::instance().init(NORMALPRIO + 1);
  Motor<3>::instance().init(NORMALPRIO + 1);
  Motor<4>::instance().init(NORMALPRIO + 1);
  Motor<5>::instance().init(NORMALPRIO + 1);
  Motor<6>::instance().init(NORMALPRIO + 1);
  Motor<7>::instance().init(NORMALPRIO + 1);
  Motor<8>::instance().init(NORMALPRIO + 1);
  Joystick::instance().connectCallback(joy_callback);
  Joystick::instance().init(NORMALPRIO + 2);
  LED::instance().init(NORMALPRIO + 3);
}


void setup()
{
  Serial.begin(2000000);
  while (!Serial); // wait for Arduino Serial Monitor
  Motor<1>::instance().attach_serial_port(Serial1);
  Motor<2>::instance().attach_serial_port(Serial2);
  Motor<3>::instance().attach_serial_port(Serial3);
  Motor<4>::instance().attach_serial_port(Serial4);
  Motor<5>::instance().attach_serial_port(Serial5);
  Motor<6>::instance().attach_serial_port(Serial6);
  Motor<7>::instance().attach_serial_port(Serial7);
  Motor<8>::instance().attach_serial_port(Serial8);

  Motor<1>::instance().set_gains(10,2);

/*
  float motor_zeros[8] = {0,10,0,0,0,0,0,0};;

  Motor<1>::instance().set_position(motor_zeros[0]);
  Motor<2>::instance().set_position(motor_zeros[1]);
  Motor<3>::instance().set_position(motor_zeros[2]);
  Motor<4>::instance().set_position(motor_zeros[3]);
  Motor<5>::instance().set_position(motor_zeros[4]);
  Motor<6>::instance().set_position(motor_zeros[5]);
  Motor<7>::instance().set_position(motor_zeros[6]);
  Motor<8>::instance().set_position(motor_zeros[7]);
*/
  // Joystick::instance().run();

  // Initialize OS and then call chSetup.
  chBegin(chSetup);
  
}

void loop()
{
  float motor_zeros[8] = {0,10,0,0,0,0,0,0};
  /*
  Motor<1>::instance().set_position(motor_zeros[0]);
  Motor<2>::instance().set_position(motor_zeros[1]);
  Motor<3>::instance().set_position(motor_zeros[2]);
  Motor<4>::instance().set_position(motor_zeros[3]);
  Motor<5>::instance().set_position(motor_zeros[4]);
  Motor<6>::instance().set_position(motor_zeros[5]);
  Motor<7>::instance().set_position(motor_zeros[6]);
  Motor<8>::instance().set_position(motor_zeros[7]);
  */
  //  Motor<8>::instance().set_position(a);
  // Motor<3>::instance().set_position(a);
  Motor<1>::instance().set_position(-1.2);
  Motor<2>::instance().set_position(-0.8);
  Motor<3>::instance().set_position(0.6);
  Motor<4>::instance().set_position(-1.3);
  Motor<5>::instance().set_position(-0.5);
  Motor<6>::instance().set_position(-1);
  Motor<7>::instance().set_position(0.2);
  Motor<8>::instance().set_position(-0.3);
  //a += 0.00001;
  // Serial.println(a);
  Serial.println(Motor<7>::instance().get_position());
  //std::bitset<12> buttons = joystick.getButtons();
  //Serial.println(buttons.to_string().c_str());
  //Serial.println(Joystick::instance().isConected());
}

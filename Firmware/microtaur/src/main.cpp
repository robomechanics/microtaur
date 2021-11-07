#include <Arduino.h>
#include "ChRt.h"
// #include "microtaur.h"
#include "motor.h"
#include "led.h"
#include "joystick.h"
#include "controllers/controllers.h"

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
  // Motor<3>::instance().init(NORMALPRIO + 1);
  Joystick::instance().connectCallback(joy_callback);
  Joystick::instance().init(NORMALPRIO + 2);
  LED::instance().init(NORMALPRIO + 3);
}


void setup()
{
  Serial.begin(2000000);
  while (!Serial); // wait for Arduino Serial Monitor
  Motor<1>::instance().attach_serial_port(Serial3);
  Motor<2>::instance().attach_serial_port(Serial4);
  // Motor<3>::instance().attach_serial_port(Serial1);
  // Initialize OS and then call chSetup.
  chBegin(chSetup);
  
}

void loop()
{
}
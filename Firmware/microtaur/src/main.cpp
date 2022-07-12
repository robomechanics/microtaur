#include <Arduino.h>
#include "ChRt.h"
#include "microtaur.h"
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
  // Joystick::instance().connectCallback(joy_callback);
  Joystick::instance().init(NORMALPRIO + 2);
  // LED::instance().init(NORMALPRIO + 3);
}

void setup()
{
  Serial.begin(2000000);
  while (!Serial); // wait for Arduino Serial Monitor
  Microtaur::instance().setup();
  // Joystick::instance().run();
  // Initialize OS and then call chSetup.
  chBegin(chSetup);
}


void loop()
{
  Microtaur::instance().get_buttons(joystick.getButtons());
  Microtaur::instance().motions();

  
  // Serial.print(millis()); Serial.print(" M1:"); Serial.print(Motor<1>::instance().get_volts()); Serial.print(" ");
  // Serial.print("M2:"); Serial.print(Motor<2>::instance().get_volts()); Serial.print(" ");

  // Serial.print("M4:"); Serial.print(Motor<4>::instance().get_volts()); Serial.print(" ");
  // Serial.print("M5:"); Serial.print(Motor<5>::instance().get_volts()); Serial.print(" ");

  // Serial.print("M6:"); Serial.print(Motor<6>::instance().get_volts()); Serial.print(" ");
  // Serial.print("M7:"); Serial.print(Motor<7>::instance().get_volts()); Serial.print(" ");

  // Serial.print("M8:"); Serial.print(Motor<8>::instance().get_volts()); Serial.print(" ");
  // Serial.print("M3:"); Serial.print(Motor<3>::instance().get_volts()); Serial.print(" \n");
}

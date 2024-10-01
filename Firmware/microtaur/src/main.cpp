#include <Arduino.h>
#include "ChRt.h"
#include "microtaur.h"
#include "motor.h"
#include "led.h"
#include "joystick.h"
#include "controllers/controllers.h"
#include "TimerOne.h"
#include "power_monitor_client.hpp"

void joy_callback(const JoyState state, const JoyState prev_state)
{
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
  Joystick::instance().connectCallback(joy_callback);
  Joystick::instance().init(NORMALPRIO + 2);  
}

void setup()
{
  Serial.begin(2000000);
  while (!Serial); // wait for Arduino Serial Monitor
  Microtaur::instance().setup();
  chBegin(chSetup);
}


void loop()
{
  Microtaur::instance().get_buttons(joystick.getButtons());
  Microtaur::instance().motions();
}
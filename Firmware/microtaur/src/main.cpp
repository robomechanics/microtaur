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
  // thread_obj::instance().init(NORMALPRIO + 2);
  // LED::instance().init(NORMALPRIO + 3);
  
}

void setup()
{
  Serial.begin(2000000);
  while (!Serial); // wait for Arduino Serial Monitor
  Microtaur::instance().setup();
  
  // Joystick::instance().run();
  // Initialize OS and then call chSetup.
  
  // Serial.println("Hello");
  chBegin(chSetup);
  // threads.addThread(print_vals);
  
}


void loop()
{
  // if (count == 0) {
  //   Timer1.initialize(1000);
  //   // Timer1.attachInterrupt(Microtaur::instance().update_voltages_positions());
  //   Timer1.attachInterrupt(update_vals);
  // }
  Microtaur::instance().get_buttons(joystick.getButtons());
  Microtaur::instance().motions();
  // Microtaur::instance().update_voltages_positions();
  // Microtaur::instance().voltage_readings(1);
  // Microtaur::instance().update_voltages_positions();
}
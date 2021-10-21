#include <Arduino.h>
#include "joystick.h"
#include "ChRt.h"
#include "led.h"

uint32_t buttons_prev = 0;


void callback(const JoyState state, const JoyState prev_state)
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

static THD_WORKING_AREA(waJoystickThread, 200);
static THD_FUNCTION(JoystickThread, arg){
  (void)arg;
  while (true){
    Joystick& j = Joystick::instance();
    j.update();
    chThdSleepMilliseconds(1);
  }
}

static THD_WORKING_AREA(waLEDThread, 200);
static THD_FUNCTION(LEDThread, arg){
  (void)arg;
  while (true){
    LED& led = LED::instance();
    led.run();
  }
}

void chSetup(){
  chThdCreateStatic(waJoystickThread, sizeof(waJoystickThread),
                    NORMALPRIO + 2, JoystickThread, NULL);
  chThdCreateStatic(waLEDThread, sizeof(waLEDThread),
                    NORMALPRIO + 2, LEDThread, NULL);
}

void setup()
{
  Serial.begin(2000000);
  LED& led = LED::instance();
  // Serial1.begin(115200);
  while (!Serial)
    ; // wait for Arduino Serial Monitor
  Joystick& j = Joystick::instance();
  j.connectCallback(callback);
  // Initialize OS and then call chSetup.
  chBegin(chSetup);
}

void loop()
{
}
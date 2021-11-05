#include <Arduino.h>
#include "joystick.h"
#include "ChRt.h"
#include "led.h"
#include "imu.h"
#include "machine.h"
#include "controllers/controllers.h"

//timers
virtual_timer_t control_timer;

//events
event_source_t control_event_source;

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

static THD_WORKING_AREA(waFSMThread, 200);
static THD_FUNCTION(FSMThread, arg)
{
  (void)arg;
  
  event_listener_t control_listener;
  chEvtRegisterMask(&control_event_source,
                    &control_listener,
                    EVENT_MASK(0));
  Machine &machine = Machine::instance();
  while (true){
    eventmask_t evt = chEvtWaitAny(ALL_EVENTS);
    machine.run();
  }
}

static THD_WORKING_AREA(waJoystickThread, 200);
static THD_FUNCTION(JoystickThread, arg)
{
  (void)arg;

  Joystick &joy = Joystick::instance();
  while (true)
    joy.run();
}

static THD_WORKING_AREA(waLEDThread, 200);
static THD_FUNCTION(LEDThread, arg)
{
  (void)arg;
  
  LED &led = LED::instance();
  while (true)
    led.run();
}

static THD_WORKING_AREA(waIMUThread, 200);
static THD_FUNCTION(IMUThread, arg)
{
  (void)arg;

  IMU &imu = IMU::instance();
  imu.run();
}
void control_callback(void *)
{
  Serial.flush();
  chEvtBroadcast(&control_event_source);
  chVTSet(&control_timer, TIME_MS2I(100), control_callback, NULL);
}
void chSetup()
{
  //Events
  chEvtObjectInit(&control_event_source);

  // Threads
  chThdCreateStatic(waJoystickThread, sizeof(waJoystickThread),
                    NORMALPRIO + 2, JoystickThread, NULL);
  chThdCreateStatic(waLEDThread, sizeof(waLEDThread),
                    NORMALPRIO + 3, LEDThread, NULL);
  chThdCreateStatic(waIMUThread, sizeof(waIMUThread),
                    NORMALPRIO + 4, IMUThread, NULL);
  chThdCreateStatic(waFSMThread, sizeof(waFSMThread),
                    NORMALPRIO + 1, FSMThread, NULL);
  

  // Timers
  chVTSet(&control_timer, TIME_MS2I(100), control_callback, NULL);
}

void setup()
{
  Serial.begin(2000000);
  // Serial1.begin(115200);
  while (!Serial)
    ; // wait for Arduino Serial Monitor
  Joystick &j = Joystick::instance();
  j.connectCallback(joy_callback);
  // Initialize State Machine
  Machine &machine = Machine::instance();
  machine.addController(std::unique_ptr<WalkingController>(new WalkingController()));
  machine.switchController("WalkingController");
  // Initialize OS and then call chSetup.
  chBegin(chSetup);
}

void loop()
{
}
#include "joystick.h"
#include "ChRt.h"
#include "led.h"

USBHost usb;
USBHub hub(usb);
USBHIDParser hid(usb);
JoystickController joystick(usb);
USBDriver *drivers[] = {&hub, &joystick, &hid};
bool driver_active[USB_DEVICES] = {false, false, false};
const char *driver_names[USB_DEVICES] = {"Hub", "Djoystick", "HID"};
USBHIDInput *hiddrivers[] = {&joystick};
const char *hid_driver_names[USB_DEVICES] = {"Hjoystick"};
bool hid_driver_active[USB_DEVICES] = {false};


Joystick::Joystick() : is_connected_(false)
{
    usb.begin();
}

// void Joystick::init(tprio_t priority){
//     Thread<Joystick>::init(priority);
// }

void Joystick::run()
{

    while (true){
        auto prev = chVTGetSystemTime();
        usb.Task();
        if (*hiddrivers[0] != hid_driver_active[0])
        {
            if (hid_driver_active[0])
            {
                Serial.println("Joystick disconnected");
                hid_driver_active[0] = false;
                is_connected_ = false;
                Serial.println("Not Connected");
                LED& led = LED::instance();
                led.set(50,950);
            }
            else
            {
                Serial.println("Joystick connected");
                hid_driver_active[0] = true;
                is_connected_=true;
                LED& led = LED::instance();
                Serial.println("Connected");
                led.set(500,500);
            }
        }

        if (joystick.available())
        {

            prev_state_ = state_;
            state_.buttons = joystick.getButtons();
            state_.axes[0] = joystick.getAxis(0);
            state_.axes[1] = joystick.getAxis(1);
            state_.axes[2] = joystick.getAxis(2);
            state_.axes[3] = joystick.getAxis(5);
            if(cb_) 
                cb_(state_, prev_state_);
        }
        joystick.joystickDataClear();
        prev = chThdSleepUntilWindowed(prev, chTimeAddX(prev, TIME_MS2I(1)));
    }
}
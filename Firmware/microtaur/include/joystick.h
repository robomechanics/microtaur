#pragma once
#include <Arduino.h>
#include "USBHost_t36.h"
#include <bitset>
#include <vector>
#include <functional>

#define USB_DEVICES 3

extern USBHost usb;
extern USBHub hub;
extern USBHIDParser hid;
extern JoystickController joystick;
extern USBDriver *drivers[];
extern const char * driver_names[USB_DEVICES];
extern USBHIDInput *hiddrivers[];
extern const char * hid_driver_names[USB_DEVICES];
extern bool hid_driver_active[USB_DEVICES];

struct JoyState{
    std::bitset<12> buttons;
    int axes[4];
};

typedef std::function<void(const JoyState, const JoyState)> CallbackFunction;

class Joystick {
    public:
        Joystick();
        ~Joystick();
        void update();
        void connectCallback(CallbackFunction cb){ 
            cb_ = cb;
        }

    private:
        JoyState state_;
        JoyState prev_state_;
        CallbackFunction cb_;
};
# Microtaur firmware

This folder contains the firmware files for the Microtaur robot. 

## Compiling and Uploading to Teensy 4.1

The repository is built on the PlatformIO ide that's bundled with VSCode. To install PlatformIO, follow the instructions on platformio.org. Once the system is installed, open `Firmware/microtaur` in vscode and you can build and upload the program from the PlatformIO menu. All dependencies should be automatically downloaded. 

PlatformIO should work on all platforms that support VSCode. This has been tested on Windows and Ubuntu. 

## Preparing the Teensy 4.1 for Battery Power

The teensy 4.1 has a jumper to select usb power or 5V input from one of its breakout pins. Make sure the traces are cut between the USB power in and the 5V. This makes sure that the battery and USB power are isolated. This also means that you will not be able to develop on the Microtaur without a battery connected. 

## Behavior Controllers

The behavior controllers are abstracted out into the `include/controllers` and `src/controllers` folder. Each behavior that is written for the microtaur inherits from the `ControllerBase` class defined in `include/controllers/controller_base.h`. Each new controller requires the redefinition of virtual functions: `before()`, `run()`, and `after()`. `before()` is called before the controller is updated, `run()` is called every control update which is executed at the controller rate and `after()` is called once the controller is stopped and a new controller is being switched to.

Each new controller needs to be registered to the global state machine defined in `include/machine.h`. The machine api exposes the `add_controller()` and `switch_controller()` methods to modify the machine. We expect the controller switches to happen through a Joystick change message. Controllers should be added in the main.cpp file's `setup()` method. 

## Binding Controller Switches to Joystick buttons. 





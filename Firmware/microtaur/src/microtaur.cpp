#include "microtaur.h"

void Microtaur::init()
{
        init_imu();
        init_led();
        init_machine();
        init_motors();
}

void Microtaur::init_motors()
{
    Motor<0>::instance().init(NORMALPRIO + 1);
    Motor<1>::instance().init(NORMALPRIO + 1);
    Motor<2>::instance().init(NORMALPRIO + 1);
    Motor<3>::instance().init(NORMALPRIO + 1);
    Motor<4>::instance().init(NORMALPRIO + 1);
    Motor<5>::instance().init(NORMALPRIO + 1);
    Motor<6>::instance().init(NORMALPRIO + 1);
    Motor<7>::instance().init(NORMALPRIO + 1);
}

void Microtaur::init_imu()
{
    IMU::instance().init(NORMALPRIO + 4);
}
void Microtaur::init_machine()
    {
      auto &machine = Machine::instance();
      machine.addController(std::unique_ptr<WalkingController>(new WalkingController()));
      machine.switchController("WalkingController");
      machine.init(NORMALPRIO + 5);

    }
void Microtaur::init_led(){
  LED::instance().init(NORMALPRIO + 3);
}
#pragma once

#include "controller_base.h"


class WalkingController : public ControllerBase {

    public:
        WalkingController();
        void run();
        void before();
        void after();

};
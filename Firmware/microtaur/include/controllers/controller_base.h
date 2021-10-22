#pragma once
#include "controllers/controller_base.h"
#include <string>

class ControllerBase {
    protected:
        std::string name_;
        double rate_;
        ControllerBase(std::string name, double rate): name_(name), rate_(rate){}
    public:
        std::string name(){return name_;}
        double rate(){return rate_;}
        virtual void before() = 0;
        virtual void run() = 0;
        virtual void after() = 0;
};
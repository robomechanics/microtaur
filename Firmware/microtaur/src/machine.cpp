#include "machine.h"
#include "ChRt.h"

Machine::Machine(): running_(false), running_mutex_(_MUTEX_DATA(running_mutex_)){
    
}

void Machine::addController(std::unique_ptr<ControllerBase> controller_ptr){
    controller_list_[controller_ptr->name()] = std::move(controller_ptr);
}

void Machine::run(){
    chMtxLock(&running_mutex_);
    if (running_){
        auto prev = chVTGetSystemTime();
        controller_list_[controller_running_]->run();
        double rate = controller_list_[controller_running_]->rate();
        unsigned int sleep_time_ms = static_cast<unsigned int>(1000./rate);
        prev = chThdSleepUntilWindowed(prev, chTimeAddX(prev, TIME_MS2I(sleep_time_ms)));

    }
    chMtxUnlock(&running_mutex_);
}

void Machine::start(){
    chMtxLock(&running_mutex_);
    running_ = true;
    chMtxUnlock(&running_mutex_);
}

void Machine::stop(){
    chMtxLock(&running_mutex_);
    running_ = false;
    chMtxUnlock(&running_mutex_);
}

void Machine::switchController(std::string name){
    stop();
    if (!controller_running_.empty()){
        controller_list_[controller_running_]->after();
        Serial.printf("[%s]->", controller_running_.c_str());
    }
    else{
        Serial.print("[]->");
    }
    controller_running_ = name;
    controller_list_[controller_running_]->before();
    Serial.printf("[%s]", name.c_str());
    start();
}

std::string Machine::state(){
    return controller_running_;
}
#include "machine.h"
#include "ChRt.h"

Machine::Machine(): running_(false){
    
}

void Machine::addController(std::unique_ptr<ControllerBase> controller_ptr){
    controller_list_[controller_ptr->name()] = std::move(controller_ptr);
}

void Machine::run(){
    if (running_){
        controller_list_[controller_running_]->run();
        double rate = controller_list_[controller_running_]->rate();
        chThdSleepMilliseconds(1000./rate);
    }
}

void Machine::start(){
    running_ = true;
}

void Machine::stop(){
    running_ = false;
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
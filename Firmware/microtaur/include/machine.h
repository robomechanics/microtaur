#pragma once

#include "controllers/controllers.h"
#include "singleton.h"
#include <map>
#include <vector>
#include <string>
#include <memory>

typedef std::map<std::string, std::unique_ptr<ControllerBase>> ControllerList;

class Machine : public Singleton<Machine> {
    friend class Singleton<Machine>;
    ControllerList controller_list_;
    std::string controller_running_;
    bool running_;
    Machine();
    public:
        void switchController(std::string controller_name);
        void addController(std::unique_ptr<ControllerBase> controller);
        void run();
        void start();
        void stop();
        std::string state();

};

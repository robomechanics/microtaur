#pragma once

#include "controllers/controllers.h"
#include "singleton.h"
#include <map>
#include <vector>
#include <string>
#include <memory>

typedef std::map<std::string, std::unique_ptr<ControllerBase>> ControllerList;
//!  The Finite-State Machine Class
/*!
  This class controls the execution of controllers and the switching between controllers.
*/
class Machine : public Singleton<Machine> {
    friend class Singleton<Machine>;
    ControllerList controller_list_;
    std::string controller_running_;
    bool running_;
    Machine();
    public:
        //! Switch to a new controller
        /*!
            This function is called to switch to controller <controller_name> from the currently running controller. The function first stops the state machine, 
            calls the after function for the previous controller, calls the before function of the new controller and starts the state machine back up with the 
            new controller as the running controller. 
            \param controller_name A string containing the name of the new controller to switch to. 
        */
        void switchController(std::string controller_name);
        //! Add a new controller
        /*!
            This function is called as part of machine setup to add a controller. 
            \param controller A unique_pointer to a controller
        */
        void addController(std::unique_ptr<ControllerBase> controller);
        //! Execute one iteration of the state machine
        void run();
        //! Start the the state machine
        void start();
        //! Stop the the state machine. Calling the run function in stopped state does nothing.
        /*! 
            Stop the the state machine. Calling the run function in stopped state does nothing.
        */
        void stop();
        //! Get the currently running controller
        std::string state();

};

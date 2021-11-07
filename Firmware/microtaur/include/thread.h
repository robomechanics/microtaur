#pragma once

#include "ChRt.h"
#include <functional>
#define DEFAULT_STACK 200

template<typename T, unsigned int size>
class Thread
{

    static THD_WORKING_AREA(work_area_, size);
protected:
    thread_t *thread_;
    void set_thread(thread_t* thread){
        thread_ = thread;
    }

public:
    thread_t *thread() { return thread_; }
    

    void signal(eventmask_t mask)
    {
        chEvtSignal(thread_, mask);
    }

    static void thread_fn(void *arg)
    {
        T& obj = *reinterpret_cast<T*>(arg);
        obj.run();
    }

    void init(tprio_t priority)
    {
        chThdCreateStatic(work_area_,
                          sizeof(work_area_),
                          priority,
                          &Thread<T, size>::thread_fn,
                          this);
    }
    virtual void run() = 0;
};

template<typename T, unsigned int size>
stkalign_t Thread<T, size>::work_area_[THD_WORKING_AREA_SIZE(size) / sizeof (stkalign_t)];